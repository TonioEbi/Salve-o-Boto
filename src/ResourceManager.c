/**
 * @file ResourceManager.c
 * @author Prof. Dr. David Buzatto
 * @brief ResourceManager implementation.
 * 
 * @copyright Copyright (c) 2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ResourceManager.h"
#include "raylib/raylib.h"

ResourceManager rm = {0};

void loadResourcesResourceManager(void) {
    //Player
    rm.player = LoadTexture("resources/images/sprites/diver.png");
    rm.playerAttacking = LoadTexture("resources/images/sprites/diver_attacking.png");
    rm.oxyTank = LoadTexture( "resources/images/sprites/tank.png");

    /*
    Descomente quando for colocar as texturas dos animais e do lixo
    Simplesmente inclua arquivos nomeados "type_0.png", "type_1.png" e assim por diante, até o "type_10.png" nas pastas apropriadas

    //NPCs
    {
        char file[36];
        for(int i = 0; i < 10; i++) {
            //Loads all animal textures into the animal array
            snprintf(file, 36, "resources/images/animal/type_%d.png", i);
            rm.animalArray[i] = LoadTexture(file);

            //Loads all animal textures into the animal array
            snprintf(file, 36, "resources/images/enemy/type_%d.png", i);
            rm.enemyArray[i] = LoadTexture(file);
        }
    }

    */

    //Game BGs
    rm.skyBgDay = LoadTexture("resources/images/sprites/background/skybg_day.png");
    rm.cityBgDay = LoadTexture("resources/images/sprites/background/citybg_day.png");
    rm.waterBgDay = LoadTexture("resources/images/sprites/background/waterbg_day.png");
    rm.floorBgDay = LoadTexture("resources/images/sprites/background/floorbg_day.png");
    /*
    rm.skyBgAfternoon;
    rm.cityBgAfternoon;
    rm.waterBgAfternoon;
    rm.floorBgAfternoon;
    rm.skyBgNight;
    rm.cityBgNight;
    rm.waterBgNight;
    rm.floorBgNight;
    */

    //Game FGs
    rm.foamFgDay = LoadTexture("resources/images/sprites/background/foamfg_day.png");
    /*
    rm.foamFgAfternoon;
    rm.foamFgNight;
    */

    //Menus
    rm.menuBg = LoadTexture("resources/images/ui/menu_bg.png"); 
    rm.menuCredits = LoadTexture("resources/images/ui/menu_crdts.png");
    rm.menuControls = LoadTexture("resources/images/ui/menu_ctrls.png");
    rm.menuGameOver = LoadTexture("resources/images/ui/menu_gmov.png");
    rm.menuPause = LoadTexture("resources/images/ui/menu_pause.png");

    //Buttons
    rm.controlsButton = LoadTexture("resources/images/ui/controles.png");
    rm.playButton = LoadTexture("resources/images/ui/jogar.png");
    rm.creditsButton = LoadTexture("resources/images/ui/creditos.png");
    rm.backButton = LoadTexture("resources/images/ui/voltar.png");
    rm.menuButton = LoadTexture("resources/images/ui/bt_menu.png");
    rm.againButton = LoadTexture("resources/images/ui/denovo.png");
    rm.backButton2 = LoadTexture("resources/images/ui/voltar2.png");

    //rm.soundExample = LoadSound( "resources/sfx/powerUp.wav" );
    
    rm.bg_tune = LoadMusicStream( "resources/musics/Hydrodinamics.mp3" );
}

void unloadResourcesResourceManager(void) {
    //Player
    UnloadTexture(rm.player);
    UnloadTexture(rm.oxyTank);

    //Menus
    UnloadTexture(rm.menuBg);
    UnloadTexture(rm.menuControls);
    UnloadTexture(rm.menuCredits);
    UnloadTexture(rm.menuGameOver);
    UnloadTexture(rm.menuPause);

    //Buttons
    UnloadTexture(rm.controlsButton);
    UnloadTexture(rm.playButton);
    UnloadTexture(rm.creditsButton);
    UnloadTexture(rm.menuButton);
    UnloadTexture(rm.againButton);
    UnloadTexture(rm.backButton2);

    //UnloadSound( rm.soundExample );
    
    UnloadMusicStream( rm.bg_tune );
}