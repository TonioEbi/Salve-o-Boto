#ifndef ENUMS_H  //Evita erros de redefinição de tipos, funções ou variáveis,  
#define ENUMS_H  //o conteúdo do header só será incluído uma vez por arquivo fonte.

typedef enum State {
    GAME_START,
    GAME_MENU,
    GAME_RUNNING,
    GAME_PAUSED,
    GAME_OVER,
    GAME_CREDITS,
    GAME_CONTROLS
} State;

#endif