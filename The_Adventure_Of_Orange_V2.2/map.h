#ifndef MAP_H
#define MAP_H

#ifdef __cplusplus
extern "C" {
#endif

#define WIDTH 15
#define HEIGHT 15

// 地图元素
#define EMPTY 0
#define WALL 1
#define PLAYER 2
#define ENEMY 3
#define ITEM 4
#define SWORD 5
#define ORANGE 6
#define GOLD 7
#define DOOR 8
#define KEY 9

void initialize_map(int map[HEIGHT][WIDTH]);

#ifdef __cplusplus
}
#endif

#endif
