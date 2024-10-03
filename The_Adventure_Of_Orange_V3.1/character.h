#ifndef CHARACTER_H
#define CHARACTER_H

#include "map.h"

typedef struct {
    int x;
    int y;
    int hp;
    int attack;
    int hasSword; // ���ӱ�־�Ա�ʾ����Ƿ��б���
    int gold;     // ���ӽ����ֵ
    int keys;     // ����Կ����ֵ
    int hasGoldOrange; // ���ӱ�־�Ա�ʾ����Ƿ��н�ɫ����
} Character;

typedef struct {
    int map[HEIGHT][WIDTH];
    Character player;
    Character enemy;
} FloorState;

#endif
