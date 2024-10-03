#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <tchar.h>
#include "map.h"
#include "character.h"
#include "game.h"

#define CELL_SIZE 50
#define STATUS_BAR_WIDTH 200
#define DIALOGUE_BOX_HEIGHT 0

void draw_status_bar(Character player, PIMAGE playerImage, PIMAGE playerWithSwordImage, PIMAGE heartImage, PIMAGE goldOrangeImage) {
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

    TCHAR keyStr[20];
    _stprintf(keyStr, _T("Կ��: %d"), player.keys);
    outtextxy(WIDTH * CELL_SIZE + 10, 500, keyStr);

    // ��ʾ��ɫ����
    if (player.hasGoldOrange) {
        outtextxy(WIDTH * CELL_SIZE + 10, 550, _T("��Ʒ: ��ɫ����"));
        putimage_withalpha(NULL, goldOrangeImage, WIDTH * CELL_SIZE + 10, 580);
    }
}

void draw_map(int map[HEIGHT][WIDTH], Character player, Character enemy, PIMAGE playerImage, PIMAGE playerWithSwordImage, PIMAGE swordImage, PIMAGE orangeImage, PIMAGE enemyImage, PIMAGE goldImage, PIMAGE wallImage, PIMAGE doorImage, PIMAGE keyImage, PIMAGE npc1Image, PIMAGE upStairsImage, PIMAGE downStairsImage, bool drawEnemy) {
    setcolor(WHITE);
    setbkcolor(BLACK); // ���ñ�����ɫΪ��ɫ
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            switch(map[i][j]) {
                case EMPTY:
                    setfillcolor(BLACK);
                    bar(j * CELL_SIZE, i * CELL_SIZE, (j + 1) * CELL_SIZE, (i + 1) * CELL_SIZE);
                    break;
                case WALL:
                    putimage_withalpha(NULL, wallImage, j * CELL_SIZE, i * CELL_SIZE);
                    break;
                case DOOR:
                    putimage_withalpha(NULL, doorImage, j * CELL_SIZE, i * CELL_SIZE);
                    break;
                case KEY:
                    putimage_withalpha(NULL, keyImage, j * CELL_SIZE, i * CELL_SIZE);
                    break;
                case NPC_1:
                    putimage_withalpha(NULL, npc1Image, j * CELL_SIZE, i * CELL_SIZE);
                    break;
                case UP_STAIRS:
                    putimage_withalpha(NULL, upStairsImage, j * CELL_SIZE, i * CELL_SIZE);
                    break;
                case DOWN_STAIRS:
                    putimage_withalpha(NULL, downStairsImage, j * CELL_SIZE, i * CELL_SIZE);
                    break;
            }
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
    if (drawEnemy && enemy.hp > 0) {
        putimage_withalpha(NULL, enemyImage, enemy.y * CELL_SIZE, enemy.x * CELL_SIZE);
    }
}

void draw_dialogue_box(const TCHAR* dialogue) {
    int dialogueBoxY = HEIGHT * CELL_SIZE - DIALOGUE_BOX_HEIGHT - 200;
    setcolor(WHITE);
    setbkmode(TRANSPARENT);
    setfont(20, 0, _T("����"));
    outtextxy(10, dialogueBoxY + 10, dialogue);
}

void draw_options(const TCHAR* option1, const TCHAR* option2) {
    int dialogueBoxY = HEIGHT * CELL_SIZE - DIALOGUE_BOX_HEIGHT - 200;
    setcolor(WHITE);
    setbkmode(TRANSPARENT);
    setfont(20, 0, _T("����"));
    outtextxy(10, dialogueBoxY + 50, option1); // ����ѡ��λ��
    outtextxy(10, dialogueBoxY + 80, option2); // ����ѡ��λ��
}

void move_player(Character *player, int dx, int dy, FloorState &floor1State, FloorState &floor2State, int &currentFloor, PIMAGE playerImage, PIMAGE playerWithSwordImage, PIMAGE swordImage, PIMAGE orangeImage, PIMAGE enemyImage, PIMAGE heartImage, PIMAGE goldImage, PIMAGE wallImage, PIMAGE doorImage, PIMAGE keyImage, PIMAGE npc1Image, PIMAGE upStairsImage, PIMAGE downStairsImage) {
    FloorState &currentFloorState = (currentFloor == 1) ? floor1State : floor2State;

    int new_x = player->x + dx;
    int new_y = player->y + dy;
    if (currentFloorState.map[new_x][new_y] != WALL) {
        if (currentFloorState.map[new_x][new_y] == DOOR && player->keys > 0) {
            player->keys--;  // ʹ��Կ��
            currentFloorState.map[new_x][new_y] = EMPTY;  // ����
        } else if (currentFloorState.map[new_x][new_y] != DOOR) {
            player->x = new_x;
            player->y = new_y;
        }

        // ����Ƿ���������
        if (currentFloorState.map[new_x][new_y] == SWORD) {
            player->hasSword = 1;
            player->attack = 5; // ���¹�����
            currentFloorState.map[new_x][new_y] = EMPTY; // �õ���������ӵ�ͼ���Ƴ�
        }
        // ����Ƿ���������
        if (currentFloorState.map[new_x][new_y] == ORANGE) {
            if (player->hp < 5) {
                player->hp += 1; // �ظ�һ������ֵ
            }
            currentFloorState.map[new_x][new_y] = EMPTY; // �Ե����Ӻ���ӵ�ͼ���Ƴ�
        }
        // ����Ƿ�����Կ��
        if (currentFloorState.map[new_x][new_y] == KEY) {
            player->keys += 1; // ����Կ��
            currentFloorState.map[new_x][new_y] = EMPTY; // �õ�Կ�׺���ӵ�ͼ���Ƴ�
        }
        // ����Ƿ��������
        if (currentFloorState.map[new_x][new_y] == GOLD) {
            player->gold += 1; // ���ӽ��
            currentFloorState.map[new_x][new_y] = EMPTY; // ʰȡ��Һ���ӵ�ͼ���Ƴ�
        }
        // ����Ƿ����� NPC
        if (currentFloorState.map[new_x][new_y] == NPC_1) {
            trigger_dialogue(player, currentFloorState.map, npc1Image, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, goldImage, wallImage, doorImage, keyImage, heartImage, upStairsImage);
        }
        // ����Ƿ���������
        if (new_x == currentFloorState.enemy.x && new_y == currentFloorState.enemy.y) {
            if (currentFloorState.enemy.hp > 0) { // ֻ���ڵ��˻��ŵ�ʱ��Ž���ս��
                while (player->hp > 0 && currentFloorState.enemy.hp > 0) {
                    player->hp -= currentFloorState.enemy.attack;
                    currentFloorState.enemy.hp -= player->attack;
                    // ��˸Ч��
                    for (int i = 0; i < 5; i++) {
                        cleardevice();
                        Sleep(50);
                        draw_map(currentFloorState.map, *player, currentFloorState.enemy, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, goldImage, wallImage, doorImage, keyImage, npc1Image, upStairsImage, downStairsImage, true);
                        draw_status_bar(*player, playerImage, playerWithSwordImage, heartImage, orangeImage);
                        Sleep(50);
                    }
                }
                if (currentFloorState.enemy.hp <= 0) {
                    // ���ѡ������ԱߵĿյص�����
                    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
                    for (int i = 0; i < 4; i++) {
                        int nx = currentFloorState.enemy.x + directions[i][0];
                        int ny = currentFloorState.enemy.y + directions[i][1];
                        if (currentFloorState.map[nx][ny] == EMPTY) {
                            currentFloorState.map[nx][ny] = GOLD;
                            break;
                        }
                    }
                    currentFloorState.map[currentFloorState.enemy.x][currentFloorState.enemy.y] = EMPTY; // �������λ�ñ��
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

        // ����Ƿ�������¥¥��
        if (currentFloorState.map[new_x][new_y] == UP_STAIRS && currentFloor == 1) {
            // ���浱ǰ¥��״̬
            floor1State.player = *player;
            floor1State.enemy = currentFloorState.enemy;
            memcpy(floor1State.map, currentFloorState.map, sizeof(currentFloorState.map));
            // �л����ڶ���
            currentFloor = 2;
            player->x = 1; // �����λ���趨���ڶ���ĳ�ʼλ��
            player->y = 1;
        }
        // ����Ƿ�������¥¥��
        if (currentFloorState.map[new_x][new_y] == DOWN_STAIRS && currentFloor == 2) {
            // ���浱ǰ¥��״̬
            floor2State.player = *player;
            floor2State.enemy = currentFloorState.enemy;
            memcpy(floor2State.map, currentFloorState.map, sizeof(currentFloorState.map));
            // �л�����һ��
            currentFloor = 1;
            player->x = 7; // �����λ���趨����һ��ĳ�ʼλ��
            player->y = 1;
        }
    }
}


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


void trigger_dialogue(Character *player, int map[HEIGHT][WIDTH], PIMAGE npc1Image, PIMAGE playerImage, PIMAGE playerWithSwordImage, PIMAGE swordImage, PIMAGE orangeImage, PIMAGE enemyImage, PIMAGE goldImage, PIMAGE wallImage, PIMAGE doorImage, PIMAGE keyImage, PIMAGE heartImage, PIMAGE upStairsImage) {
    const TCHAR* dialogues[] = {
        _T("���ֶ�������������ҵĳ����أ���������... ...��"),
        _T("ɥ�룺�������ʿŶ����ӭ����˹ά�۴�½"),
        _T("�������������Ǵ�½��¬��������"),
        _T("ֻҪ��ܴ�ħ�����ܳ�ȥ�ˡ��ұ���ʩ����ħ����ӡ"),
        _T("�Ѿ�����ȥ��... ...�����˰���ף����ˣ�����������͸����"),
        _T("ϣ������Դ��ħ��������ҵķ�ӡ... ...")
    };

    int num_dialogues = sizeof(dialogues) / sizeof(dialogues[0]);

    PIMAGE npc1ImageC = newimage();
    PIMAGE npc1ImageO = newimage();
    getimage(npc1ImageC, "images/npc_1_c.png");
    getimage(npc1ImageO, "images/npc_1_o.png");

    int npcImageX = WIDTH * CELL_SIZE - 110; // NPC ͼ��λ��
    int npcImageY = HEIGHT * CELL_SIZE - DIALOGUE_BOX_HEIGHT - 200;

    for (int i = 0; i < num_dialogues; i++) {
        cleardevice();
        draw_map(map, *player, *player, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, goldImage, wallImage, doorImage, keyImage, npc1Image, upStairsImage, NULL, false);
        draw_status_bar(*player, playerImage, playerWithSwordImage, heartImage, NULL);
        draw_dialogue_box(dialogues[i]);

        // ������ʾ NPC ͼ��
        if (i % 2 == 0) {
            putimage_withalpha(NULL, npc1ImageC, npcImageX, npcImageY);
        } else {
            putimage_withalpha(NULL, npc1ImageO, npcImageX, npcImageY);
        }

        getch();
    }

    while (true) {
        cleardevice();
        draw_map(map, *player, *player, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, goldImage, wallImage, doorImage, keyImage, npc1Image, upStairsImage, NULL, false);
        draw_status_bar(*player, playerImage, playerWithSwordImage, heartImage, NULL);
        draw_options(_T("1. ��һ����Ŭ���ģ�"), _T("2. �ϵǣ���ƾʲô���㣡"));

        // ��ʾ NPC ͼ��
        if (num_dialogues % 2 == 0) {
            putimage_withalpha(NULL, npc1ImageC, npcImageX, npcImageY);
        } else {
            putimage_withalpha(NULL, npc1ImageO, npcImageX, npcImageY);
        }

        char choice = getch();
        if (choice == '1') {
            player->hasGoldOrange = 1;
            map[5][2] = EMPTY; // �Ƴ�NPC
            cleardevice();
            draw_map(map, *player, *player, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, goldImage, wallImage, doorImage, keyImage, npc1Image, upStairsImage, NULL, false);
            draw_status_bar(*player, playerImage, playerWithSwordImage, heartImage, orangeImage);
            draw_dialogue_box(_T("���ֶ�����һ����Ŭ���ģ�"));
            getch();
            cleardevice();
            break;
        } else if (choice == '2') {
            cleardevice();
            draw_map(map, *player, *player, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, goldImage, wallImage, doorImage, keyImage, npc1Image, upStairsImage, NULL, false);
            draw_status_bar(*player, playerWithSwordImage, heartImage, heartImage, heartImage);
            draw_dialogue_box(_T("ɥ�룺С������ܣ���������һ�٣�����֪��֪��ʲô�ж���ò��"));
            getch();

            // ��ʾɥ�������������
            cleardevice();
            draw_map(map, *player, *player, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, goldImage, wallImage, doorImage, keyImage, npc1Image, upStairsImage, NULL, false);
            draw_status_bar(*player, playerWithSwordImage, heartImage, heartImage, heartImage);
            setcolor(RED);
            setbkmode(TRANSPARENT);
            setfont(20, 0, _T("����"));

            // ��ʾ��һ��
            outtextxy(10, HEIGHT * CELL_SIZE - DIALOGUE_BOX_HEIGHT - 200 + 10, _T("---ɥ������������������"));
            // ��ʾ�ڶ���
            outtextxy(10, HEIGHT * CELL_SIZE - DIALOGUE_BOX_HEIGHT - 200 + 40, _T("�㱻ɥ��ɱ����... ..."));

            getch();

            player->hp = 0;
            PIMAGE gameOverImage = newimage();
            getimage(gameOverImage, "images/game_over.png");
            putimage(0, 0, gameOverImage);
            getch();
            closegraph();
            exit(0);
        } else {
            cleardevice();
            draw_map(map, *player, *player, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, goldImage, wallImage, doorImage, keyImage, npc1Image, upStairsImage, NULL, false);
            draw_status_bar(*player, playerImage, playerWithSwordImage, heartImage, NULL);
            draw_options(_T("1. ��һ����Ŭ���ģ�"), _T("2. �ϵǣ���ƾʲô���㣡"));
            draw_dialogue_box(_T("������ѡ��"));
            getch();
        }
    }
}
