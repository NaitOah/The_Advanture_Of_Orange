#ifndef GAME_H
#define GAME_H

#include "character.h"
#include "map.h"
#include "draw.h"
#include "player.h"
#include "save_load.h"

void initialize_game(GameState *gameState, bool newGame);
void game_loop(GameState *gameState);

#endif
