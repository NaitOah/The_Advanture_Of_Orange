#ifndef MAP_H
#define MAP_H

#include "character.h"

#define WIDTH 15
#define HEIGHT 15

// 地图元素
#define EMPTY 0
#define WALL 1
#define PLAYER 2
#define ENEMY 3
#define ENEMY_2 4
#define ITEM 5
#define SWORD 6
#define ORANGE 7
#define GOLD 8
#define DOOR 9
#define KEY 10
#define NPC_1 11
#define UP_STAIRS 15
#define DOWN_STAIRS 16

typedef struct {
    int map[HEIGHT][WIDTH];
    Character player;
    Character enemy;
    Character enemy2;
} FloorState;

void initialize_map(int map[HEIGHT][WIDTH], int floor);

#endif
