#include "Menu.h"

static Texture2D menuBg;
static Texture2D menuCredits;
static Texture2D menuControls;

void initMenuAssets(void) 
{
    menuBg = LoadTexture("resources/images/menu_bg.png"); 
    menuCredits = LoadTexture("resources/images/menu_crdts.png");
    menuControls = LoadTexture("resources/images/menu_ctrls.png");
}

void unloadMenuAssets(void) 
{
    UnloadTexture(menuBg);
    UnloadTexture(menuControls);
    UnloadTexture(menuCredits);

}

void drawMainMenu(State *gameState) 
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawTexture(menuBg, 0, 0, WHITE);
     
    //area dos botoes 
    Rectangle btnControles = { 105, 305, 182, 63 };
    Rectangle btnJogar = { 309, 305, 182, 63 };
    Rectangle btnCreditos  = { 514, 306, 182, 63 };

    Vector2 mouse = GetMousePosition();

    //detecta clique e muda estado do jogo
     if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(mouse, btnJogar))
            {
            *gameState = GAME_RUNNING;
            }
        if (CheckCollisionPointRec(mouse, btnCreditos)) 
            {
            *gameState = GAME_CREDITS;
            }
        if (CheckCollisionPointRec(mouse, btnControles))
            {
                *gameState = GAME_CONTROLS;
            }
        }
    

    EndDrawing();
}

void drawMenuCredits(State *gameState) 
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawTexture(menuCredits, 0, 0, WHITE);
     
    Rectangle btnVoltar = { 30, 15, 200, 170 };
    
    Vector2 mouse = GetMousePosition();

     if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(mouse, btnVoltar))
        {
            *gameState = GAME_MENU;
        }
    }

    EndDrawing();
}

void drawMenuControls(State *gameState) 
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawTexture(menuControls, 0, 0, WHITE);
     
    Rectangle btnVoltar = { 30, 15, 200, 170 };
    
    Vector2 mouse = GetMousePosition();

     if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(mouse, btnVoltar))
        {
            *gameState = GAME_MENU;
        }
    }

    EndDrawing();
}    

void drawMenuGameOver( State *gameState) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    
    //DrawTexture() Vamo ter que criar a imagem do gameover ainda

    //Rectangle btnRecomecar = {}
    //Rectangle btnMenu = {}

    Vector2 mouse = GetMousePosition();

     /*if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(mouse, btnRecomecar))
        {
            *gameState = GAME_START;
        }
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(mouse, btnMenu))
        {
            *gameState = GAME_MENU;
        }
    } */

    EndDrawing();
}
