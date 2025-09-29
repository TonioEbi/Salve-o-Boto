#include <stdlib.h>
#include <stdbool.h>

#include "raylib/raylib.h"

#include "Npc.h"
#include "GlobalVariables.h"
#include "ResourceManager.h"

Npc* createNpc(float speed){ //creates the npc with the starting values
    Npc *n = (Npc*)malloc(sizeof(Npc));
    if (n == NULL) {
        return NULL;
    }

    n->removeOnNextFrame = false;
    n->removeOnCollision = false;
    n->type = GetRandomValue(0, 1); // 0 = Animal 1 = Garbage
    n->speed.x = speed;
    n->speed.y = 0;

   if(n->type == NPC_ANIMAL) {
    n->variant = GetRandomValue(0, 15);
    n->collision.width = 16;
    n->collision.height = 8;
    n->collisionOxygen = -10;
    n->captureOxygen = -20;
    n->captureScore = -1;
   }
   else{ //NPC_GARBAGE
    n->variant = GetRandomValue(0, 9);
    n->collision.width = 16;
    n->collision.height = 16;
    n->collisionOxygen = -20;
    n->captureOxygen = 10;
    n->captureScore = 1;
   }
   
   /*
    switch(n->variant) {
        default:
            n->collision.width = 16;
            n->collision.height = 8;
    }

    switch(n->type) {
        case NPC_ANIMAL:
            n->collisionOxygen = -10;
            n->captureOxygen = -20;
            n->captureScore = -1;
            break;

        default:
            n->collisionOxygen = -20;
            n->captureOxygen = 10;
            n->captureScore = 1;
    }
*/
    n->collision.x = globalPixelWidth;
    n->collision.y = (int)GetRandomValue((globalPixelHeight - n->collision.height), globalWaterSurfaceHeight);

    return n;
}

Npc* createBubble(float speed){ //creates a bubble with the starting values
    Npc *n = (Npc*)malloc(sizeof(Npc));
    if(n == NULL) {
        return NULL;
    }

    n->removeOnNextFrame = false;
    n->removeOnCollision = true;
    n->type = NPC_BUBBLE;

    n->collision.width = 16;
    n->collision.height = 16;
    n->speed.x = 0;
    n->speed.y = speed;

    n->collision.x = (int)GetRandomValue(globalPixelWidth / 2, globalPixelWidth - n->collision.width);
    n->collision.y = globalPixelHeight;

    n->collisionOxygen = 25;
    n->captureOxygen = 0;
    n->captureScore = 0;

    return n;
}

void drawNpc(Npc* n){ //draws the npc
    /*
    Descomente quando for colocar as texturas dos npcs
    */
    Texture2D texture;

    if(n->type == NPC_BUBBLE){
        texture = rm.bubbleIdle;
    }

   else if(n->type == NPC_GARBAGE) {
        texture = rm.enemyArray[n->variant];
    }
    else {
        texture = rm.animalArray[n->variant];
    }

    Rectangle source = {0, 0, (float)texture.width, (float)texture.height};
    Rectangle dest = {
        (int)(n->collision.x + n->collision.width / 2) * currentWindowScale,
        (int)(n->collision.y + n->collision.height / 2) * currentWindowScale,
        source.width * currentWindowScale,
        source.height * currentWindowScale
    };
    Vector2 offset = {8 * currentWindowScale, 8 * currentWindowScale};

    DrawTexturePro(texture, source, dest, offset, 0, WHITE);

 


    Color tint = {255, 255, 255, 0};
    /*Temporary collision display
    switch(n->type) {
        case NPC_ANIMAL:
            color = GREEN;
            break;

        case NPC_GARBAGE:
            color = RED;
            break;

        default:
            color = BLUE;
    } */

    DrawRectangle(
        n->collision.x * currentWindowScale,
        n->collision.y * currentWindowScale,
        n->collision.width * currentWindowScale,
        n->collision.height * currentWindowScale,
        tint
    );
}

void updateNpc(Npc *n, float delta){ //update the npc position and state
    if(n->type == NPC_BUBBLE) {
        //Bubble 
        n->collision.y -= n->speed.y * delta;
        if(n->collision.y < globalWaterSurfaceHeight) {
            n->removeOnNextFrame = true;
        }
    }
    else {
        //Animal or garbage
        n->collision.x -= n->speed.x * delta;
    }
}