#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <tchar.h> // 用于处理 _T 宏
#include <stdlib.h> // 用于随机数生成
#include <time.h>   // 用于时间获取
#include "map.h"

#define CELL_SIZE 50
#define STATUS_BAR_WIDTH 200

// 玩家和敌人结构体
typedef struct {
    int x;
    int y;
    int hp;
    int attack;
    int hasSword; // 增加标志以表示玩家是否有宝剑
    int gold;     // 增加金币数值
    int keys;     // 增加钥匙数值
} Character;

// 绘制状态栏
void draw_status_bar(Character player, PIMAGE playerImage, PIMAGE playerWithSwordImage, PIMAGE heartImage) {
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
}

// 绘制地图
void draw_map(int map[HEIGHT][WIDTH], Character player, Character enemy, PIMAGE playerImage, PIMAGE playerWithSwordImage, PIMAGE swordImage, PIMAGE orangeImage, PIMAGE enemyImage, PIMAGE goldImage, PIMAGE wallImage, PIMAGE doorImage, PIMAGE keyImage) {
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
    if (enemy.hp > 0) {
        putimage_withalpha(NULL, enemyImage, enemy.y * CELL_SIZE, enemy.x * CELL_SIZE);
    }
}

// 处理玩家移动
void move_player(Character *player, int dx, int dy, int map[HEIGHT][WIDTH], Character *enemy, PIMAGE playerImage, PIMAGE playerWithSwordImage, PIMAGE swordImage, PIMAGE orangeImage, PIMAGE enemyImage, PIMAGE heartImage, PIMAGE goldImage, PIMAGE wallImage, PIMAGE doorImage, PIMAGE keyImage) {
    int new_x = player->x + dx;
    int new_y = player->y + dy;
    if (map[new_x][new_y] != WALL) {
        if (map[new_x][new_y] == DOOR && player->keys > 0) {
            player->keys--;  // 使用钥匙
            map[new_x][new_y] = EMPTY;  // 开门
        } else if (map[new_x][new_y] != DOOR) {
            player->x = new_x;
            player->y = new_y;
        }

        // 检测是否碰到宝剑
        if (map[new_x][new_y] == SWORD) {
            player->hasSword = 1;
            player->attack = 5; // 更新攻击力
            map[new_x][new_y] = EMPTY; // 拿到宝剑后将其从地图上移除
        }
        // 检测是否碰到橙子
        if (map[new_x][new_y] == ORANGE) {
            if (player->hp < 5) {
                player->hp += 1; // 回复一点生命值
            }
            map[new_x][new_y] = EMPTY; // 吃掉橙子后将其从地图上移除
        }
        // 检测是否碰到钥匙
        if (map[new_x][new_y] == KEY) {
            player->keys += 1; // 增加钥匙
            map[new_x][new_y] = EMPTY; // 拿到钥匙后将其从地图上移除
        }
        // 检测是否碰到金币
        if (map[new_x][new_y] == GOLD) {
            player->gold += 1; // 增加金币
            map[new_x][new_y] = EMPTY; // 拾取金币后将其从地图上移除
        }
        // 检测是否碰到敌人
        if (new_x == enemy->x && new_y == enemy->y) {
            if (enemy->hp > 0) { // 只有在敌人活着的时候才进行战斗
                while (player->hp > 0 && enemy->hp > 0) {
                    player->hp -= enemy->attack;
                    enemy->hp -= player->attack;
                    // 闪烁效果
                    for (int i = 0; i < 5; i++) {
                        cleardevice();
                        Sleep(50);
                        draw_map(map, *player, *enemy, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, goldImage, wallImage, doorImage, keyImage);
                        draw_status_bar(*player, playerImage, playerWithSwordImage, heartImage);
                        Sleep(50);
                    }
                }
                if (enemy->hp <= 0) {
                    // 随机选择怪物旁边的空地掉落金币
                    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
                    for (int i = 0; i < 4; i++) {
                        int nx = enemy->x + directions[i][0];
                        int ny = enemy->y + directions[i][1];
                        if (map[nx][ny] == EMPTY) {
                            map[nx][ny] = GOLD;
                            break;
                        }
                    }
                    map[enemy->x][enemy->y] = EMPTY; // 清除敌人位置标记
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
}

// 显示启动页面
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

// 主函数
int main() {
    srand(time(NULL)); // 初始化随机数生成器
    initgraph(WIDTH * CELL_SIZE + STATUS_BAR_WIDTH, HEIGHT * CELL_SIZE);

    show_start_screen(); // 显示启动页面

    int map[HEIGHT][WIDTH];
    Character player = {1, 1, 3, 2, 0, 0, 0}; // 初始化时有三点生命值，攻击力为2，没有宝剑，金币为0，钥匙为0
    Character enemy = {0, 0, 5, 3}; // 敌人初始化，初始位置无效，将在地图中设置

    initialize_map(map);

    // 查找敌人位置
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

    // 加载图片
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

    while (1) {
        cleardevice();
        draw_map(map, player, enemy, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, goldImage, wallImage, doorImage, keyImage);
        draw_status_bar(player, playerImage, playerWithSwordImage, heartImage);

        if (kbhit()) {
            char command = getch();
            switch (command) {
                case 'w': move_player(&player, -1, 0, map, &enemy, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, heartImage, goldImage, wallImage, doorImage, keyImage); break;
                case 'a': move_player(&player, 0, -1, map, &enemy, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, heartImage, goldImage, wallImage, doorImage, keyImage); break;
                case 's': move_player(&player, 1, 0, map, &enemy, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, heartImage, goldImage, wallImage, doorImage, keyImage); break;
                case 'd': move_player(&player, 0, 1, map, &enemy, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, heartImage, goldImage, wallImage, doorImage, keyImage); break;
                case 'e':
                    if (player.hasSword) {
                        player.hasSword = 0;
                        player.attack = 2; // 更新攻击力
                        map[player.x][player.y] = SWORD; // 将宝剑丢在地上
                    } else if (map[player.x][player.y] == SWORD) {
                        player.hasSword = 1;
                        player.attack = 5; // 更新攻击力
                        map[player.x][player.y] = EMPTY; // 拿起宝剑后将其从地图上移除
                    }
                    break; // 装备/取下宝剑
            }
        }
        Sleep(100); // 控制游戏速度
    }

    closegraph();
    return 0;
}
