#pragma once
#include "raylib/raylib.h"

typedef enum Direction {
    LEFT,
    RIGHT
} Direction;

typedef struct Player {
    Rectangle size;
    int oxygen;
    float damageCooldown;
    Vector2 speed;
    int score;
    float netTimer;
    int netOffset;
    Vector2 netSize;
    Direction lastDir;
    Texture2D playerSpr;
} Player;

Player* createPlayer(void);

void updatePlayer(Player *p, float delta);

void drawPlayer(Player *p);

void drawOxygenBar(Player *p);