#pragma once
#include "raylib/raylib.h"
#include <stdbool.h>

typedef struct Npc {
    Rectangle collision;
    float speed;
    bool captured;
    bool enemy;
    int variant;
}Npc;

Npc* createNpc(void);

void drawNpc(Npc* n);

void updateNpc(Npc *n, float delta);