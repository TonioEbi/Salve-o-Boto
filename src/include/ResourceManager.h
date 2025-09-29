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
    //Misc. Images
   //    Image icon;

    //Player
    Texture2D player;
    Texture2D playerAttacking;
    Texture2D oxyTank;

    //NPCs
    Texture2D animalArray[16];
    Texture2D enemyArray[10];

    Texture2D bubbleIdle;
    Texture2D bubblePop;
    Texture2D bubbleBreathe;

    //Game BGs
    Texture2D skyBgDay;
    Texture2D cityBgDay;
    Texture2D waterBgDay;
    Texture2D floorBgDay;
    Texture2D skyBgAfternoon;
    Texture2D cityBgAfternoon;
    Texture2D waterBgAfternoon;
    Texture2D floorBgAfternoon;
    Texture2D skyBgNight;
    Texture2D cityBgNight;
    Texture2D waterBgNight;
    Texture2D floorBgNight;

    //Game FGs
    Texture2D foamFgDay;
    Texture2D foamFgAfternoon;
    Texture2D foamFgNight;

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
    
    Music bg_tune;
    
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