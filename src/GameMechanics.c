#include "Player.h"
#include "Npc.h"
#include "GameWorld.h"
#include "GlobalVariables.h"
#include <stdbool.h>
#include "GameMechanics.h"
#include "raylib/raylib.h"
#include <stdio.h>

void checkCapture(GameWorld *gw, Player* p, Npc* n){
    Rectangle netRec = {
        p->collision.x + (p->collision.width - p->netSize.x) / 2,
        p->collision.y + (p->collision.height - p->netSize.y) / 2,
        p->netSize.x,
        p->netSize.y
    };

    switch(p->lastDir) {
        case LEFT: netRec.x -= p->netOffset; break;
        default: netRec.x += p->netOffset;
    }

    if(CheckCollisionRecs(netRec, n->collision)) {
        //Capture
        n->captured = true;

        //If the NPC is an enemy, the player scores. Otherwise, the player is punished.
        if(n->enemy){ 
            score++;
            p->oxygen += 10;
            gw->caughtEnemies++;
        }else{
            p->oxygen -=10; 
        }
    }
}

void playerBubbleInteract(Player* p, Bubble* b){
     if(CheckCollisionRecs(p->collision, b->collision) && !b->pop){
        if(p->oxygen < 100){
            p->oxygen += 20;
            if(p->oxygen > 100){
               p->oxygen = 100;
               
            }  
        } 
      b->pop = true;
    }

}