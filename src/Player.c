#include "Player.h"
#include "raylib/raylib.h"
#include <stdlib.h>
#include <math.h>

Player * createPlayer(void){   // creates the player with the inicial settings

    Player *p = (Player*) malloc(sizeof(Player));
    if (p == NULL) {
        return NULL;
    }

    p->size.width = 132;
    p->size.height = 90;
    p->size.x = (GetScreenWidth() - p->size.width) / 2.0f ;
    p->size.y = GetScreenHeight() * 0.6f;
    p->oxygen = 100;
    p->speed.x = 300;
    p->speed.y = 300;
    p->score = 0;
    p->netTimer = 0;
    p->netOffset = 100;
    p->netSize = (Vector2){100, 100};
    p->lastDir = RIGHT;
    p->playerSpr = LoadTexture("resources/images/diver.png");

    return p;
}

void drawPlayer(Player *p){
    //Ensures the drawn sprite has the correct dimensions
    int res = 48;
    int scale = 3;
    Rectangle source = {0, 0, res, res};
    Rectangle dest = {p->size.x + p->size.width / 2, p->size.y + p->size.height / 2, source.width * scale, source.height * scale};
    Vector2 offset = {res / 2 * scale, res / 2 * scale};
    Color tint = {255, 255, 255, 255 * (1 - (int)(p->damageCooldown * 15) % 2)};

    Vector2 netPos = {p->size.x + (p->size.width - p->netSize.x) / 2, p->size.y + (p->size.height - p->netSize.y) / 2};

    switch(p->lastDir) {
        case LEFT:
            source.x += res;
            source.width *= -1;
            netPos.x -= p->netOffset;
            break;
        default:
            netPos.x += p->netOffset;
    }

    DrawTexturePro(p->playerSpr, source, dest, offset, 0, tint);

    //Temporary player collision display
    DrawRectangle(p->size.x, p->size.y, p->size.width, p->size.height, (Color){0, 255, 255, 63});
    //Temporary net collision display
    if(p->netTimer > 0.1) {
        DrawRectangle(netPos.x, netPos.y, p->netSize.x, p->netSize.y, (Color){255, 255, 0, 63});
    }
}

void updatePlayer(Player *p, float delta){
    //Damage cooldown (invincibility frames)
    if(p->damageCooldown > 0) {
        p->damageCooldown = fmax(0, p->damageCooldown - delta);
    }

    //Net attack timer
    if(p->netTimer > 0) {
        p->netTimer = fmax(0, p->netTimer - delta);
    }

    //Only use net if the timer is set to 0
    if(p->netTimer == 0 && (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_E))){
        p->netTimer = 0.5;
    }

    //player movement
    if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){
        p->size.x += p->speed.x * delta;
        p->lastDir = RIGHT;
    }
    if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)){
        p->size.x -= p->speed.x * delta;
        p->lastDir = LEFT;
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
    }else if(p->size.y < (GetScreenHeight() / 3)){
        p->size.y = (GetScreenHeight() / 3);
    }

}

void drawOxygenBar(Player *p){
    DrawRectangle(10, 10, 3 * p->oxygen, 30, DARKGREEN);
}