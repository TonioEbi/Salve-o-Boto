#include <stdlib.h>
#include <math.h>

#include "raylib/raylib.h"

#include "Player.h"
#include "GlobalVariables.h"
#include "ResourceManager.h"

Player * createPlayer(void){   // creates the player with the inicial settings

    Player *p = (Player*) malloc(sizeof(Player));
    if (p == NULL) {
        return NULL;
    }

    p->collision.width = 60;
    p->collision.height = 40;
    p->collision.x = (globalPixelWidth - p->collision.width) / 2.0f ;
    p->collision.y = globalPixelHeight * 0.6f;
    p->oxygen = 100;
    p->speed.x = 120;
    p->speed.y = 120;
    p->score = 0;
    p->netTimer = 0;
    p->netOffset = 48;
    p->netSize = (Vector2){48, 48};
    p->lastDir = RIGHT;

    return p;
}

void drawPlayer(Player *p){
    //Ensures the drawn sprite has the correct dimensions
    int res = 64;
    Rectangle source = {0, 0, res, res};
    Rectangle dest = {
        (p->collision.x + p->collision.width / 2) * currentWindowScale,
        (p->collision.y + p->collision.height / 2) * currentWindowScale,
        source.width * currentWindowScale,
        source.height * currentWindowScale
    };
    Vector2 offset = {res / 2 * currentWindowScale, res / 2 * currentWindowScale};
    Color tint = {255, 255, 255, 255 * (1 - (int)(p->damageCooldown * 15) % 2)};

    Vector2 netPos = {
        p->collision.x + (p->collision.width - p->netSize.x) / 2,
        p->collision.y + (p->collision.height - p->netSize.y) / 2
    };

    switch(p->lastDir) {
        case LEFT:
            source.x += res;
            source.width *= -1;
            netPos.x -= p->netOffset;
            break;
        default:
            netPos.x += p->netOffset;
    }

    DrawTexturePro(rm.player, source, dest, offset, 0, tint);

    //Temporary player collision display
    DrawRectangle(
        p->collision.x * currentWindowScale,
        p->collision.y * currentWindowScale,
        p->collision.width * currentWindowScale,
        p->collision.height * currentWindowScale,
        (Color){0, 255, 255, 63}
    );
    //Temporary net collision display
    if(p->netTimer > 0.1) {
        DrawRectangle(
            netPos.x * currentWindowScale,
            netPos.y * currentWindowScale,
            p->netSize.x * currentWindowScale,
            p->netSize.y * currentWindowScale,
            (Color){255, 255, 0, 63}
        );
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

    //Player movement
    if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){
        p->collision.x += p->speed.x * delta;
        p->lastDir = RIGHT;
    }
    if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)){
        p->collision.x -= p->speed.x * delta;
        p->lastDir = LEFT;
    }
    if(IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)){
        p->collision.y -= p->speed.y * delta;
    }
    if(IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)){
        p->collision.y += p->speed.y * delta;
    }

    if(p->oxygen >= 100){
       p->oxygen = 100;
    }

    //Border collision
    p->collision.x = fmin(fmax(0, p->collision.x), globalPixelWidth - p->collision.width);
    p->collision.y = fmin(fmax(globalWaterSurfaceHeight, p->collision.y), globalPixelHeight - p->collision.height);
}

void drawOxygenBar(Player *p){
    DrawRectangle(
        8 * currentWindowScale,
        8 * currentWindowScale,
        p->oxygen * currentWindowScale,
        10 * currentWindowScale,
        DARKGREEN
    );
}