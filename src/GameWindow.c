#include <stdlib.h>
#include <stdbool.h>
#include "GameWindow.h"
#include "GameWorld.h"
#include "ResourceManager.h"
#include "raylib/raylib.h"
#include "Menu.h"


GameWindow* createGameWindow(
    int width, 
    int height, 
    const char *title, 
    int targetFPS,
    bool antialiasing, 
    bool resizable, 
    bool fullScreen,
    bool undecorated, 
    bool alwaysOnTop, 
    bool invisibleBackground, 
    bool alwaysRun, 
    bool loadResources, 
    bool initAudio ) {

    GameWindow *gw = (GameWindow*) malloc(sizeof(GameWindow));
    gw->width = width;
    gw->height = height;
    gw->title = title;
    gw->targetFPS = targetFPS;
    gw->antialiasing = antialiasing;
    gw->resizable = resizable;
    gw->fullScreen = fullScreen;
    gw->undecorated = undecorated;
    gw->alwaysOnTop = alwaysOnTop;
    gw->invisibleBackground = invisibleBackground;
    gw->alwaysRun = alwaysRun;
    gw->loadResources = loadResources;
    gw->initAudio = initAudio;
    gw->initialized = false;
    gw->gw = NULL;
    return gw;
}

void initGameWindow(GameWindow *gameWindow) {

    if (!gameWindow->initialized) {
        InitWindow(gameWindow->width, gameWindow->height, gameWindow->title);
        SetTargetFPS(gameWindow->targetFPS);
        gameWindow->gw = createGameWorld();
        gameWindow->initialized = true;
        gameWindow->gw->gameState = GAME_MENU; //jogo inicia no menu
    }

    initMenuAssets();

    //loop principal
    while (!WindowShouldClose()) {

        switch (gameWindow->gw->gameState) 
        {
            case GAME_MENU:
                drawMainMenu(&gameWindow->gw->gameState);
                break;

            case GAME_CREDITS:
                drawMenuCredits(&gameWindow->gw->gameState);
                break;

            case GAME_RUNNING:
                updateGameWorld(gameWindow->gw, GetFrameTime());
                drawGameWorld(gameWindow->gw);
                
                break;

            case GAME_CONTROLS:
                drawMenuControls(&gameWindow->gw->gameState);
                break;

            case GAME_OVER:
                drawMenuGameOver(&gameWindow->gw->gameState);
                break;

            case GAME_PAUSED:
                drawMenuPause(&gameWindow->gw->gameState);
                break;

            default:
                break;
        }
        
    }

    unloadMenuAssets();

    destroyGameWorld(gameWindow->gw);
    CloseWindow();
}

