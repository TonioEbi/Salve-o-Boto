/**
 * @file GameWorld.h
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld implementation.
 * 
 * @copyright Copyright (c) 2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "raylib/raylib.h"

#include "GameWorld.h"
#include "GlobalVariables.h"
#include "ResourceManager.h"

#include "Player.h"
#include "Npc.h"
#include "GameMechanics.h"
#include "Score.h"



//#include "raylib/raymath.h"
//#define RAYGUI_IMPLEMENTATION    // to use raygui, comment these three lines.
//#include "raylib/raygui.h"       // other compilation units must only include
//#undef RAYGUI_IMPLEMENTATION     // raygui.h

/**
 * @brief Creates a dinamically allocated GameWorld struct instance.
 */
GameWorld* createGameWorld( State initialState ) { //initialize the gameworld with the initial values
    score = 0;

    GameWorld *gw = (GameWorld*) malloc( sizeof( GameWorld ) );

    gw->player = createPlayer();
    for(int i = 0; i < MAX_NPC; i++){
        gw->npc[i] = NULL;
    }
    gw->activeNpc = 0;
    gw->timer = 0.0f;
    gw->spawnTimer = 0.0f;
    gw->spawnInterval = INITIAL_SPAWN_INTERVAL;
    gw->timeCount = 0;
    gw->lastSec = 0;
    gw->BubbleTimer = 0;
    gw->activeBubble = 0;
    gw->gameState = initialState;
    gw->escapedEnemies = 0;
    gw->caughtEnemies = 0;
    gw->npcSpeed = 60;
    return gw;
}

/**
 * @brief Destroys a GameWindow object and its dependecies.
 */
void destroyGameWorld( GameWorld *gw ) { //free the gameworld from the memory
    for (int i = 0; i < MAX_NPC; i++) {
        if (gw->npc[i] != NULL) {
            free(gw->npc[i]);
        }
    }
    free( gw->player ); 
    free( gw );
}

/**
 * @brief Reads user input and updates the state of the game.
 */
void updateGameWorld( GameWorld *gw, float delta ) { //update the gameworld with all its components
    gw->timer += delta;
    updatePlayer( gw->player, delta );
    gw->spawnTimer += delta;
    gw->BubbleTimer += delta;

    //Pause function
    if(gw->gameState == GAME_RUNNING){
        if(IsKeyPressed(KEY_P)){
            gw->gameState = GAME_PAUSED;
        }
    }

    //timer logic that controls the enemies spawn
    int currentSec = (int)gw->timer;

    if (currentSec > gw->lastSec) {
        gw->timeCount++;
        gw->BubbleTimer++;
        gw->lastSec = currentSec;

        //Npc spawn logic
        if(gw->spawnTimer >= gw->spawnInterval){
            gw->spawnTimer = 0.0f;

            if (gw->activeNpc < MAX_NPC) {
                for (int i = 0; i < MAX_NPC; i++) {
                    if (gw->npc[i] == NULL) {
                        gw->npc[i] = createNpc(gw->npcSpeed);
                        gw->activeNpc++;
                        break;                   
                    }
                }
            }
        }

        // Increase the speed and decrease spawn interval of the game if x enemies escape/are captured
        if(gw->escapedEnemies >= ENEMY_ESCAPE_LIMIT || gw->caughtEnemies >= ENEMY_CAUGHT_LIMIT) {
            gw->npcSpeed += 4;
            gw->npcSpeed = fmin(gw->npcSpeed, MAX_NPC_SPEED);
            gw->spawnInterval = fmax(gw->spawnInterval - SPAWN_DECREMENT, MIN_SPAWN_INTERVAL);

            // Reset the counters
            gw->escapedEnemies = 0;
            gw->caughtEnemies = 0;
        }

        //Bubble spawn logic
        if(gw->BubbleTimer >= BUBBLE_SPAWN_INTERVAL){
            gw->BubbleTimer = 0.0f;

            if(gw->activeNpc < MAX_NPC) {
                for(int i = 0; i < MAX_NPC; i++) {
                    if(gw->npc[i] == NULL) {
                        gw->npc[i] = createBubble(68);
                        gw->activeNpc++;
                        break;
                    }
                }
            }
        }
    }

    //Oxygen control
    if(gw->player->oxygen > 0){
        if(gw->player->collision.y == globalWaterSurfaceHeight && gw->player->netTimer == 0) {
            if(gw->player->oxygen < MAX_OXYGEN) {
                gw->player->oxygen = fmin(gw->player->oxygen + 6 * delta, MAX_OXYGEN);
            }
        }
        else if(gw->player->collision.y + gw->player->collision.height / 2 < (globalPixelHeight * 2 / 3)) {
            gw->player->oxygen -= 3 * delta;
        }
        else {
            gw->player->oxygen -= 6 * delta;
        }
    }
    else{
        updateBestScore();
        gw->gameState = GAME_OVER;
    }

    //Update all NPCs
    for(int i = 0; i < MAX_NPC; i++) {
        //Only update NPC if it is currently active
        if(gw->npc[i] != NULL) {
            updateNpc(gw->npc[i], delta);

            //Checks if the NPC is marked for removal
            if(gw->npc[i]->shouldBeRemoved) {
                //Checks if the NPC should be removed in the current frame
                if(gw->npc[i]->removalCountdown <= 0) {
                    free(gw->npc[i]);
                    gw->npc[i] = NULL;
                    gw->activeNpc--;
                    continue;
                }
            }
            else {
                checkNpcCapture(gw, gw->player, gw->npc[i]);
                checkNpcCollision(gw->player, gw->npc[i]);

                //Checks if the NPC has escaped
                if(gw->npc[i]->collision.x + gw->npc[i]->collision.width < 0){
                    gw->npc[i]->shouldBeRemoved = true;
                    gw->npc[i]->removalCountdown = 0;

                    if(gw->npc[i]->type == NPC_GARBAGE) {
                        gw->escapedEnemies++;
                    }
                }
            }
        }
    }
}


/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw ) { //draws the gameworld with all its components

    BeginDrawing();

    drawBackground(gw->timer);

    drawPlayer(gw->player, gw->timer);

    for (int i = 0; i < MAX_NPC; i++) {
        if(gw->npc[i] != NULL) {
            if(gw->npc[i]->type == NPC_BUBBLE) {
                drawBubble(gw->npc[i]);
            }
            else {
                drawNpc(gw->npc[i]);
            }
        }
    }

    drawForeground(gw->timer);
    
    //Water surface height
    //DrawLine(0, globalWaterSurfaceHeight * currentWindowScale, GetScreenWidth(), globalWaterSurfaceHeight * currentWindowScale, BLUE);

    drawOxygenBar(gw->player);
    drawInGameScore();

    EndDrawing();

}

/**
 * @brief Draws the environment behind all entities.
 */
void drawBackground( float time ) {
    Texture2D* skyBg;
    Texture2D* cityBg;
    Texture2D* waterBg;
    Texture2D* floorBg;

    Rectangle source;
    Rectangle dest;
    Vector2 offset = {0, 0};

    int dayTimeInterval = 60;

    //Only changes textures in 60 second intervals
    if((int)time % dayTimeInterval == 0) {
        switch((int)(time / dayTimeInterval) % 4) {
            /*
            case 1:
                gameBg = &rm.skyBgAfternoon;
                cityBg = &rm.cityBgAfternoon;
                waterBg = &rm.waterBgAfternoon;
                floorBg = &rm.floorBgAfternoon;
                break;
            case 2:
                gameBg = &rm.skyBgNight;
                cityBg = &rm.cityBgNight;
                waterBg = &rm.waterBgNight;
                floorBg = &rm.floorBgNight;
                break;
                
            case 3:
                gameBg = &rm.skyBgAfternoon;
                cityBg = &rm.cityBgAfternoon;
                waterBg = &rm.waterBgAfternoon;
                floorBg = &rm.floorBgAfternoon;
                break;
            
            */

            default:
                skyBg = &rm.skyBgDay;
                cityBg = &rm.cityBgDay;
                waterBg = &rm.waterBg;
                floorBg = &rm.floorBg;
        }
    }
    
    //Sky
    source = (Rectangle){0, 0, 320, 64};
    dest = (Rectangle){0, 0, GetScreenWidth(), 64 * currentWindowScale};
    DrawTexturePro(*skyBg, source, dest, offset, 0, WHITE);

    //Cityscape
    source = (Rectangle){(int)time, 0, 320, 180};
    dest = (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()};
    DrawTexturePro(*cityBg, source, dest, offset, 0, WHITE);

    //Water
    dest = (Rectangle){0, 52 * currentWindowScale, GetScreenWidth(), 128 * currentWindowScale};
    source = (Rectangle){320 + (int)(time * 70), 0, 320, 128};
    DrawTexturePro(*waterBg, source, dest, offset, 0, WHITE);
    source = (Rectangle){(int)(time * 90), 0, 320, 128};
    DrawTexturePro(*waterBg, source, dest, offset, 0, WHITE);

    //Floor
    source = (Rectangle){(int)(time * 40), 0, 320, 64};
    dest = (Rectangle){0, 116 * currentWindowScale, GetScreenWidth(), 64 * currentWindowScale};
    DrawTexturePro(*floorBg, source, dest, offset, 0, WHITE);
}

/**
 * @brief Draws the environment in front of all entities.
 */
void drawForeground( float time ) {
    Rectangle source;
    Rectangle dest;
    Vector2 offset = {0, 0};

    //Foam
    source = (Rectangle){(int)(time * 90), 0, 320, 32};
    dest = (Rectangle){0, 52 * currentWindowScale, GetScreenWidth(), 32 * currentWindowScale};
    DrawTexturePro(rm.foamFg, source, dest, offset, 0, WHITE);

    //Bubbles
    source = (Rectangle){(int)(time * 100), 0, 320, 128};
    dest = (Rectangle){0, 52 * currentWindowScale, GetScreenWidth(), 128 * currentWindowScale};
    DrawTexturePro(rm.bubbleFg, source, dest, offset, 0, WHITE);

    //Floor
    source = (Rectangle){(int)(time * 110), 0, 320, 32};
    dest = (Rectangle){0, 148 * currentWindowScale, GetScreenWidth(), 32 * currentWindowScale};
    DrawTexturePro(rm.floorFg, source, dest, offset, 0, WHITE);
}