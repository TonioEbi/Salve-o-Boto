#include "Player.h"
#include "Npc.h"
#include <stdbool.h>
#include "GameMechanics.h"
#include "raylib/raylib.h"
#include <stdio.h>

void checkCapture(Player* p, Npc* n){
    Rectangle netRec = {
        p->size.x + (p->size.width - p->netSize.x) / 2,
        p->size.y + (p->size.height - p->netSize.y) / 2,
        p->netSize.x,
        p->netSize.y
    };

    switch(p->lastDir) {
        case LEFT: netRec.x -= p->netOffset; break;
        default: netRec.x += p->netOffset;
    }

    if(CheckCollisionRecs(netRec, n->size)) {
        //Capture
        n->captured = true;

        //If the NPC is an enemy, the player scores. Otherwise, the player is punished.
        if(n->enemy){ 
            p->score++;
            p->oxygen += 10;
        }else{
            p->oxygen -=10; 
        }
    }
}

void playerBubbleInteract(Player* p, Bubble* b){
     if(CheckCollisionRecs(p->size, b->size) && !b->pop){
        if(p->oxygen < 100){
            p->oxygen += 20;
            if(p->oxygen > 100){
               p->oxygen = 100;
               
            }  
        } 
      b->pop = true;
    }

}