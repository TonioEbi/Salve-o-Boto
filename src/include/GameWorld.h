/**
 * @file GameWorld.h
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld struct and function declarations.
 * 
 * @copyright Copyright (c) 2025
 */
#pragma once
#include "Player.h"
#include "Npc.h"
#include "enums.h"
#include "Bubble.h"
#define MAX_NPC 1000

typedef struct GameWorld {
    Player *player;
    Npc *npc[MAX_NPC];
    int activeNpc;
    float timer;
    int timeCount;
    int lastSec;
    Bubble *bubble;
    State gameState;
} GameWorld;

/**
 * @brief Creates a dinamically allocated GameWorld struct instance.
 */
GameWorld* createGameWorld( void );

/**
 * @brief Destroys a GameWindow object and its dependecies.
 */
void destroyGameWorld( GameWorld *gw );

/**
 * @brief Reads user input and updates the state of the game.
 */
void updateGameWorld( GameWorld *gw, float delta );

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw );