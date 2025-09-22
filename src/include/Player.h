#pragma once
#include "raylib/raylib.h"

typedef struct Player {
    Rectangle size;
    int oxigen;
    Vector2 speed;
    int score;
    Texture2D playerSpr;
} Player;

Player* createPlayer(void);

void updatePlayer(Player *p, float delta);

void drawPlayer(Player *p);

void drawOxigenBar(Player *p);