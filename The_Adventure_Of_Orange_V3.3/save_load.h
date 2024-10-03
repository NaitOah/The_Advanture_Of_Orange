#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#include "character.h"
#include "map.h"

#define MAX_SAVES 5
#define SAVE_FOLDER "saves"

typedef struct {
    FloorState floor1State;
    FloorState floor2State;
    Character player;
    int currentFloor;
} GameState;


bool check_save_exists(int slot);  // 修改返回类型为 bool
void save_game(GameState *gameState, int slot);
void load_game(GameState *gameState, int slot);
const char* get_save_time(int slot);
int get_oldest_save_slot();
void ensure_save_dir_exists();
void delete_save(int slot);

#endif
