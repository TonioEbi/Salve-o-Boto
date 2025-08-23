#pragma once
#include "raylib/raylib.h"

typedef struct Player {
    Rectangle size;
    int life;
    Vector2 speed;
    int score;
} Player;

Player* createPlayer(void);

void updatePlayer(Player *p, float delta);

void drawPlayer(Player *p);