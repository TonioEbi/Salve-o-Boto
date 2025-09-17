#include "Player.h"
#include "Npc.h"
#include <stdbool.h>
#include "GameMechanics.h"
#include "raylib/raylib.h"
#include <stdio.h>

bool playerNpcCollision(Player* p, Npc* n){
    if(p->size.x + p->size.width > n->size.x){ //checks for frontal collision
        if(p->size.x < n->size.x + n->size.width){ //checks if the player is inside the npc space
            if(p->size.y + p->size.height > n->size.y){ //checks if the player is in the same route as the npc
                if(p->size.y < n->size.y + n->size.height){
                        
                    return true;
                }
            }
        }
    }
    return false;
}

void isCaptured(Player* p, Npc* n){
    if(playerNpcCollision(p, n)){
        if(IsKeyPressed(KEY_SPACE)){
            n->captured = true; //the player capture the npc as he colide with they and press the space bar
            if(n->enemy){ //checks if the npc is a enemy, if it is the player scores, if it ain't the player loses a life
                p->score++;
                p->oxigen += 10;
            }else{
                p->oxigen -=10; 
            }
        }
    }
}

void playerBubbleInteract(Player* p, Bubble* b){
     if(CheckCollisionRecs(p->size, b->size) && !b->pop){
        if(p->oxigen < 100){
            p->oxigen += 20;
            if(p->oxigen > 100){
               p->oxigen = 100;
               
            }  
        } 
      b->pop = true;
    }

}