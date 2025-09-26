#pragma once
#include "Player.h"
#include "Npc.h"
#include "Bubble.h"
#include <stdbool.h>

void checkCapture(GameWorld *gw, Player* p, Npc* n);

void playerBubbleInteract(Player* p, Bubble* b);