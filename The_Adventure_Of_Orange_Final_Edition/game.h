#ifndef GAME_H
#define GAME_H

#include "character.h"
#include "map.h"

typedef struct {
    FloorState floor1State;
    FloorState floor2State;
    Character player;
    int currentFloor;
} GameState;

void initialize_game(GameState *gameState, bool newGame);
void game_loop(GameState *gameState, int skin);

#endif
