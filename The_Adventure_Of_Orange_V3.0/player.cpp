#include <graphics.h>
#include <conio.h>
#include <tchar.h>
#include "player.h"
#include "draw.h"
#include "map.h"

#define CELL_SIZE 50


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
