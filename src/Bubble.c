#include "raylib/raylib.h"
#include <stdbool.h>
#include "Bubble.h"
#include <stdlib.h>

Bubble* createBubble(void){
    Bubble *b = (Bubble*)malloc(sizeof(Bubble));
    if (b == NULL) {
        return NULL;
    }

    b->size.x = GetRandomValue(GetScreenWidth()/2, GetScreenWidth() - b->size.width);
    b->size.width = 45;
    b->size.height = 45;
    b->speed = 171;
    b->oxyregen = 25;
    b->size.y = GetScreenHeight();
    b->pop = false;
    
    return b;
}

void drawBubble(Bubble* b){
     
    DrawRectangle(b->size.x, b->size.y, b->size.width, b->size.height, BLUE);           

}

void updateBubble(Bubble *b, float delta){

     b->size.y -= b->speed * delta;

     if(b->size.y < GetScreenHeight()/3){

        b->pop = true;
    }

}