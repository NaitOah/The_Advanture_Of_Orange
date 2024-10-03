#include <graphics.h>
#include <conio.h>
#include <tchar.h>
#include <stdio.h>
#include <time.h>
#include "game.h"
#include "map.h"
#include "character.h"
#include "save_load.h"
#include "draw.h"
#include "player.h"
#include "menu.h"

#define CELL_SIZE 50
#define STATUS_BAR_WIDTH 200

void draw_save_confirmation(int selectedOption) {
    cleardevice();
    setfillcolor(BLACK); // ���ñ�����ɫΪ��ɫ
    bar(0, 0, WIDTH * CELL_SIZE + STATUS_BAR_WIDTH, HEIGHT * CELL_SIZE);

    setcolor(WHITE); // �����ı���ɫΪ��ɫ
    setbkmode(TRANSPARENT);
    setfont(30, 0, _T("����"));
    outtextxy(100, 200, _T("ȷ��Ҫ������Ϸ��"));
    outtextxy(100, 300, _T("1. ��"));
    outtextxy(100, 400, _T("2. ��"));

    if (selectedOption == 1) {
        outtextxy(80, 300, _T(">"));
    } else if (selectedOption == 2) {
        outtextxy(80, 400, _T(">"));
    }
}

void draw_save_success() {
    cleardevice();
    setfillcolor(BLACK); // ���ñ�����ɫΪ��ɫ
    bar(0, 0, WIDTH * CELL_SIZE + STATUS_BAR_WIDTH, HEIGHT * CELL_SIZE);

    setcolor(WHITE); // �����ı���ɫΪ��ɫ
    setbkmode(TRANSPARENT);
    setfont(30, 0, _T("����"));
    outtextxy((WIDTH * CELL_SIZE + STATUS_BAR_WIDTH) / 2 - 100, HEIGHT * CELL_SIZE / 2, _T("��Ϸ����ɹ�"));
    outtextxy((WIDTH * CELL_SIZE + STATUS_BAR_WIDTH) / 2 - 150, HEIGHT * CELL_SIZE / 2 + 50, _T("�������������Ϸ"));
}

void initialize_game(GameState *gameState, bool newGame) {
    if (newGame) {
        initialize_map(gameState->floor1State.map, 1);
        initialize_map(gameState->floor2State.map, 2);
        gameState->floor1State.player = (Character){1, 1, 3, 2, 0, 0, 0};
        gameState->floor1State.enemy = (Character){8, 1, 5, 3};
        gameState->floor2State.player = gameState->floor1State.player;
        gameState->floor2State.enemy = (Character){0, 0, 0, 0};
        gameState->player = gameState->floor1State.player;
        gameState->currentFloor = 1;
    }
}

void draw_exit_confirmation(int selectedOption) {
    cleardevice();
    setcolor(WHITE);
    setbkmode(TRANSPARENT);
    setfont(30, 0, _T("����"));
    outtextxy(100, 100, _T("ȷ���˳���Ϸ��"));
    outtextxy(100, 200, _T("1. ��"));
    outtextxy(100, 300, _T("2. ��"));

    if (selectedOption == 1) {
        outtextxy(80, 200, _T(">"));
    } else if (selectedOption == 2) {
        outtextxy(80, 300, _T(">"));
    }
}


void game_loop(GameState *gameState, int selectedSkin) {
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
    PIMAGE upStairsImage = newimage();
    PIMAGE downStairsImage = newimage();

    // ����ͼƬ
    if (selectedSkin == 1) {
        getimage(playerImage, "images/player.png");
        getimage(playerWithSwordImage, "images/player_with_sword.png");
        getimage(swordImage, "images/sword.png");
    } else if (selectedSkin == 2) {
        getimage(playerImage, "images/player_2.png");
        getimage(playerWithSwordImage, "images/player_with_sword_2.png");
        getimage(swordImage, "images/sword_2.png");
    }

    getimage(heartImage, "images/heart.png");
    getimage(orangeImage, "images/orange.png");
    getimage(enemyImage, "images/enemy_1.png");
    getimage(goldImage, "images/gold.png");
    getimage(wallImage, "images/wall.png");
    getimage(doorImage, "images/door.png");
    getimage(keyImage, "images/key.png");
    getimage(npc1Image, "images/npc_1.png");
    getimage(goldOrangeImage, "images/gold_orange.png");
    getimage(upStairsImage, "images/up_stairs.png");
    getimage(downStairsImage, "images/down_stairs.png");

    int saveConfirmation = 0;  // 0 ��ʾ���ڱ���ȷ�Ͻ��棬1 ��ʾ�ڱ���ȷ�Ͻ���
    int exitConfirmation = 0;  // 0 ��ʾ�����˳�ȷ�Ͻ��棬1 ��ʾ���˳�ȷ�Ͻ���
    int selectedOption = 1;
    bool running = true;

    ensure_save_dir_exists();

    while (running) {
        if (saveConfirmation == 0 && exitConfirmation == 0) {
            cleardevice();
            if (gameState->currentFloor == 1) {
                draw_map(gameState->floor1State.map, gameState->player, gameState->floor1State.enemy, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, goldImage, wallImage, doorImage, keyImage, npc1Image, upStairsImage, downStairsImage, true);
                draw_status_bar(gameState->player, playerImage, playerWithSwordImage, heartImage, goldOrangeImage);
            } else {
                draw_map(gameState->floor2State.map, gameState->player, gameState->floor2State.enemy, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, goldImage, wallImage, doorImage, keyImage, npc1Image, upStairsImage, downStairsImage, false);
                draw_status_bar(gameState->player, playerImage, playerWithSwordImage, heartImage, goldOrangeImage);
            }

            if (kbhit()) {
                char command = getch();
                switch (command) {
                    case 'w': move_player(&gameState->player, -1, 0, gameState->floor1State, gameState->floor2State, gameState->currentFloor, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, heartImage, goldImage, wallImage, doorImage, keyImage, npc1Image, upStairsImage, downStairsImage); break;
                    case 'a': move_player(&gameState->player, 0, -1, gameState->floor1State, gameState->floor2State, gameState->currentFloor, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, heartImage, goldImage, wallImage, doorImage, keyImage, npc1Image, upStairsImage, downStairsImage); break;
                    case 's': move_player(&gameState->player, 1, 0, gameState->floor1State, gameState->floor2State, gameState->currentFloor, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, heartImage, goldImage, wallImage, doorImage, keyImage, npc1Image, upStairsImage, downStairsImage); break;
                    case 'd': move_player(&gameState->player, 0, 1, gameState->floor1State, gameState->floor2State, gameState->currentFloor, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, heartImage, goldImage, wallImage, doorImage, keyImage, npc1Image, upStairsImage, downStairsImage); break;
                    case 'e':
                        if (gameState->player.hasSword) {
                            gameState->player.hasSword = 0;
                            gameState->player.attack = 2; // ���¹�����
                            if (gameState->currentFloor == 1) {
                                gameState->floor1State.map[gameState->player.x][gameState->player.y] = SWORD; // ���������ڵ���
                            } else {
                                gameState->floor2State.map[gameState->player.x][gameState->player.y] = SWORD; // ���������ڵ���
                            }
                        } else if (gameState->currentFloor == 1 && gameState->floor1State.map[gameState->player.x][gameState->player.y] == SWORD) {
                            gameState->player.hasSword = 1;
                            gameState->player.attack = 5; // ���¹�����
                            gameState->floor1State.map[gameState->player.x][gameState->player.y] = EMPTY; // ���𱦽�����ӵ�ͼ���Ƴ�
                        } else if (gameState->currentFloor == 2 && gameState->floor2State.map[gameState->player.x][gameState->player.y] == SWORD) {
                            gameState->player.hasSword = 1;
                            gameState->player.attack = 5; // ���¹�����
                            gameState->floor2State.map[gameState->player.x][gameState->player.y] = EMPTY; // ���𱦽�����ӵ�ͼ���Ƴ�
                        }
                        break;
                    case 'u':
                        if (gameState->player.hasGoldOrange) {
                            gameState->player.hp = 6; // ����Ѫ���������ʼ���Ѫ��Ϊ5
                            gameState->player.hasGoldOrange = 0; // ʹ�ú��ɫ������ʧ
                        }
                        break;
                    case 'p':
                        saveConfirmation = 1;  // ���뱣��ȷ�Ͻ���
                        selectedOption = 1;    // Ĭ��ѡ���ǡ�
                        break;
                    case 27: // ESC ��
                        exitConfirmation = 1; // �����˳�ȷ�Ͻ���
                        selectedOption = 1;   // Ĭ��ѡ���ǡ�
                        break;
                }
            }
        } else if (saveConfirmation == 1) {
            draw_save_confirmation(selectedOption);

            if (kbhit()) {
                int command = getch();
                switch (command) {
                    case '1':  // ѡ����
                        selectedOption = 1;
                        break;
                    case '2':  // ѡ���
                        selectedOption = 2;
                        break;
                    case 13:  // �س���
                        if (selectedOption == 1) {
                            int saveSlot = get_oldest_save_slot();
                            save_game(gameState, saveSlot);
                            draw_save_success();
                            getch();  // �ȴ���Ұ��������
                        }
                        saveConfirmation = 0;  // �˳�����ȷ�Ͻ���
                        break;
                    case 27:  // ESC ��
                        saveConfirmation = 0;  // �˳�����ȷ�Ͻ���
                        break;
                }
            }
        } else if (exitConfirmation == 1) {
            draw_exit_confirmation(selectedOption);

            if (kbhit()) {
                int command = getch();
                switch (command) {
                    case '1':  // ѡ����
                        selectedOption = 1;
                        break;
                    case '2':  // ѡ���
                        selectedOption = 2;
                        break;
                    case 13:  // �س���
                        if (selectedOption == 1) {
                            running = false; // �˳���Ϸ
                        }
                        exitConfirmation = 0;  // �˳��˳�ȷ�Ͻ���
                        break;
                    case 27:  // ESC ��
                        exitConfirmation = 0;  // �˳��˳�ȷ�Ͻ���
                        break;
                }
            }
        }

        Sleep(100); // ������Ϸ�ٶ�
    }

    closegraph();
}
