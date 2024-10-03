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
    setfillcolor(BLACK); // 设置背景颜色为黑色
    bar(0, 0, WIDTH * CELL_SIZE + STATUS_BAR_WIDTH, HEIGHT * CELL_SIZE);

    setcolor(WHITE); // 设置文本颜色为白色
    setbkmode(TRANSPARENT);
    setfont(30, 0, _T("宋体"));
    outtextxy(100, 200, _T("确定要保存游戏吗？"));
    outtextxy(100, 300, _T("1. 是"));
    outtextxy(100, 400, _T("2. 否"));

    if (selectedOption == 1) {
        outtextxy(80, 300, _T(">"));
    } else if (selectedOption == 2) {
        outtextxy(80, 400, _T(">"));
    }
}

void draw_save_success() {
    cleardevice();
    setfillcolor(BLACK); // 设置背景颜色为黑色
    bar(0, 0, WIDTH * CELL_SIZE + STATUS_BAR_WIDTH, HEIGHT * CELL_SIZE);

    setcolor(WHITE); // 设置文本颜色为白色
    setbkmode(TRANSPARENT);
    setfont(30, 0, _T("宋体"));
    outtextxy((WIDTH * CELL_SIZE + STATUS_BAR_WIDTH) / 2 - 100, HEIGHT * CELL_SIZE / 2, _T("游戏保存成功"));
    outtextxy((WIDTH * CELL_SIZE + STATUS_BAR_WIDTH) / 2 - 150, HEIGHT * CELL_SIZE / 2 + 50, _T("按任意键返回游戏"));
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
    setfont(30, 0, _T("宋体"));
    outtextxy(100, 100, _T("确认退出游戏吗？"));
    outtextxy(100, 200, _T("1. 是"));
    outtextxy(100, 300, _T("2. 否"));

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

    // 加载图片
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

    int saveConfirmation = 0;  // 0 表示不在保存确认界面，1 表示在保存确认界面
    int exitConfirmation = 0;  // 0 表示不在退出确认界面，1 表示在退出确认界面
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
                            gameState->player.attack = 2; // 更新攻击力
                            if (gameState->currentFloor == 1) {
                                gameState->floor1State.map[gameState->player.x][gameState->player.y] = SWORD; // 将宝剑丢在地上
                            } else {
                                gameState->floor2State.map[gameState->player.x][gameState->player.y] = SWORD; // 将宝剑丢在地上
                            }
                        } else if (gameState->currentFloor == 1 && gameState->floor1State.map[gameState->player.x][gameState->player.y] == SWORD) {
                            gameState->player.hasSword = 1;
                            gameState->player.attack = 5; // 更新攻击力
                            gameState->floor1State.map[gameState->player.x][gameState->player.y] = EMPTY; // 拿起宝剑后将其从地图上移除
                        } else if (gameState->currentFloor == 2 && gameState->floor2State.map[gameState->player.x][gameState->player.y] == SWORD) {
                            gameState->player.hasSword = 1;
                            gameState->player.attack = 5; // 更新攻击力
                            gameState->floor2State.map[gameState->player.x][gameState->player.y] = EMPTY; // 拿起宝剑后将其从地图上移除
                        }
                        break;
                    case 'u':
                        if (gameState->player.hasGoldOrange) {
                            gameState->player.hp = 6; // 回满血量，假设初始最大血量为5
                            gameState->player.hasGoldOrange = 0; // 使用后金色橙子消失
                        }
                        break;
                    case 'p':
                        saveConfirmation = 1;  // 进入保存确认界面
                        selectedOption = 1;    // 默认选择“是”
                        break;
                    case 27: // ESC 键
                        exitConfirmation = 1; // 进入退出确认界面
                        selectedOption = 1;   // 默认选择“是”
                        break;
                }
            }
        } else if (saveConfirmation == 1) {
            draw_save_confirmation(selectedOption);

            if (kbhit()) {
                int command = getch();
                switch (command) {
                    case '1':  // 选择是
                        selectedOption = 1;
                        break;
                    case '2':  // 选择否
                        selectedOption = 2;
                        break;
                    case 13:  // 回车键
                        if (selectedOption == 1) {
                            int saveSlot = get_oldest_save_slot();
                            save_game(gameState, saveSlot);
                            draw_save_success();
                            getch();  // 等待玩家按下任意键
                        }
                        saveConfirmation = 0;  // 退出保存确认界面
                        break;
                    case 27:  // ESC 键
                        saveConfirmation = 0;  // 退出保存确认界面
                        break;
                }
            }
        } else if (exitConfirmation == 1) {
            draw_exit_confirmation(selectedOption);

            if (kbhit()) {
                int command = getch();
                switch (command) {
                    case '1':  // 选择是
                        selectedOption = 1;
                        break;
                    case '2':  // 选择否
                        selectedOption = 2;
                        break;
                    case 13:  // 回车键
                        if (selectedOption == 1) {
                            running = false; // 退出游戏
                        }
                        exitConfirmation = 0;  // 退出退出确认界面
                        break;
                    case 27:  // ESC 键
                        exitConfirmation = 0;  // 退出退出确认界面
                        break;
                }
            }
        }

        Sleep(100); // 控制游戏速度
    }

    closegraph();
}
