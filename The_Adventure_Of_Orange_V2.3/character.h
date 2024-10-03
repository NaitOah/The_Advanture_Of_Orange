#ifndef CHARACTER_H
#define CHARACTER_H

typedef struct {
    int x;
    int y;
    int hp;
    int attack;
    int hasSword; // 增加标志以表示玩家是否有宝剑
    int gold;     // 增加金币数值
    int keys;     // 增加钥匙数值
    int hasGoldOrange; // 增加标志以表示玩家是否有金色橙子
} Character;

#endif
