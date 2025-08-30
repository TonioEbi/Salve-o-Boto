#pragma once
#include "raylib/raylib.h"
#include <stdbool.h>

typedef struct Npc {
    Rectangle size;
    float speed;
    bool captured;
    bool enemy;
    bool dealtDamage;
}Npc;

Npc* createNpc(void);

void drawNpc(Npc* n);

void updateNpc(Npc *n, float delta);