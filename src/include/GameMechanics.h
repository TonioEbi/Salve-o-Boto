#pragma once
#include "Player.h"
#include "Npc.h"
#include "Bubble.h"
#include <stdbool.h>

void checkCapture(Player* p, Npc* n);

void playerBubbleInteract(Player* p, Bubble* b);