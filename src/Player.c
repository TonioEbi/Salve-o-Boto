#include "Player.h"
#include "raylib/raylib.h"
#include <stdlib.h>

static Texture2D playerspr;

Player * createPlayer(void){   // creates the player with the inicial settings

    Player *p = (Player*) malloc(sizeof(Player));
    if (p == NULL) {
        return NULL;
    }

    p->size.x = GetScreenWidth() / 8.0f;
    p->size.y = GetScreenHeight() * 0.85f;
    p->size.width = 135;
    p->size.height = 90;
    p->oxigen = 100;
    p->speed.x = 300;
    p->speed.y = 300;
    p->score = 0;

    return p;
}

void drawPlayer(Player *p){
    playerspr = LoadTexture("resources/images/diver.png");
    DrawTexture(playerspr, p->size.x, p->size.y, WHITE);
    
}

void updatePlayer(Player *p, float delta){

    //player movement
    if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){
        p->size.x += p->speed.x * delta;
    }
    if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)){
        p->size.x -= p->speed.x * delta;
    }
    if(IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)){
        p->size.y -= p->speed.y * delta;
    }
    if(IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)){
        p->size.y += p->speed.y * delta;
    }

    //player collision
    if(p->size.x < 0){
        p->size.x = 0;
    }else if(p->size.x + p->size.width > GetScreenWidth()){
        p->size.x = GetScreenWidth() - p->size.width;
    }

    if(p->size.y + p->size.height > GetScreenHeight()){
        p->size.y = GetScreenHeight() - p->size.height;
    }else if(p->size.y < (GetScreenHeight() / 3) - (p->size.height)){
        p->size.y = (GetScreenHeight() / 3) - (p->size.height);
    }

}

void drawOxigenBar(Player *p){
    DrawRectangle(10, 10, 3 * p->oxigen, 30, DARKGREEN);
}