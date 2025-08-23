/**
 * @file GameWorld.h
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld implementation.
 * 
 * @copyright Copyright (c) 2025
 */
#include <stdio.h>
#include <stdlib.h>

#include "GameWorld.h"
#include "ResourceManager.h"

#include "raylib/raylib.h"

#include "Player.h"
#include "Npc.h"
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
    gw->activeNpc = 0;
    gw->timer = 0.0f;
    gw->timeCount = 0;
    gw->lastSec = 0;
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

    //timer logic that controls the enemies spawn
    int currentSec = (int)gw->timer;

    if (currentSec > gw->lastSec) {
        gw->timeCount++;
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
    }

    for (int i = 0; i < MAX_NPC; i++) {
        if (gw->npc[i] != NULL) {
            updateNpc(gw->npc[i], delta);
            if(playerNpcCollision(gw->player, gw->npc[i])){
                if(gw->npc[i]->hostile && !gw->npc[i]->dealtDamage){ //deals damage when the player have contact with an hostile npc and don't allow the same enemy to deal more damamge
                    gw->player->life--;
                    gw->npc[i]->dealtDamage = true;
                }
            }
            isCaptured(gw->player, gw->npc[i]); //checks if the npc was captured
        }
    }
}


/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw ) { //draws the gameworld with all its components

    BeginDrawing();
    ClearBackground(BLACK);

    for (int i = 0; i < MAX_NPC; i++) {
        if (gw->npc[i] != NULL && !gw->npc[i]->captured) {
            drawNpc(gw->npc[i]);
        }
    }

    drawPlayer(gw->player);

    DrawLine(0, GetScreenHeight() / 3, GetScreenWidth(), GetScreenHeight() / 3, BLUE);

    EndDrawing();

}