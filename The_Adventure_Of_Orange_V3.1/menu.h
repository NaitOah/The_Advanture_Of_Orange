#ifndef MENU_H
#define MENU_H

#include "character.h"
#include "map.h"
#include "game.h"

void draw_main_menu(int selectedOption);
void draw_load_menu(int selectedOption, char saveFiles[][100], int numFiles);
void show_start_screen();
void show_main_menu(GameState *gameState, bool *running, bool *restart);  // 更新函数签名
void show_load_menu(GameState *gameState, bool *running, bool *restart);  // 更新函数签名

#endif
