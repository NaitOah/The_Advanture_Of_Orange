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

    setbkmode(TRANSPARENT); // 设置背景模式为透明
    setcolor(BLACK); // 设置文本颜色为黑色
    setfont(20, 0, _T("宋体")); // 设置字体为宋体，大小为20
    outtextxy(WIDTH * CELL_SIZE + 10, 20, _T("玩家状态:"));

    if (player.hasSword) {
        outtextxy(WIDTH * CELL_SIZE + 10, 60, _T("装备: 宝剑"));
        putimage_withalpha(NULL, playerWithSwordImage, WIDTH * CELL_SIZE + 10, 100);
    } else {
        outtextxy(WIDTH * CELL_SIZE + 10, 60, _T("装备: 无"));
        putimage_withalpha(NULL, playerImage, WIDTH * CELL_SIZE + 10, 100);
    }

    outtextxy(WIDTH * CELL_SIZE + 10, 200, _T("按 'e' 键"));
    outtextxy(WIDTH * CELL_SIZE + 10, 230, _T("取下宝剑"));

    outtextxy(WIDTH * CELL_SIZE + 10, 300, _T("生命值:"));
    for (int i = 0; i < player.hp; i++) {
        putimage_withalpha(NULL, heartImage, WIDTH * CELL_SIZE + 10 + i * 30, 330);
    }

    TCHAR attackStr[20];
    _stprintf(attackStr, _T("攻击力: %d"), player.attack);
    outtextxy(WIDTH * CELL_SIZE + 10, 400, attackStr);

    TCHAR goldStr[20];
    _stprintf(goldStr, _T("金币: %d"), player.gold);
    outtextxy(WIDTH * CELL_SIZE + 10, 450, goldStr);

    TCHAR keyStr[20];
    _stprintf(keyStr, _T("钥匙: %d"), player.keys);
    outtextxy(WIDTH * CELL_SIZE + 10, 500, keyStr);

    // 显示金色橙子
    if (player.hasGoldOrange) {
        outtextxy(WIDTH * CELL_SIZE + 10, 550, _T("物品: 金色橙子"));
        putimage_withalpha(NULL, goldOrangeImage, WIDTH * CELL_SIZE + 10, 580);
    }
}

void draw_map(int map[HEIGHT][WIDTH], Character player, Character enemy, PIMAGE playerImage, PIMAGE playerWithSwordImage, PIMAGE swordImage, PIMAGE orangeImage, PIMAGE enemyImage, PIMAGE goldImage, PIMAGE wallImage, PIMAGE doorImage, PIMAGE keyImage, PIMAGE npc1Image, PIMAGE upStairsImage, PIMAGE downStairsImage, bool drawEnemy) {
    setcolor(WHITE);
    setbkcolor(BLACK); // 设置背景颜色为黑色
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

    // 绘制橙子和金币
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

    // 绘制宝剑
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (map[i][j] == SWORD) {
                putimage_withalpha(NULL, swordImage, j * CELL_SIZE, i * CELL_SIZE);
            }
        }
    }

    // 绘制玩家
    if (player.hasSword) {
        putimage_withalpha(NULL, playerWithSwordImage, player.y * CELL_SIZE, player.x * CELL_SIZE);
    } else {
        putimage_withalpha(NULL, playerImage, player.y * CELL_SIZE, player.x * CELL_SIZE);
    }

    // 绘制敌人
    if (drawEnemy && enemy.hp > 0) {
        putimage_withalpha(NULL, enemyImage, enemy.y * CELL_SIZE, enemy.x * CELL_SIZE);
    }
}

void draw_dialogue_box(const TCHAR* dialogue) {
    int dialogueBoxY = HEIGHT * CELL_SIZE - DIALOGUE_BOX_HEIGHT - 200;
    setcolor(WHITE);
    setbkmode(TRANSPARENT);
    setfont(20, 0, _T("宋体"));
    outtextxy(10, dialogueBoxY + 10, dialogue);
}

void draw_options(const TCHAR* option1, const TCHAR* option2) {
    int dialogueBoxY = HEIGHT * CELL_SIZE - DIALOGUE_BOX_HEIGHT - 200;
    setcolor(WHITE);
    setbkmode(TRANSPARENT);
    setfont(20, 0, _T("宋体"));
    outtextxy(10, dialogueBoxY + 50, option1); // 调整选项位置
    outtextxy(10, dialogueBoxY + 80, option2); // 调整选项位置
}

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


void show_start_screen() {
    cleardevice();
    setfillcolor(WHITE);
    bar(0, 0, WIDTH * CELL_SIZE + STATUS_BAR_WIDTH, HEIGHT * CELL_SIZE);

    PIMAGE logo = newimage();
    getimage(logo, "images/TAOO.png");
    putimage((WIDTH * CELL_SIZE + STATUS_BAR_WIDTH - 950) / 2, 50, logo);

    setcolor(BLACK);
    setbkmode(TRANSPARENT); // 设置背景模式为透明
    setfont(30, 0, _T("宋体"));
    outtextxy((WIDTH * CELL_SIZE + STATUS_BAR_WIDTH) / 2 - 100, 450, _T("按任意键开始游戏"));

    getch();
    cleardevice();
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
