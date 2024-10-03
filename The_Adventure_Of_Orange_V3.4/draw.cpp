#include <graphics.h>
#include <tchar.h>
#include <cstdio>
#include "draw.h"

#define CELL_SIZE 50
#define STATUS_BAR_WIDTH 200

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

void draw_map(int map[HEIGHT][WIDTH], Character player, Character enemy1, Character enemy2,
              PIMAGE playerImage, PIMAGE playerWithSwordImage, PIMAGE swordImage, PIMAGE orangeImage,
              PIMAGE enemyImage, PIMAGE enemy2Image, PIMAGE goldImage, PIMAGE wallImage, PIMAGE doorImage,
              PIMAGE keyImage, PIMAGE npc1Image, PIMAGE upStairsImage, PIMAGE downStairsImage, bool drawEnemy) {
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
    if (enemy1.hp > 0) {
        putimage_withalpha(NULL, enemyImage, enemy1.y * CELL_SIZE, enemy1.x * CELL_SIZE);
    }
    if (enemy2.hp > 0) {
        putimage_withalpha(NULL, enemy2Image, enemy2.y * CELL_SIZE, enemy2.x * CELL_SIZE);
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

void draw_exit_confirmation(int selectedOption) {
    cleardevice();
    setfillcolor(BLACK);
    bar(0, 0, WIDTH * CELL_SIZE + STATUS_BAR_WIDTH, HEIGHT * CELL_SIZE + DIALOGUE_BOX_HEIGHT);

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
