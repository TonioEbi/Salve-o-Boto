#include "raylib/raylib.h"
#include <stdbool.h>
#include "Npc.h"
#include <stdlib.h>

Npc* createNpc(void){ //creates the npc with the starting values
    Npc *n = (Npc*)malloc(sizeof(Npc));
    if (n == NULL) {
        return NULL;
    }

    n->size.width = 45;
    n->size.height = 15;
    n->speed = 150;

   /*
    //Creates the NPC from the left or right side of the screen
    int dir = GetRandomValue(0, 1);
    if(dir == 0) {
        n->size.x = -n->size.width;
    }
    else {
        n->size.x = GetScreenWidth();
        n->speed *= -1;
    }
*/
    n->size.x = GetScreenWidth();
    n->size.y = GetRandomValue((GetScreenHeight() - n->size.height), GetScreenHeight() / 3);
    n->captured = false;
    n->enemy = GetRandomValue(0, 1);

    return n;
}

void drawNpc(Npc* n){ //draws the npc
    if(n->enemy){
        DrawRectangle(n->size.x, n->size.y, n->size.width, n->size.height, RED);
    }else{
        DrawRectangle(n->size.x, n->size.y, n->size.width, n->size.height, GREEN);
    }
    
}

void updateNpc(Npc *n, float delta){ //update the npc position and state
    if(n->captured){
        n = NULL;
    }
    else {
        n->size.x -= n->speed * delta;
    }
}