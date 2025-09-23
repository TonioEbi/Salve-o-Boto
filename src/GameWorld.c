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

#include "GameWorld.h"
#include "ResourceManager.h"

#include "raylib/raylib.h"

#include "Player.h"
#include "Npc.h"
#include "Bubble.h"
#include "GameMechanics.h"

//#include "raylib/raymath.h"
//#define RAYGUI_IMPLEMENTATION    // to use raygui, comment these three lines.
//#include "raylib/raygui.h"       // other compilation units must only include
//#undef RAYGUI_IMPLEMENTATION     // raygui.h

/**
 * @brief Creates a dinamically allocated GameWorld struct instance.
 */
GameWorld* createGameWorld( void ) { //inicialize the gameworld with the inicial values

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
    gw->timeCount = 0;
    gw->lastSec = 0;
    gw->BubbleTimer = 0;
    gw->activeBubble = 0;
    gw->gameState = GAME_RUNNING;
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
    
    for(int i = 0; i < MAX_BUBBLE; i++){
        if(gw->bubble[i] != NULL){
            updateBubble(gw->bubble[i], delta);
            playerBubbleInteract(gw->player, gw->bubble[i]);
        }
        
    }

    //timer logic that controls the enemies spawn
    int currentSec = (int)gw->timer;

    if (currentSec > gw->lastSec) {
        gw->timeCount++;
        gw->BubbleTimer++;
        gw->lastSec = currentSec;
        if (gw->activeNpc < MAX_NPC) {
            for (int i = 0; i < MAX_NPC; i++) {
                if (gw->npc[i] == NULL) {
                    gw->npc[i] = createNpc();
                    gw->activeNpc++;
                    break;                   
                }
            }
        }

        //Oxygen control
        if(gw->player->oxygen > 0){
            if(gw->player->size.y == GetScreenHeight() / 3) {
                if(gw->player->oxygen < 100){
                    gw->player->oxygen = fmin(gw->player->oxygen + 2, 100);
                }
            }
            else if(gw->player->size.y + gw->player->size.height / 2 < (GetScreenHeight() * 2 / 3)) {
                gw->player->oxygen -= 3;
            }
            else {
                gw->player->oxygen -= 6;
            }
        }
        else{
            gw->gameState = GAME_OVER;
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

    }

   
    for (int i = 0; i < MAX_NPC; i++) {
        if (gw->npc[i] != NULL && !gw->npc[i]->captured) {
            updateNpc(gw->npc[i], delta);

            //Checks if the player is currently using the net
            if(gw->player->netTimer > 0.1) {
                //Checks if the NPC was captured
                checkCapture(gw->player, gw->npc[i]);
            }

            //Only deal damage to the player if the cooldown is 0
            if(gw->player->damageCooldown == 0) {
                //Checks if the NPC collided with the player
                if(CheckCollisionRecs(gw->player->size, gw->npc[i]->size)){
                    gw->player->damageCooldown = 1;
                    gw->player->oxygen -= 10;
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
    ClearBackground((Color){ 16, 62, 87, 255 });

    for (int i = 0; i < MAX_NPC; i++) {
        if (gw->npc[i] != NULL && !gw->npc[i]->captured) {
            drawNpc(gw->npc[i]);
        }
    }

    drawPlayer(gw->player);
    
    for(int i = 0; i < MAX_BUBBLE; i++){
      if(gw->bubble[i] != NULL && !gw->bubble[i]->pop){
         drawBubble(gw->bubble[i]);

        }
        
    }
    
    DrawLine(0, GetScreenHeight() / 3, GetScreenWidth(), GetScreenHeight() / 3, BLUE);

    drawOxygenBar(gw->player);

    EndDrawing();

}
