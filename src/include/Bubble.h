#pragma once
#include "raylib/raylib.h"
#include <stdbool.h>

typedef struct Bubble {
     
    Rectangle size;
    float speed;
    int oxyregen;
    bool pop; 

} Bubble;

Bubble* createBubble(void);

void drawBubble(Bubble* b);

void updateBubble(Bubble *b, float delta);


