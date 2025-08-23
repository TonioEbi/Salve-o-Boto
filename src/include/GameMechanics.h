#pragma once
#include "Player.h"
#include "Npc.h"
#include <stdbool.h>

bool playerNpcCollision(Player* p, Npc* n);

void isCaptured(Player* p, Npc* n);