#include <stdlib.h>
#include <stdbool.h>

#include "raylib/raylib.h"

#include "Bubble.h"
#include "GlobalVariables.h"
#include "ResourceManager.h"

Bubble* createBubble(void){
    Bubble *b = (Bubble*)malloc(sizeof(Bubble));
    if (b == NULL) {
        return NULL;
    }
    else {
        b->collision.width = 16;
        b->collision.height = 16;
        b->speed = 68;
        b->oxyregen = 25;
        b->collision.x = GetRandomValue(globalPixelWidth / 2, globalPixelWidth - b->collision.width);
        b->collision.y = globalPixelHeight;
        b->pop = false;
        
        return b;
    }
}

void drawBubble(Bubble* b){
    DrawRectangle(
        b->collision.x * currentWindowScale,
        b->collision.y * currentWindowScale,
        b->collision.width * currentWindowScale,
        b->collision.height * currentWindowScale,
        BLUE
    );
}

void updateBubble(Bubble *b, float delta){

     b->collision.y -= b->speed * delta;

     if(b->collision.y < globalWaterSurfaceHeight){

        b->pop = true;
    }

}