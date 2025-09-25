#include <stdlib.h>
#include <stdbool.h>

#include "raylib/raylib.h"

#include "Npc.h"
#include "GlobalVariables.h"
#include "ResourceManager.h"

Npc* createNpc(void){ //creates the npc with the starting values
    Npc *n = (Npc*)malloc(sizeof(Npc));
    if (n == NULL) {
        return NULL;
    }

    n->collision.width = 16;
    n->collision.height = 8;
    n->speed = 60;

    n->collision.x = globalPixelWidth;
    n->collision.y = GetRandomValue((globalPixelHeight - n->collision.height), globalWaterSurfaceHeight);
    n->captured = false;
    n->enemy = GetRandomValue(0, 1);
    n->variant = GetRandomValue(0, 10);

    return n;
}

void drawNpc(Npc* n){ //draws the npc
    /*
    Descomente quando for colocar as texturas dos npcs

    Texture2D texture;
    if(n->type) {
        texture = rm.enemyArray[n->variant];
    }
    else {
        texture = rm.animalArray[n->variant];
    }

    Rectangle source = {0, 0, 16, 16};
    Rectangle dest = {
        (p->collision.x + p->collision.width / 2) * currentWindowScale,
        (p->collision.y + p->collision.height / 2) * currentWindowScale,
        source.width * currentWindowScale,
        source.height * currentWindowScale
    };
    Vector2 offset = {8 * currentWindowScale, 8 * currentWindowScale};

    DrawTexturePro(texture, source, dest, offset, 0, WHITE);

    */

    if(n->enemy){
        DrawRectangle(
            n->collision.x * currentWindowScale,
            n->collision.y * currentWindowScale,
            n->collision.width * currentWindowScale,
            n->collision.height * currentWindowScale,
            RED
        );
    }else{
        DrawRectangle(
            n->collision.x * currentWindowScale,
            n->collision.y * currentWindowScale,
            n->collision.width * currentWindowScale,
            n->collision.height * currentWindowScale,
            GREEN
        );
    }
}

void updateNpc(Npc *n, float delta){ //update the npc position and state
    if(n->captured){
        n = NULL;
    }
    else {
        n->collision.x -= n->speed * delta;
    }
}