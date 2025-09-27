#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

#include "GlobalVariables.h"
#include "Npc.h"
#include "enums.h"


void drawScoreboard(State s) {
    char scoreText[32];
    sprintf(scoreText, "%d", score) ;
    if (s == GAME_RUNNING) {
        DrawText(scoreText, GetScreenWidth() - 60, 15, 24, WHITE);
    } else if (s == GAME_OVER) {
        DrawText(scoreText, GetScreenWidth() / 2, GetScreenHeight() / 2 + 80, 24, WHITE);
    }
    
}

void updateScoreboard(State s) {
    drawScoreboard(s);    
}