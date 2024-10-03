#ifndef GAME_H
#define GAME_H

#include "character.h"
#include "map.h"

void draw_status_bar(Character player, PIMAGE playerImage, PIMAGE playerWithSwordImage, PIMAGE heartImage, PIMAGE goldOrangeImage);
void draw_map(int map[HEIGHT][WIDTH], Character player, Character enemy, PIMAGE playerImage, PIMAGE playerWithSwordImage, PIMAGE swordImage, PIMAGE orangeImage, PIMAGE enemyImage, PIMAGE goldImage, PIMAGE wallImage, PIMAGE doorImage, PIMAGE keyImage, PIMAGE npc1Image, bool drawEnemy = true);
void draw_dialogue_box(const TCHAR* dialogue);
void draw_options(const TCHAR* option1, const TCHAR* option2);
void move_player(Character *player, int dx, int dy, int map[HEIGHT][WIDTH], Character *enemy, PIMAGE playerImage, PIMAGE playerWithSwordImage, PIMAGE swordImage, PIMAGE orangeImage, PIMAGE enemyImage, PIMAGE heartImage, PIMAGE goldImage, PIMAGE wallImage, PIMAGE doorImage, PIMAGE keyImage, PIMAGE npc1Image);
void show_start_screen();
void trigger_dialogue(Character *player, int map[HEIGHT][WIDTH], PIMAGE npc1Image, PIMAGE playerImage, PIMAGE playerWithSwordImage, PIMAGE swordImage, PIMAGE orangeImage, PIMAGE enemyImage, PIMAGE goldImage, PIMAGE wallImage, PIMAGE doorImage, PIMAGE keyImage, PIMAGE heartImage);

#endif
