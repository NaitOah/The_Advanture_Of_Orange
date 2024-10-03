#include <graphics.h>
#include <conio.h>
#include <ctime>
#include "map.h"
#include "character.h"
#include "game.h"

#define CELL_SIZE 50
#define STATUS_BAR_WIDTH 200
#define DIALOGUE_BOX_HEIGHT 0

int main() {
    srand(time(NULL)); // ��ʼ�������������
    initgraph(WIDTH * CELL_SIZE + STATUS_BAR_WIDTH, HEIGHT * CELL_SIZE + DIALOGUE_BOX_HEIGHT);

    show_start_screen(); // ��ʾ����ҳ��

    int map[HEIGHT][WIDTH];
    Character player = {1, 1, 3, 2, 0, 0, 0}; // ��ʼ��ʱ����������ֵ��������Ϊ2��û�б��������Ϊ0��Կ��Ϊ0����ɫ����Ϊ0
    Character enemy = {0, 0, 5, 3}; // ���˳�ʼ������ʼλ����Ч�����ڵ�ͼ������

    initialize_map(map);

    // ���ҵ���λ��
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (map[i][j] == ENEMY) {
                enemy.x = i;
                enemy.y = j;
                break;
            }
        }
    }

    PIMAGE playerImage = newimage();
    PIMAGE playerWithSwordImage = newimage();
    PIMAGE swordImage = newimage();
    PIMAGE heartImage = newimage();
    PIMAGE orangeImage = newimage();
    PIMAGE enemyImage = newimage();
    PIMAGE goldImage = newimage();
    PIMAGE wallImage = newimage();
    PIMAGE doorImage = newimage();
    PIMAGE keyImage = newimage();
    PIMAGE npc1Image = newimage();
    PIMAGE goldOrangeImage = newimage();

    // ����ͼƬ
    getimage(playerImage, "images/player.png");
    getimage(playerWithSwordImage, "images/player_with_sword.png");
    getimage(swordImage, "images/sword.png");
    getimage(heartImage, "images/heart.png");
    getimage(orangeImage, "images/orange.png");
    getimage(enemyImage, "images/enemy_1.png");
    getimage(goldImage, "images/gold.png");
    getimage(wallImage, "images/wall.png");
    getimage(doorImage, "images/door.png");
    getimage(keyImage, "images/key.png");
    getimage(npc1Image, "images/npc_1.png");
    getimage(goldOrangeImage, "images/gold_orange.png");

    while (1) {
        cleardevice();
        draw_map(map, player, enemy, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, goldImage, wallImage, doorImage, keyImage, npc1Image);
        draw_status_bar(player, playerImage, playerWithSwordImage, heartImage, goldOrangeImage);

        if (kbhit()) {
            char command = getch();
            switch (command) {
                case 'w': move_player(&player, -1, 0, map, &enemy, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, heartImage, goldImage, wallImage, doorImage, keyImage, npc1Image); break;
                case 'a': move_player(&player, 0, -1, map, &enemy, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, heartImage, goldImage, wallImage, doorImage, keyImage, npc1Image); break;
                case 's': move_player(&player, 1, 0, map, &enemy, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, heartImage, goldImage, wallImage, doorImage, keyImage, npc1Image); break;
                case 'd': move_player(&player, 0, 1, map, &enemy, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, heartImage, goldImage, wallImage, doorImage, keyImage, npc1Image); break;
                case 'e':
                    if (player.hasSword) {
                        player.hasSword = 0;
                        player.attack = 2; // ���¹�����
                        map[player.x][player.y] = SWORD; // ���������ڵ���
                    } else if (map[player.x][player.y] == SWORD) {
                        player.hasSword = 1;
                        player.attack = 5; // ���¹�����
                        map[player.x][player.y] = EMPTY; // ���𱦽�����ӵ�ͼ���Ƴ�
                    }
                    break; // װ��/ȡ�±���
                case 'u':
                    if (player.hasGoldOrange) {
                        player.hp = 6; // ����Ѫ���������ʼ���Ѫ��Ϊ5
                        player.hasGoldOrange = 0; // ʹ�ú��ɫ������ʧ
                    }
                    break;
                case 'f':
                    if (map[player.x][player.y] == NPC_1) {
                        trigger_dialogue(&player, map, npc1Image, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, goldImage, wallImage, doorImage, keyImage, heartImage);
                    }
                    break;
            }
        }
        Sleep(100); // ������Ϸ�ٶ�
    }

    closegraph();
    return 0;
}
