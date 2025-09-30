#pragma once

#include <stdbool.h>
#include "enums.h"

void drawInGameScore(void);
void drawBestScore(bool showLastScore);
void updateBestScore(void);
void drawOutlinedText(const char *text, int posX, int posY, int fontSize, Color color, Color outlineColor);