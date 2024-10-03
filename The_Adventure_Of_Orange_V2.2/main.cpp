#include <graphics.h>
#include <conio.h>
#include <ctime> // 包含 ctime 头文件
#include "map.h"
#include "character.h"
#include "game.h"

#define CELL_SIZE 50
#define STATUS_BAR_WIDTH 200

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
