#ifndef CHARACTER_H
#define CHARACTER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int x;
    int y;
    int hp;
    int attack;
    int hasSword; // ���ӱ�־�Ա�ʾ����Ƿ��б���
    int gold;     // ���ӽ����ֵ
    int keys;     // ����Կ����ֵ
} Character;

#ifdef __cplusplus
}
#endif

#endif
