#ifndef CHARACTER_H
#define CHARACTER_H

typedef struct {
    int x;
    int y;
    int hp;
    int attack;
    int hasSword; // ��ʾ����Ƿ��б���
    int gold;     // �����ֵ
    int keys;     // Կ����ֵ
    int hasGoldOrange; // ��ʾ����Ƿ��н�ɫ����
} Character;

#endif
