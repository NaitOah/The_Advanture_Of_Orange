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
            player->keys--;  // 使用钥匙
            currentFloorState.map[new_x][new_y] = EMPTY;  // 开门
        } else if (currentFloorState.map[new_x][new_y] != DOOR) {
            player->x = new_x;
            player->y = new_y;
        }

        // 检测是否碰到宝剑
        if (currentFloorState.map[new_x][new_y] == SWORD) {
            player->hasSword = 1;
            player->attack = 5; // 更新攻击力
            currentFloorState.map[new_x][new_y] = EMPTY; // 拿到宝剑后将其从地图上移除
        }
        // 检测是否碰到橙子
        if (currentFloorState.map[new_x][new_y] == ORANGE) {
            if (player->hp < 5) {
                player->hp += 1; // 回复一点生命值
            }
            currentFloorState.map[new_x][new_y] = EMPTY; // 吃掉橙子后将其从地图上移除
        }
        // 检测是否碰到钥匙
        if (currentFloorState.map[new_x][new_y] == KEY) {
            player->keys += 1; // 增加钥匙
            currentFloorState.map[new_x][new_y] = EMPTY; // 拿到钥匙后将其从地图上移除
        }
        // 检测是否碰到金币
        if (currentFloorState.map[new_x][new_y] == GOLD) {
            player->gold += 1; // 增加金币
            currentFloorState.map[new_x][new_y] = EMPTY; // 拾取金币后将其从地图上移除
        }
        // 检测是否碰到 NPC
        if (currentFloorState.map[new_x][new_y] == NPC_1) {
            trigger_dialogue(player, currentFloorState.map, npc1Image, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, goldImage, wallImage, doorImage, keyImage, heartImage, upStairsImage);
        }
        // 检测是否碰到敌人
        if (new_x == currentFloorState.enemy.x && new_y == currentFloorState.enemy.y) {
            if (currentFloorState.enemy.hp > 0) { // 只有在敌人活着的时候才进行战斗
                while (player->hp > 0 && currentFloorState.enemy.hp > 0) {
                    player->hp -= currentFloorState.enemy.attack;
                    currentFloorState.enemy.hp -= player->attack;
                    // 闪烁效果
                    for (int i = 0; i < 5; i++) {
                        cleardevice();
                        Sleep(50);
                        draw_map(currentFloorState.map, *player, currentFloorState.enemy, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, goldImage, wallImage, doorImage, keyImage, npc1Image, upStairsImage, downStairsImage, true);
                        draw_status_bar(*player, playerImage, playerWithSwordImage, heartImage, orangeImage);
                        Sleep(50);
                    }
                }
                if (currentFloorState.enemy.hp <= 0) {
                    // 随机选择怪物旁边的空地掉落金币
                    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
                    for (int i = 0; i < 4; i++) {
                        int nx = currentFloorState.enemy.x + directions[i][0];
                        int ny = currentFloorState.enemy.y + directions[i][1];
                        if (currentFloorState.map[nx][ny] == EMPTY) {
                            currentFloorState.map[nx][ny] = GOLD;
                            break;
                        }
                    }
                    currentFloorState.map[currentFloorState.enemy.x][currentFloorState.enemy.y] = EMPTY; // 清除敌人位置标记
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

        // 检测是否碰到上楼楼梯
        if (currentFloorState.map[new_x][new_y] == UP_STAIRS && currentFloor == 1) {
            // 保存当前楼层状态
            floor1State.player = *player;
            floor1State.enemy = currentFloorState.enemy;
            memcpy(floor1State.map, currentFloorState.map, sizeof(currentFloorState.map));
            // 切换到第二层
            currentFloor = 2;
            player->x = 1; // 将玩家位置设定到第二层的初始位置
            player->y = 1;
        }
        // 检测是否碰到下楼楼梯
        if (currentFloorState.map[new_x][new_y] == DOWN_STAIRS && currentFloor == 2) {
            // 保存当前楼层状态
            floor2State.player = *player;
            floor2State.enemy = currentFloorState.enemy;
            memcpy(floor2State.map, currentFloorState.map, sizeof(currentFloorState.map));
            // 切换到第一层
            currentFloor = 1;
            player->x = 7; // 将玩家位置设定到第一层的初始位置
            player->y = 1;
        }
    }
}

void trigger_dialogue(Character *player, int map[HEIGHT][WIDTH], PIMAGE npc1Image, PIMAGE playerImage, PIMAGE playerWithSwordImage, PIMAGE swordImage, PIMAGE orangeImage, PIMAGE enemyImage, PIMAGE goldImage, PIMAGE wallImage, PIMAGE doorImage, PIMAGE keyImage, PIMAGE heartImage, PIMAGE upStairsImage) {
    const TCHAR* dialogues[] = {
        _T("帕乐尔：这里是哪里，我的橙子呢（自言自语... ...）"),
        _T("丧彪：年轻的勇士哦，欢迎来到斯维驰大陆"),
        _T("你现在身处于我们大陆的卢基塔里面"),
        _T("只要打败大魔王就能出去了。我被他施加了魔法封印"),
        _T("已经出不去了... ...年轻人啊，祝你好运，这个橙子是送给你的"),
        _T("希望你可以打败魔王，解除我的封印... ...")
    };

    int num_dialogues = sizeof(dialogues) / sizeof(dialogues[0]);

    PIMAGE npc1ImageC = newimage();
    PIMAGE npc1ImageO = newimage();
    getimage(npc1ImageC, "images/npc_1_c.png");
    getimage(npc1ImageO, "images/npc_1_o.png");

    int npcImageX = WIDTH * CELL_SIZE - 110; // NPC 图像位置
    int npcImageY = HEIGHT * CELL_SIZE - DIALOGUE_BOX_HEIGHT - 200;

    for (int i = 0; i < num_dialogues; i++) {
        cleardevice();
        draw_map(map, *player, *player, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, goldImage, wallImage, doorImage, keyImage, npc1Image, upStairsImage, NULL, false);
        draw_status_bar(*player, playerImage, playerWithSwordImage, heartImage, NULL);
        draw_dialogue_box(dialogues[i]);

        // 交替显示 NPC 图像
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
        draw_options(_T("1. 我一定会努力的！"), _T("2. 老登，我凭什么帮你！"));

        // 显示 NPC 图像
        if (num_dialogues % 2 == 0) {
            putimage_withalpha(NULL, npc1ImageC, npcImageX, npcImageY);
        } else {
            putimage_withalpha(NULL, npc1ImageO, npcImageX, npcImageY);
        }

        char choice = getch();
        if (choice == '1') {
            player->hasGoldOrange = 1;
            map[5][2] = EMPTY; // 移除NPC
            cleardevice();
            draw_map(map, *player, *player, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, goldImage, wallImage, doorImage, keyImage, npc1Image, upStairsImage, NULL, false);
            draw_status_bar(*player, playerImage, playerWithSwordImage, heartImage, orangeImage);
            draw_dialogue_box(_T("帕乐尔：我一定会努力的！"));
            getch();
            cleardevice();
            break;
        } else if (choice == '2') {
            cleardevice();
            draw_map(map, *player, *player, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, goldImage, wallImage, doorImage, keyImage, npc1Image, upStairsImage, NULL, false);
            draw_status_bar(*player, playerWithSwordImage, heartImage, heartImage, heartImage);
            draw_dialogue_box(_T("丧彪：小登你别跑，让我揍你一顿，让你知道知道什么叫懂礼貌！"));
            getch();

            // 显示丧彪很生气的文字
            cleardevice();
            draw_map(map, *player, *player, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, goldImage, wallImage, doorImage, keyImage, npc1Image, upStairsImage, NULL, false);
            draw_status_bar(*player, playerWithSwordImage, heartImage, heartImage, heartImage);
            setcolor(RED);
            setbkmode(TRANSPARENT);
            setfont(20, 0, _T("宋体"));

            // 显示第一行
            outtextxy(10, HEIGHT * CELL_SIZE - DIALOGUE_BOX_HEIGHT - 200 + 10, _T("---丧彪很生气，后果很严重"));
            // 显示第二行
            outtextxy(10, HEIGHT * CELL_SIZE - DIALOGUE_BOX_HEIGHT - 200 + 40, _T("你被丧彪杀死了... ..."));

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
            draw_options(_T("1. 我一定会努力的！"), _T("2. 老登，我凭什么帮你！"));
            draw_dialogue_box(_T("请做出选择"));
            getch();
        }
    }
}
