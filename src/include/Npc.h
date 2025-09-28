#pragma once
#include "raylib/raylib.h"
#include <stdbool.h>
#include "enums.h"

typedef struct Npc {
    Rectangle collision;
    NPCType type;
    Vector2 speed;
    bool removeOnNextFrame;
    bool removeOnCollision;
    int collisionOxygen;
    int captureOxygen;
    int captureScore;
    int variant;
}Npc;

Npc* createNpc(float speed);

Npc* createBubble(float speed);

void drawNpc(Npc* n);

void updateNpc(Npc *n, float delta);