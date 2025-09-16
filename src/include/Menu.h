#include "enums.h"
#include "raylib/raylib.h"

//inclui e dps mata os assets
void initMenuAssets(void);
void unloadMenuAssets(void);

//desenha telas do menu e define funcoes dos botoes
void drawMainMenu(State *gameState);
void drawMenuCredits(State *gameState);
void drawMenuControls(State *gameState);