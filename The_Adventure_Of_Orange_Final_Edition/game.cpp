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

void initialize_game(GameState *gameState, bool newGame) {
    if (newGame) {
        initialize_map(gameState->floor1State.map, 1);
        initialize_map(gameState->floor2State.map, 2);
        gameState->floor1State.player = (Character){1, 1, 3, 2, 0, 0, 0, 0};
        gameState->floor1State.enemy = (Character){8, 1, 5, 3, 0, 0, 0, 0};
        gameState->floor1State.enemy2 = (Character){0, 0, 0, 0, 0, 0, 0, 0}; // 没有第二个敌人
        gameState->floor2State.player = (Character){1, 1, 3, 2, 0, 0, 0, 0}; // 初始化第二层玩家位置
        gameState->floor2State.enemy = (Character){6, 1, 5, 3, 0, 0, 0, 0}; // 初始化第二层敌人
        gameState->floor2State.enemy2 = (Character){12, 7, 5, 5, 0, 0, 0, 0}; // 初始化第二层第二个敌人
        gameState->player = gameState->floor1State.player;
        gameState->currentFloor = 1;
    }
}

void game_loop(GameState *gameState, int skin) {
    PIMAGE playerImage = newimage();
    PIMAGE playerWithSwordImage = newimage();
    PIMAGE swordImage = newimage();
    PIMAGE heartImage = newimage();
    PIMAGE orangeImage = newimage();
    PIMAGE enemyImage = newimage();
    PIMAGE enemy2Image = newimage();
    PIMAGE goldImage = newimage();
    PIMAGE wallImage = newimage();
    PIMAGE doorImage = newimage();
    PIMAGE keyImage = newimage();
    PIMAGE npc1Image = newimage();
    PIMAGE goldOrangeImage = newimage();
    PIMAGE upStairsImage = newimage();
    PIMAGE downStairsImage = newimage();
    PIMAGE princessImage = newimage(); // 新增公主图片

    // 加载图片
    getimage(playerImage, skin == 1 ? "images/player.png" : "images/player_2.png");
    getimage(playerWithSwordImage, skin == 1 ? "images/player_with_sword.png" : "images/player_with_sword_2.png");
    getimage(swordImage, skin == 1 ? "images/sword.png" : "images/sword_2.png");
    getimage(heartImage, "images/heart.png");
    getimage(orangeImage, "images/orange.png");
    getimage(enemyImage, "images/enemy_1.png");
    getimage(enemy2Image, "images/enemy_2.png");
    getimage(goldImage, "images/gold.png");
    getimage(wallImage, "images/wall.png");
    getimage(doorImage, "images/door.png");
    getimage(keyImage, "images/key.png");
    getimage(npc1Image, "images/npc_1.png");
    getimage(goldOrangeImage, "images/gold_orange.png");
    getimage(upStairsImage, "images/up_stairs.png");
    getimage(downStairsImage, "images/down_stairs.png");
    getimage(princessImage, "images/princess.png"); // 加载公主图片

    int saveConfirmation = 0;  // 0 表示不在保存确认界面，1 表示在保存确认界面
    int selectedOption = 1;

    ensure_save_dir_exists();

    while (1) {
        if (saveConfirmation == 0) {
            cleardevice();
            if (gameState->currentFloor == 1) {
                draw_map(gameState->floor1State.map, gameState->player, gameState->floor1State.enemy, gameState->floor1State.enemy2,
                    playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, enemy2Image, goldImage, wallImage, doorImage, keyImage, npc1Image, upStairsImage, downStairsImage, princessImage, true);
                draw_status_bar(gameState->player, playerImage, playerWithSwordImage, heartImage, goldOrangeImage);
            } else {
                draw_map(gameState->floor2State.map, gameState->player, gameState->floor2State.enemy, gameState->floor2State.enemy2,
                    playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, enemy2Image, goldImage, wallImage, doorImage, keyImage, npc1Image, upStairsImage, downStairsImage, princessImage, false);
                draw_status_bar(gameState->player, playerImage, playerWithSwordImage, heartImage, goldOrangeImage);
            }

            if (kbhit()) {
                char command = getch();
                switch (command) {
                    case 'w': move_player(&gameState->player, -1, 0, gameState->floor1State, gameState->floor2State, gameState->currentFloor,
                            playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, enemy2Image, heartImage, goldImage, wallImage, doorImage, keyImage, npc1Image, upStairsImage, downStairsImage, princessImage); break;
                    case 'a': move_player(&gameState->player, 0, -1, gameState->floor1State, gameState->floor2State, gameState->currentFloor,
                            playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, enemy2Image, heartImage, goldImage, wallImage, doorImage, keyImage, npc1Image, upStairsImage, downStairsImage, princessImage); break;
                    case 's': move_player(&gameState->player, 1, 0, gameState->floor1State, gameState->floor2State, gameState->currentFloor,
                            playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, enemy2Image, heartImage, goldImage, wallImage, doorImage, keyImage, npc1Image, upStairsImage, downStairsImage, princessImage); break;
                    case 'd': move_player(&gameState->player, 0, 1, gameState->floor1State, gameState->floor2State, gameState->currentFloor,
                            playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, enemy2Image, heartImage, goldImage, wallImage, doorImage, keyImage, npc1Image, upStairsImage, downStairsImage, princessImage); break;
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
                    case 27:  // ESC 键
                        saveConfirmation = 2;  // 进入退出确认界面
                        selectedOption = 1;    // 默认选择“是”
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
                            // 保存游戏
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
        } else if (saveConfirmation == 2) {  // 退出确认界面
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
                            closegraph();
                            exit(0);  // 退出游戏
                        }
                        saveConfirmation = 0;  // 退出退出确认界面
                        break;
                    case 27:  // ESC 键
                        saveConfirmation = 0;  // 退出退出确认界面
                        break;
                }
            }
        }

        Sleep(100); // 控制游戏速度
    }

    closegraph();
}
