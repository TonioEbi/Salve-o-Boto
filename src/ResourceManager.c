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
    //Misc. Images
    rm.icon = LoadImage("resources/images/icon.png");

    //Player
    rm.player = LoadTexture("resources/images/sprites/diver.png");
    rm.playerAttacking = LoadTexture("resources/images/sprites/diver_attacking.png");
    rm.oxyTank = LoadTexture( "resources/images/sprites/tank.png");

    //NPCs
    {
        char file[50];
        for(int i = 0; i < 17; i++) {
            //Loads all animal textures into the animal array
            snprintf(file, sizeof(file), "resources/images/sprites/npc/animal/type_%d.png", i);
            rm.animalArray[i] = LoadTexture(file);
        }
        
        for(int i = 0; i < 11; i++) {
            //Loads all animal textures into the animal array
            snprintf(file, sizeof(file), "resources/images/sprites/npc/enemy/type_%d.png", i);
            rm.enemyArray[i] = LoadTexture(file);
        }
    }

    rm.bubbleIdle = LoadTexture("resources/images/sprites/npc/bubble/bubble_idle.png");
    rm.bubblePop = LoadTexture("resources/images/sprites/npc/bubble/bubble_pop.png");
    rm.bubbleBreathe = LoadTexture("resources/images/sprites/npc/bubble/bubble_breathe.png");

    //Game BGs
    rm.sunBg = LoadTexture("resources/images/sprites/background/sunbg.png");
    rm.moonBg = LoadTexture("resources/images/sprites/background/moonbg.png");
    rm.cloudShadowBg = LoadTexture("resources/images/sprites/background/cloudshadowbg.png");
    rm.cloudHighlightBg = LoadTexture("resources/images/sprites/background/cloudhighlightbg.png");
    rm.cityscapeBg = LoadTexture("resources/images/sprites/background/cityscapebg.png");
    rm.cityOverlayBg = LoadTexture("resources/images/sprites/background/cityoverlaybg.png");
    rm.waterBg = LoadTexture("resources/images/sprites/background/waterbg.png");
    rm.floorBg = LoadTexture("resources/images/sprites/background/floorbg.png");

    //Game FGs
    rm.foamFg = LoadTexture("resources/images/sprites/background/foamfg.png");
    rm.bubbleFg = LoadTexture("resources/images/sprites/background/bubblefg.png");
    rm.floorFg = LoadTexture("resources/images/sprites/background/floorfg.png");

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
    //Misc. Images
    UnloadImage(rm.icon);

    //Player
    UnloadTexture(rm.player);
    UnloadTexture(rm.oxyTank);

    //NPCs
    for(int i = 0; i < 11; i ++){
    UnloadTexture(rm.enemyArray[i]);
    }
    for(int i = 0; i < 17; i++){
    UnloadTexture(rm.animalArray[i]);
    }

    UnloadTexture(rm.bubbleIdle);
    UnloadTexture(rm.bubblePop);
    UnloadTexture(rm.bubbleBreathe);

    //Game BGs
    UnloadTexture(rm.sunBg);
    UnloadTexture(rm.moonBg);
    UnloadTexture(rm.cloudShadowBg);
    UnloadTexture(rm.cloudHighlightBg);
    UnloadTexture(rm.cityscapeBg);
    UnloadTexture(rm.cityOverlayBg);
    UnloadTexture(rm.waterBg);
    UnloadTexture(rm.floorBg);

    //Game FGs
    UnloadTexture(rm.foamFg);
    UnloadTexture(rm.bubbleFg);
    UnloadTexture(rm.floorFg);

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