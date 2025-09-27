#pragma once
#include "raylib/raylib.h"

#include "enums.h"

typedef struct Player {
    Rectangle collision;
    int oxygen;
    float damageCooldown;
    Vector2 speed;
    float netTimer;
    int netOffset;
    Vector2 netSize;
    Direction lastDir;
} Player;

Player* createPlayer(void);

void updatePlayer(Player *p, float delta);

void drawPlayer(Player *p);

void drawOxygenBar(Player *p);