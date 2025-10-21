#ifndef ENUMS_H  //Evita erros de redefinição de tipos, funções ou variáveis,  
#define ENUMS_H  //o conteúdo do header só será incluído uma vez por arquivo fonte.

typedef enum State {
    GAME_RESTART,
    GAME_MENU,
    GAME_MENU_RESET,
    GAME_RUNNING,
    GAME_RUNNING_RESET,
    GAME_PAUSED,
    GAME_OVER,
    GAME_CREDITS,
    GAME_MENU_CONTROLS,
    GAME_PAUSE_CONTROLS
} State;

typedef enum Direction {
    LEFT,
    RIGHT
} Direction;

typedef enum NPCType {
    NPC_ANIMAL = 0,
    NPC_GARBAGE = 1,
    NPC_BUBBLE = 2
} NPCType;

#endif