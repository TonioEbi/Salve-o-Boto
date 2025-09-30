#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "raylib/raylib.h"

#include "Score.h"
#include "GlobalVariables.h"
#include "enums.h"

bool isNewBest = true;

void drawInGameScore(void) {
    char scoreText[32];
    sprintf(scoreText, "%d", score);

    Vector2 textOffset = MeasureTextEx(GetFontDefault(), scoreText, 10, 1);
    textOffset.x = (int)textOffset.x;
    textOffset.y = (int)(textOffset.y / 2);

    int x = (globalPixelWidth - 16 - textOffset.x) * currentWindowScale;
    int y = (globalPixelHeight - 16 - textOffset.y) * currentWindowScale;
    drawOutlinedText(scoreText, x, y, 10 * currentWindowScale, WHITE, BLACK);
}

void drawBestScore(bool showLastScore) {
    Vector2 textOffset;
    int x;
    int y;

    char best[32] = "Melhor: ";
    Color color = WHITE;
    char bestScoreText[11];
    sprintf(bestScoreText, "%d", hiscore);
    strcat(best, bestScoreText);

    if(showLastScore) {
        char scoreText[11];
        sprintf(scoreText, "%d", score);

        textOffset = MeasureTextEx(GetFontDefault(), scoreText, 10, 1);
        textOffset.x = (int)(textOffset.x / 2);
        textOffset.y = (int)(textOffset.y / 2);
        x = (globalPixelWidth / 2 - textOffset.x) * currentWindowScale;
        y = (globalPixelHeight - 32 - textOffset.y) * currentWindowScale;

        if(isNewBest) {
            sprintf(best, "Novo melhor!");
            color = GREEN;
        }

        drawOutlinedText(scoreText, x, y, 10 * currentWindowScale, WHITE, BLACK);
    }

    textOffset = MeasureTextEx(GetFontDefault(), best, 10, 1);
    textOffset.x = (int)(textOffset.x / 2);
    textOffset.y = (int)(textOffset.y / 2);

    x = (globalPixelWidth / 2 - textOffset.x) * currentWindowScale;
    y = (globalPixelHeight - 16 - textOffset.y) * currentWindowScale;
    drawOutlinedText(best, x, y, 10 * currentWindowScale, color, BLACK);
}

void updateBestScore(void) {
    if(score > hiscore) {
        hiscore = score;
        isNewBest = true;
    }
    else {
        isNewBest = false;
    }
}

void drawOutlinedText(const char *text, int posX, int posY, int fontSize, Color color, Color outlineColor) {
    int offset = fontSize / 10;

    DrawText(text, posX - offset, posY - offset, fontSize, outlineColor);
    DrawText(text, posX, posY - offset, fontSize, outlineColor);
    DrawText(text, posX + offset, posY - offset, fontSize, outlineColor);
    DrawText(text, posX - offset, posY, fontSize, outlineColor);
    DrawText(text, posX + offset, posY, fontSize, outlineColor);
    DrawText(text, posX - offset, posY + offset, fontSize, outlineColor);
    DrawText(text, posX, posY + offset, fontSize, outlineColor);
    DrawText(text, posX + offset, posY + offset, fontSize, outlineColor);
    DrawText(text, posX, posY, fontSize, color);
}