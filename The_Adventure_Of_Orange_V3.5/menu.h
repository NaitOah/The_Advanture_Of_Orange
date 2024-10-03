#ifndef MENU_H
#define MENU_H

#include "character.h"
#include "map.h"

#define MAX_SAVES 5
#define SAVE_FOLDER "saves"
#define MUSIC_FOLDER "music"

#include "game.h"

void draw_main_menu(int selectedOption);
void draw_load_menu(int selectedOption, char saveFiles[][100], int numFiles);
void draw_other_menu(int selectedOption);
void draw_music_menu(int selectedOption, const char* musicFiles[], int numFiles);
void draw_skin_menu(int selectedOption, int selectedSkin); // 添加这个声明
void show_start_screen();
void show_main_menu(GameState *gameState, bool *running, bool *restart, int *selectedSkin);
void show_load_menu(GameState *gameState, bool *running, bool *restart);
void show_other_menu();
void show_music_menu();
void play_music(const char *filename);
void show_skin_menu(int *selectedSkin);

#endif
