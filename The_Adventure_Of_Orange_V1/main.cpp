#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <tchar.h>

#define WIDTH 15
#define HEIGHT 15
#define CELL_SIZE 50
#define STATUS_BAR_WIDTH 200

// 地图元素
#define EMPTY 0
#define WALL 1
#define PLAYER 2
#define ENEMY 3
#define ITEM 4
#define SWORD 5
#define ORANGE 6

// 玩家和敌人结构体
typedef struct {
    int x;
    int y;
    int hp;
    int attack;
    int hasSword; // 增加标志以表示玩家是否有宝剑
} Character;

// 初始化地图
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
    // 放置宝剑和橙子
    map[5][5] = SWORD;
    map[3][3] = ORANGE;
    map[4][4] = ORANGE;
    map[6][6] = ORANGE;
    // 放置敌人
    map[HEIGHT-2][WIDTH-2] = ENEMY;
}

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

    outtextxy(WIDTH * CELL_SIZE + 10, 200, _T("按 e 键"));
    outtextxy(WIDTH * CELL_SIZE + 10, 230, _T("装备/取下宝剑"));

    outtextxy(WIDTH * CELL_SIZE + 10, 300, _T("生命值:"));
    for (int i = 0; i < player.hp; i++) {
        putimage_withalpha(NULL, heartImage, WIDTH * CELL_SIZE + 10 + i * 30, 330);
    }
}

// 绘制地图
void draw_map(int map[HEIGHT][WIDTH], Character player, Character enemy, PIMAGE playerImage, PIMAGE playerWithSwordImage, PIMAGE swordImage, PIMAGE orangeImage, PIMAGE enemyImage) {
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

    // 绘制橙子
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (map[i][j] == ORANGE) {
                putimage_withalpha(NULL, orangeImage, j * CELL_SIZE, i * CELL_SIZE);
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
void move_player(Character *player, int dx, int dy, int map[HEIGHT][WIDTH], Character *enemy, PIMAGE playerImage, PIMAGE playerWithSwordImage, PIMAGE swordImage, PIMAGE orangeImage, PIMAGE enemyImage, PIMAGE heartImage) {
    int new_x = player->x + dx;
    int new_y = player->y + dy;
    if (map[new_x][new_y] != WALL) {
        player->x = new_x;
        player->y = new_y;
        // 检测是否碰到宝剑
        if (map[new_x][new_y] == SWORD) {
            player->hasSword = 1;
            map[new_x][new_y] = EMPTY; // 拿到宝剑后将其从地图上移除
        }
        // 检测是否碰到橙子
        if (map[new_x][new_y] == ORANGE) {
            if (player->hp < 5) {
                player->hp += 1; // 回复一点生命值
            }
            map[new_x][new_y] = EMPTY; // 吃掉橙子后将其从地图上移除
        }
        // 检测是否碰到敌人
        if (new_x == enemy->x && new_y == enemy->y) {
            while (player->hp > 0 && enemy->hp > 0) {
                player->hp -= enemy->attack;
                enemy->hp -= (player->hasSword ? 5 : 2);
                // 闪烁效果
                for (int i = 0; i < 5; i++) {
                    cleardevice();
                    Sleep(50);
                    draw_map(map, *player, *enemy, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage);
                    draw_status_bar(*player, playerImage, playerWithSwordImage, heartImage);
                    Sleep(50);
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

// 主函数
int main() {
    initgraph(WIDTH * CELL_SIZE + STATUS_BAR_WIDTH, HEIGHT * CELL_SIZE);

    int map[HEIGHT][WIDTH];
    Character player = {1, 1, 3, 10, 0}; // 初始化时有三点生命值，没有宝剑
    Character enemy = {HEIGHT-2, WIDTH-2, 5, 3}; // 敌人初始化，血量为5，攻击力为3

    initialize_map(map);

    PIMAGE playerImage = newimage();
    PIMAGE playerWithSwordImage = newimage();
    PIMAGE swordImage = newimage();
    PIMAGE heartImage = newimage();
    PIMAGE orangeImage = newimage();
    PIMAGE enemyImage = newimage();

    // 加载图片
    getimage(playerImage, "images/player.png");
    getimage(playerWithSwordImage, "images/player_with_sword.png");
    getimage(swordImage, "images/sword.png");
    getimage(heartImage, "images/heart.png");
    getimage(orangeImage, "images/orange.png");
    getimage(enemyImage, "images/enemy_1.png");

    while (1) {
        cleardevice();
        draw_map(map, player, enemy, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage);
        draw_status_bar(player, playerImage, playerWithSwordImage, heartImage);

        if (kbhit()) {
            char command = getch();
            switch (command) {
                case 'w': move_player(&player, -1, 0, map, &enemy, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, heartImage); break;
                case 'a': move_player(&player, 0, -1, map, &enemy, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, heartImage); break;
                case 's': move_player(&player, 1, 0, map, &enemy, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, heartImage); break;
                case 'd': move_player(&player, 0, 1, map, &enemy, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, heartImage); break;
                case 'e': player.hasSword = !player.hasSword; break; // 装备/取下宝剑
            }
        }
        Sleep(100); // 控制游戏速度
    }

    closegraph();
    return 0;
}

