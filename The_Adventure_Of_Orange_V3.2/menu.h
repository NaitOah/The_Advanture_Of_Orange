#ifndef MENU_H
#define MENU_H

#include "character.h"
#include "map.h"
#include "game.h"

void draw_main_menu(int selectedOption);
void draw_load_menu(int selectedOption, char saveFiles[][100], int numFiles);
void draw_skin_menu(int selectedSkin, PIMAGE skin1Preview, PIMAGE skin2Preview); // 更新函数签名
void show_start_screen();
void show_main_menu(GameState *gameState, bool *running, bool *restart, int *selectedSkin);  // 更新函数签名
void show_load_menu(GameState *gameState, bool *running, bool *restart);  // 保持函数签名不变
void show_skin_menu(int *selectedSkin); // 更新函数签名

#endif
