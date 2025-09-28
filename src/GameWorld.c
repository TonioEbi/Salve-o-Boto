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
#include "Bubble.h"
#include "GameMechanics.h"
#include "Scoreboard.h"



//#include "raylib/raymath.h"
//#define RAYGUI_IMPLEMENTATION    // to use raygui, comment these three lines.
//#include "raylib/raygui.h"       // other compilation units must only include
//#undef RAYGUI_IMPLEMENTATION     // raygui.h

/**
 * @brief Creates a dinamically allocated GameWorld struct instance.
 */
GameWorld* createGameWorld( State initialState ) { //initialize the gameworld with the initial values

    GameWorld *gw = (GameWorld*) malloc( sizeof( GameWorld ) );
    
    

    gw->player = createPlayer();
    for(int i = 0; i < MAX_NPC; i++){
        gw->npc[i] = NULL;
    }
    for(int i = 0; i < MAX_BUBBLE; i++){
        gw->bubble[i] = NULL;
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

    score = 0;

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
    gw->spawnTimer += delta;
    updatePlayer( gw->player, delta );

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
      if (gw->escapedEnemies >= ENEMY_ESCAPE_LIMIT || gw->caughtEnemies >= ENEMY_CAUGHT_LIMIT) {
        gw->npcSpeed += 4;
        gw->npcSpeed = fmin(gw->npcSpeed, MAX_NPC_SPEED);
        gw->spawnInterval = fmax(gw->spawnInterval - SPAWN_DECREMENT, MIN_SPAWN_INTERVAL);

        // Reset the counters
        gw->escapedEnemies = 0;
        gw->caughtEnemies = 0;
    }

        if(gw->BubbleTimer % 6 == 0){
            if(gw->activeBubble < MAX_BUBBLE){
            for (int i = 0; i < MAX_BUBBLE; i++){
                if(gw->bubble[i] == NULL){
                    gw->bubble[i] = createBubble();
                    gw->activeBubble++;
                    break;

                    }
                }
            }
        }

        //Oxygen control
        if(gw->player->oxygen > 0){
            if(gw->player->collision.y == globalWaterSurfaceHeight) {
                if(gw->player->oxygen < 100){
                    gw->player->oxygen = fmin(gw->player->oxygen + 2, 100);
                }
            }
            else if(gw->player->collision.y + gw->player->collision.height / 2 < (GetScreenHeight() * 2 / 3)) {
                gw->player->oxygen -= 3;
            }
            else {
                gw->player->oxygen -= 6;
            }
        }
        else{
            gw->gameState = GAME_OVER;
        }
    }

    //Update all NPCs

    for (int i = 0; i < MAX_NPC; i++) {

        //if (gw->npc[i] != NULL && !gw->npc[i]->captured) {
        if (gw->npc[i] != NULL) {
            updateNpc(gw->npc[i], delta);

        //Checks if the npc has escaped or been captured
            if(gw->npc[i]->collision.x <= 0 || gw->npc[i]->captured) {
                if (gw->npc[i]->enemy && gw->npc[i]->collision.x <= 0){
                    gw->escapedEnemies++;
                }

                free(gw->npc[i]);
                gw->npc[i] = NULL;
                gw->activeNpc--;

                continue;   
            }
            

            //Checks if the player is currently using the net
            if(gw->player->netTimer > 0 && gw->player->netTimer < 0.25 && gw->player->collision.y > globalWaterSurfaceHeight) {
                //Checks if the NPC was captured
                checkCapture(gw, gw->player, gw->npc[i]);
            }

            //Only deal damage to the player if the cooldown is 0
            if(gw->player->damageCooldown == 0) {
                //Checks if the NPC collided with the player
                if(CheckCollisionRecs(gw->player->collision, gw->npc[i]->collision)){
                    gw->player->damageCooldown = 1;
                    gw->player->oxygen -= 15;
                }
            }
        }
    }
    
    //Update all bubbles
    for(int i = 0; i < MAX_BUBBLE; i++){
        if(gw->bubble[i] != NULL){
            updateBubble(gw->bubble[i], delta);
            playerBubbleInteract(gw->player, gw->bubble[i]);
        }
    }

    updateScoreboard(gw->gameState);
}


/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw ) { //draws the gameworld with all its components

    BeginDrawing();

    drawBackground(gw->timer);

    drawPlayer(gw->player, gw->timer);

    for (int i = 0; i < MAX_NPC; i++) {
        if (gw->npc[i] != NULL && !gw->npc[i]->captured) {
            drawNpc(gw->npc[i]);
        }
    }
    
    for(int i = 0; i < MAX_BUBBLE; i++){
      if(gw->bubble[i] != NULL && !gw->bubble[i]->pop){
         drawBubble(gw->bubble[i]);
        }
    }

    drawForeground(gw->timer);
    
    //Water surface height
    //DrawLine(0, globalWaterSurfaceHeight * currentWindowScale, GetScreenWidth(), globalWaterSurfaceHeight * currentWindowScale, BLUE);

    drawOxygenBar(gw->player);
    drawScoreboard(gw->gameState);

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
                waterBg = &rm.waterBgDay;
                floorBg = &rm.floorBgDay;
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
    source = (Rectangle){320 + (int)(time * 75), 0, 320, 128};
    DrawTexturePro(*waterBg, source, dest, offset, 0, WHITE);
    source = (Rectangle){(int)(time * 100), 0, 320, 128};
    DrawTexturePro(*waterBg, source, dest, offset, 0, WHITE);

    //Floor
    source = (Rectangle){(int)(time * 40), 0, 320, 32};
    dest = (Rectangle){0, 148 * currentWindowScale, GetScreenWidth(), 32 * currentWindowScale};
    DrawTexturePro(*floorBg, source, dest, offset, 0, WHITE);
}

/**
 * @brief Draws the environment in front of all entities.
 */
void drawForeground( float time ) {
    Texture2D* foamFg;

    Rectangle source;
    Rectangle dest;
    Vector2 offset = {0, 0};

    int dayTimeInterval = 60;

    //Only changes textures in 60 second intervals
    if((int)time % dayTimeInterval == 0) {
        switch((int)(time / dayTimeInterval) % 4) {
            /*
            case 1:
                foamFg = &rm.foamFgAfternoon;
                break;
            case 2:
                foamFg = &rm.foamFgNight;
                break;
                
            case 3:
                foamFg = &rm.foamFgAfternoon;
                break;
            
            */

            default:
                foamFg = &rm.foamFgDay;
        }
    }

    //Foam
    source = (Rectangle){(int)(time * 100), 0, 320, 32};
    dest = (Rectangle){0, 52 * currentWindowScale, GetScreenWidth(), 32 * currentWindowScale};
    DrawTexturePro(*foamFg, source, dest, offset, 0, WHITE);
}