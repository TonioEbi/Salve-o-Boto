/**
 * @file ResourceManager.h
 * @author Prof. Dr. David Buzatto
 * @brief ResourceManager struct and function declarations.
 * 
 * @copyright Copyright (c) 2025
 */
#pragma once

#include "raylib/raylib.h"

typedef struct ResourceManager {
    //Player
    Texture2D player;

    //NPCs
    Texture2D animalArray[10];
    Texture2D enemyArray[10];

    //Menus
    Texture2D menuBg; 
    Texture2D menuCredits;
    Texture2D menuControls;
    Texture2D menuGameOver;
    Texture2D menuPause;

    //Botões
    Texture2D controlsButton;
    Texture2D playButton;
    Texture2D creditsButton;
    Texture2D backButton;
    Texture2D menuButton;
    Texture2D againButton;
    Texture2D backButton2;

    //Sound soundExample;
    //Music musicExample;
} ResourceManager;

/**
 * @brief Global ResourceManager instance.
 */
extern ResourceManager rm;

/**
 * @brief Load global game resources, linking them in the global instance of
 * ResourceManager called rm.
 */
void loadResourcesResourceManager( void );

/**
 * @brief Unload global game resources.
 */
void unloadResourcesResourceManager( void );