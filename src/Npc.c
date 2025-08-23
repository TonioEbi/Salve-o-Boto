#include "raylib/raylib.h"
#include <stdbool.h>
#include "Npc.h"
#include <stdlib.h>

Npc* createNpc(void){ //creates the npc with the starting values
    Npc *n = (Npc*)malloc(sizeof(Npc));
    if (n == NULL) {
        return NULL;
    }

    n->size.x = GetScreenWidth();
    n->size.width = 45;
    n->size.height = 15;
    n->size.y = GetRandomValue((GetScreenHeight() - n->size.height), GetScreenHeight() / 3);
    n->speed = 150;
    n->captured = false;
    n->enemy = GetRandomValue(0, 1);
    n->hostile = n->enemy ? false : (GetRandomValue(0,1));
    n->dealtDamage = false;

    return n;
}

void drawNpc(Npc* n){ //draws the npc
    if(n->enemy){
        DrawRectangle(n->size.x, n->size.y, n->size.width, n->size.height, RED);
    }else if(n->hostile) {
        DrawRectangle(n->size.x, n->size.y, n->size.width, n->size.height, PURPLE);
    }else{
        DrawRectangle(n->size.x, n->size.y, n->size.width, n->size.height, GREEN);
    }
    
}

void updateNpc(Npc *n, float delta){ //update the npc position and state
    n->size.x -= n->speed * delta;

    if(n->captured){
        n = NULL;
    }
}