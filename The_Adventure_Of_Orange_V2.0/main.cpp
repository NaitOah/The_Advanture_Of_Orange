#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <tchar.h> // ���ڴ��� _T ��
#include <stdlib.h> // �������������
#include <time.h>   // ����ʱ���ȡ

#define WIDTH 15
#define HEIGHT 15
#define CELL_SIZE 50
#define STATUS_BAR_WIDTH 200

// ��ͼԪ��
#define EMPTY 0
#define WALL 1
#define PLAYER 2
#define ENEMY 3
#define ITEM 4
#define SWORD 5
#define ORANGE 6
#define GOLD 7

// ��Һ͵��˽ṹ��
typedef struct {
    int x;
    int y;
    int hp;
    int attack;
    int hasSword; // ���ӱ�־�Ա�ʾ����Ƿ��б���
    int gold;     // ���ӽ����ֵ
} Character;

// ��ʼ����ͼ
void initialize_map(int map[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT-1 || j == 0 || j == WIDTH-1) {
                map[i][j] = WALL;
            } else {
                map[i][j] = EMPTY;
            }
        }
    }
    // ���ñ����ͳ���
    map[5][5] = SWORD;
    map[3][3] = ORANGE;
    map[4][4] = ORANGE;
    map[6][6] = ORANGE;
    // ���õ���
    map[HEIGHT-2][WIDTH-2] = ENEMY;
}

// ����״̬��
void draw_status_bar(Character player, PIMAGE playerImage, PIMAGE playerWithSwordImage, PIMAGE heartImage) {
    setfillcolor(LIGHTGRAY);
    bar(WIDTH * CELL_SIZE, 0, WIDTH * CELL_SIZE + STATUS_BAR_WIDTH, HEIGHT * CELL_SIZE);

    setbkmode(TRANSPARENT); // ���ñ���ģʽΪ͸��
    setcolor(BLACK); // �����ı���ɫΪ��ɫ
    setfont(20, 0, _T("����")); // ��������Ϊ���壬��СΪ20
    outtextxy(WIDTH * CELL_SIZE + 10, 20, _T("���״̬:"));

    if (player.hasSword) {
        outtextxy(WIDTH * CELL_SIZE + 10, 60, _T("װ��: ����"));
        putimage_withalpha(NULL, playerWithSwordImage, WIDTH * CELL_SIZE + 10, 100);
    } else {
        outtextxy(WIDTH * CELL_SIZE + 10, 60, _T("װ��: ��"));
        putimage_withalpha(NULL, playerImage, WIDTH * CELL_SIZE + 10, 100);
    }

    outtextxy(WIDTH * CELL_SIZE + 10, 200, _T("�� 'e' ��"));
    outtextxy(WIDTH * CELL_SIZE + 10, 230, _T("ȡ�±���"));

    outtextxy(WIDTH * CELL_SIZE + 10, 300, _T("����ֵ:"));
    for (int i = 0; i < player.hp; i++) {
        putimage_withalpha(NULL, heartImage, WIDTH * CELL_SIZE + 10 + i * 30, 330);
    }

    TCHAR attackStr[20];
    _stprintf(attackStr, _T("������: %d"), player.attack);
    outtextxy(WIDTH * CELL_SIZE + 10, 400, attackStr);

    TCHAR goldStr[20];
    _stprintf(goldStr, _T("���: %d"), player.gold);
    outtextxy(WIDTH * CELL_SIZE + 10, 450, goldStr);
}

// ���Ƶ�ͼ
void draw_map(int map[HEIGHT][WIDTH], Character player, Character enemy, PIMAGE playerImage, PIMAGE playerWithSwordImage, PIMAGE swordImage, PIMAGE orangeImage, PIMAGE enemyImage, PIMAGE goldImage) {
    setcolor(WHITE);
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            switch(map[i][j]) {
                case EMPTY:
                    setfillcolor(LIGHTGRAY);
                    break;
                case WALL:
                    setfillcolor(DARKGRAY);
                    break;
            }
            bar(j * CELL_SIZE, i * CELL_SIZE, (j + 1) * CELL_SIZE, (i + 1) * CELL_SIZE);
        }
    }

    // ���Ƴ��Ӻͽ��
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (map[i][j] == ORANGE) {
                putimage_withalpha(NULL, orangeImage, j * CELL_SIZE, i * CELL_SIZE);
            }
            if (map[i][j] == GOLD) {
                putimage_withalpha(NULL, goldImage, j * CELL_SIZE, i * CELL_SIZE);
            }
        }
    }

    // ���Ʊ���
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (map[i][j] == SWORD) {
                putimage_withalpha(NULL, swordImage, j * CELL_SIZE, i * CELL_SIZE);
            }
        }
    }

    // �������
    if (player.hasSword) {
        putimage_withalpha(NULL, playerWithSwordImage, player.y * CELL_SIZE, player.x * CELL_SIZE);
    } else {
        putimage_withalpha(NULL, playerImage, player.y * CELL_SIZE, player.x * CELL_SIZE);
    }

    // ���Ƶ���
    if (enemy.hp > 0) {
        putimage_withalpha(NULL, enemyImage, enemy.y * CELL_SIZE, enemy.x * CELL_SIZE);
    }
}

// ��������ƶ�
void move_player(Character *player, int dx, int dy, int map[HEIGHT][WIDTH], Character *enemy, PIMAGE playerImage, PIMAGE playerWithSwordImage, PIMAGE swordImage, PIMAGE orangeImage, PIMAGE enemyImage, PIMAGE heartImage, PIMAGE goldImage) {
    int new_x = player->x + dx;
    int new_y = player->y + dy;
    if (map[new_x][new_y] != WALL) {
        player->x = new_x;
        player->y = new_y;
        // ����Ƿ���������
        if (map[new_x][new_y] == SWORD) {
            player->hasSword = 1;
            player->attack = 5; // ���¹�����
            map[new_x][new_y] = EMPTY; // �õ���������ӵ�ͼ���Ƴ�
        }
        // ����Ƿ���������
        if (map[new_x][new_y] == ORANGE) {
            if (player->hp < 5) {
                player->hp += 1; // �ظ�һ������ֵ
            }
            map[new_x][new_y] = EMPTY; // �Ե����Ӻ���ӵ�ͼ���Ƴ�
        }
        // ����Ƿ��������
        if (map[new_x][new_y] == GOLD) {
            player->gold += 1; // ���ӽ��
            map[new_x][new_y] = EMPTY; // ʰȡ��Һ���ӵ�ͼ���Ƴ�
        }
        // ����Ƿ���������
        if (new_x == enemy->x && new_y == enemy->y) {
            while (player->hp > 0 && enemy->hp > 0) {
                player->hp -= enemy->attack;
                enemy->hp -= player->attack;
                // ��˸Ч��
                for (int i = 0; i < 5; i++) {
                    cleardevice();
                    Sleep(50);
                    draw_map(map, *player, *enemy, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, goldImage);
                    draw_status_bar(*player, playerImage, playerWithSwordImage, heartImage);
                    Sleep(50);
                }
            }
            if (enemy->hp <= 0) {
                // ���ѡ������ԱߵĿյص�����
                int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
                for (int i = 0; i < 4; i++) {
                    int nx = enemy->x + directions[i][0];
                    int ny = enemy->y + directions[i][1];
                    if (map[nx][ny] == EMPTY) {
                        map[nx][ny] = GOLD;
                        break;
                    }
                }
            }
            if (player->hp <= 0) {
                PIMAGE gameOverImage = newimage();
                getimage(gameOverImage, "images/game_over.png");
                putimage(0, 0, gameOverImage);
                getch();
                closegraph();
                exit(0);
            }
        }
    }
}

// ��ʾ����ҳ��
void show_start_screen() {
    cleardevice();
    setfillcolor(WHITE);
    bar(0, 0, WIDTH * CELL_SIZE + STATUS_BAR_WIDTH, HEIGHT * CELL_SIZE);

    PIMAGE logo = newimage();
    getimage(logo, "images/TAOO.png");
    putimage((WIDTH * CELL_SIZE + STATUS_BAR_WIDTH - 950) / 2, 50, logo);

    setcolor(BLACK);
    setbkmode(TRANSPARENT); // ���ñ���ģʽΪ͸��
    setfont(30, 0, _T("����"));
    outtextxy((WIDTH * CELL_SIZE + STATUS_BAR_WIDTH) / 2 - 100, 450, _T("���������ʼ��Ϸ"));

    getch();
    cleardevice();
}

// ������
int main() {
    srand(time(NULL)); // ��ʼ�������������
    initgraph(WIDTH * CELL_SIZE + STATUS_BAR_WIDTH, HEIGHT * CELL_SIZE);

    show_start_screen(); // ��ʾ����ҳ��

    int map[HEIGHT][WIDTH];
    Character player = {1, 1, 3, 2, 0, 0}; // ��ʼ��ʱ����������ֵ��������Ϊ2��û�б��������Ϊ0
    Character enemy = {HEIGHT-2, WIDTH-2, 5, 3}; // ���˳�ʼ����Ѫ��Ϊ5��������Ϊ3

    initialize_map(map);

    PIMAGE playerImage = newimage();
    PIMAGE playerWithSwordImage = newimage();
    PIMAGE swordImage = newimage();
    PIMAGE heartImage = newimage();
    PIMAGE orangeImage = newimage();
    PIMAGE enemyImage = newimage();
    PIMAGE goldImage = newimage();

    // ����ͼƬ
    getimage(playerImage, "images/player.png");
    getimage(playerWithSwordImage, "images/player_with_sword.png");
    getimage(swordImage, "images/sword.png");
    getimage(heartImage, "images/heart.png");
    getimage(orangeImage, "images/orange.png");
    getimage(enemyImage, "images/enemy_1.png");
    getimage(goldImage, "images/gold.png");

    while (1) {
        cleardevice();
        draw_map(map, player, enemy, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, goldImage);
        draw_status_bar(player, playerImage, playerWithSwordImage, heartImage);

        if (kbhit()) {
            char command = getch();
            switch (command) {
                case 'w': move_player(&player, -1, 0, map, &enemy, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, heartImage, goldImage); break;
                case 'a': move_player(&player, 0, -1, map, &enemy, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, heartImage, goldImage); break;
                case 's': move_player(&player, 1, 0, map, &enemy, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, heartImage, goldImage); break;
                case 'd': move_player(&player, 0, 1, map, &enemy, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, heartImage, goldImage); break;
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
                    break; // ȡ�±���
            }
        }
        Sleep(100); // ������Ϸ�ٶ�
    }

    closegraph();
    return 0;
}
