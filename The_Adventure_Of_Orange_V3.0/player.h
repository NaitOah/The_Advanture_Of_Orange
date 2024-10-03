#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"
#include "map.h"

void move_player(Character *player, int dx, int dy, FloorState &floor1State, FloorState &floor2State, int &currentFloor, PIMAGE playerImage, PIMAGE playerWithSwordImage, PIMAGE swordImage, PIMAGE orangeImage, PIMAGE enemyImage, PIMAGE heartImage, PIMAGE goldImage, PIMAGE wallImage, PIMAGE doorImage, PIMAGE keyImage, PIMAGE npc1Image, PIMAGE upStairsImage, PIMAGE downStairsImage);
void trigger_dialogue(Character *player, int map[HEIGHT][WIDTH], PIMAGE npc1Image, PIMAGE playerImage, PIMAGE playerWithSwordImage, PIMAGE swordImage, PIMAGE orangeImage, PIMAGE enemyImage, PIMAGE goldImage, PIMAGE wallImage, PIMAGE doorImage, PIMAGE keyImage, PIMAGE heartImage, PIMAGE upStairsImage);

#endif
