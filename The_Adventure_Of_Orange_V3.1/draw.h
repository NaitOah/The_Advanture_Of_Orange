#ifndef DRAW_H
#define DRAW_H

#include "character.h"
#include "map.h"
#include <graphics.h>

#define DIALOGUE_BOX_HEIGHT 0 // 添加这一行定义 DIALOGUE_BOX_HEIGHT

void draw_status_bar(Character player, PIMAGE playerImage, PIMAGE playerWithSwordImage, PIMAGE heartImage, PIMAGE goldOrangeImage);
void draw_map(int map[HEIGHT][WIDTH], Character player, Character enemy, PIMAGE playerImage, PIMAGE playerWithSwordImage, PIMAGE swordImage, PIMAGE orangeImage, PIMAGE enemyImage, PIMAGE goldImage, PIMAGE wallImage, PIMAGE doorImage, PIMAGE keyImage, PIMAGE npc1Image, PIMAGE upStairsImage, PIMAGE downStairsImage, bool drawEnemy);
void draw_dialogue_box(const TCHAR* dialogue);
void draw_options(const TCHAR* option1, const TCHAR* option2);
void draw_save_confirmation(int selectedOption);
void draw_save_success();
void draw_exit_confirmation(int selectedOption);

#endif
