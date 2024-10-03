#ifndef CHARACTER_H
#define CHARACTER_H

typedef struct {
    int x;
    int y;
    int hp;
    int attack;
    int hasSword; // 表示玩家是否有宝剑
    int gold;     // 金币数值
    int keys;     // 钥匙数值
    int hasGoldOrange; // 表示玩家是否有金色橙子
} Character;

#endif
