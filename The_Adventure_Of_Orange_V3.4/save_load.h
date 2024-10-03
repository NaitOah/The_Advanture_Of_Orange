#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#include "game.h"

#define MAX_SAVES 5
#define SAVE_FOLDER "saves"

void ensure_save_dir_exists();
bool check_save_exists(int slot);
void save_game(GameState *gameState, int slot);
void load_game(GameState *gameState, int slot);
const char* get_save_time(int slot);
int get_oldest_save_slot(); // 添加声明
void delete_save(int slot); // 添加声明

#endif
