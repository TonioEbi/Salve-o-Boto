#include "Menu.h"

static Texture2D menuBg;
static Texture2D menuCredits;
static Texture2D menuControls;
static Texture2D controlsButton;
static Texture2D playButton;
static Texture2D creditsButton;
static Texture2D backButton;


void initMenuAssets(void) 
{
    menuBg = LoadTexture("resources/images/menu_bg.png"); 
    menuCredits = LoadTexture("resources/images/menu_crdts.png");
    menuControls = LoadTexture("resources/images/menu_ctrls.png");
    controlsButton = LoadTexture("resources/images/controles.png");
    playButton = LoadTexture("resources/images/jogar.png");
    creditsButton = LoadTexture("resources/images/creditos.png");
    backButton = LoadTexture("resources/images/voltar.png");

}

void unloadMenuAssets(void) 
{
    UnloadTexture(menuBg);
    UnloadTexture(menuControls);
    UnloadTexture(menuCredits);
    UnloadTexture(controlsButton);
    UnloadTexture(playButton);
    UnloadTexture(creditsButton);

}

//desenho e animacao dos botoes
static void DrawButtonAnimation(Rectangle dimensions, Texture2D texture, Vector2 mouse, float scale) {
    if (CheckCollisionPointRec(mouse, dimensions)) {
        Rectangle scaledDest = {
            dimensions.x - (dimensions.width * (scale - 1.0f) / 2.0f),
            dimensions.y - (dimensions.height * (scale - 1.0f) / 2.0f),
            dimensions.width * scale,
            dimensions.height * scale
        };
        DrawTexturePro(texture, (Rectangle){ 0, 0, (float)texture.width, (float)texture.height }, scaledDest, (Vector2){ 0, 0 }, 0.0f, WHITE);
    } else {
        DrawTexture(texture, (int)dimensions.x, (int)dimensions.y, WHITE);
    }
}


void drawMainMenu(State *gameState) 
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawTexture(menuBg, 0, 0, WHITE);
     
    //area dos botoes 
    Rectangle btnControles = { 105, 305, 182, 63 };
    Rectangle btnJogar = { 309, 305, 182, 63 };
    Rectangle btnCreditos  = { 514, 305, 182, 63 };

    Vector2 mouse = GetMousePosition();
    float scale = 1.1f;

    //animacao dos botoes
    DrawButtonAnimation(btnJogar, playButton, mouse, scale);
    DrawButtonAnimation(btnCreditos, creditsButton, mouse, scale);
    DrawButtonAnimation(btnControles, controlsButton, mouse, scale);


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
     
    Rectangle btnVoltar = { 22, 17, (float)backButton.width, (float)backButton.height};
    Vector2 mouse = GetMousePosition();
    float scale = 1.1f;
    DrawButtonAnimation(btnVoltar, backButton, mouse, scale);

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
     
    Rectangle btnVoltar = { 22, 17, (float)backButton.width, (float)backButton.height};
    Vector2 mouse = GetMousePosition();
    float scale = 1.1f;
    DrawButtonAnimation(btnVoltar, backButton, mouse, scale);

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
