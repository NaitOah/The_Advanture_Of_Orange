#include <graphics.h>
#include <conio.h>
#include <ctime>
#include "map.h"
#include "character.h"
#include "game.h"
#include "menu.h"
#include "player.h"
#include "draw.h"

#define CELL_SIZE 50
#define STATUS_BAR_WIDTH 200
#define DIALOGUE_BOX_HEIGHT 0

int main() {
    srand(time(NULL)); // 初始化随机数生成器
    initgraph(WIDTH * CELL_SIZE + STATUS_BAR_WIDTH, HEIGHT * CELL_SIZE + DIALOGUE_BOX_HEIGHT);

    show_start_screen(); // 显示启动页面

    int map1[HEIGHT][WIDTH];
    int map2[HEIGHT][WIDTH];

    initialize_map(map1, 1);
    initialize_map(map2, 2);

    FloorState floor1State = {0};
    FloorState floor2State = {0};

    memcpy(floor1State.map, map1, sizeof(map1));
    memcpy(floor2State.map, map2, sizeof(map2));

    Character player = {1, 1, 3, 2, 0, 0, 0}; // 初始化时有三点生命值，攻击力为2，没有宝剑，金币为0，钥匙为0，金色橙子为0
    Character enemy1 = {8, 1, 5, 3}; // 第一层敌人初始化位置和属性
    Character enemy2 = {0, 0, 0, 0}; // 第二层没有敌人

    floor1State.player = player;
    floor1State.enemy = enemy1;
    floor2State.player = player;
    floor2State.enemy = enemy2;

    int currentFloor = 1;

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
    getimage(npc1Image, "images/npc_1.png");
    getimage(goldOrangeImage, "images/gold_orange.png");
    getimage(upStairsImage, "images/up_stairs.png");
    getimage(downStairsImage, "images/down_stairs.png");

    while (1) {
        cleardevice();
        if (currentFloor == 1) {
            draw_map(floor1State.map, player, floor1State.enemy, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, goldImage, wallImage, doorImage, keyImage, npc1Image, upStairsImage, downStairsImage, true);
            draw_status_bar(player, playerImage, playerWithSwordImage, heartImage, goldOrangeImage);
        } else {
            draw_map(floor2State.map, player, floor2State.enemy, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, goldImage, wallImage, doorImage, keyImage, npc1Image, upStairsImage, downStairsImage, false);
            draw_status_bar(player, playerImage, playerWithSwordImage, heartImage, goldOrangeImage);
        }

        if (kbhit()) {
            char command = getch();
            switch (command) {
                case 'w': move_player(&player, -1, 0, floor1State, floor2State, currentFloor, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, heartImage, goldImage, wallImage, doorImage, keyImage, npc1Image, upStairsImage, downStairsImage); break;
                case 'a': move_player(&player, 0, -1, floor1State, floor2State, currentFloor, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, heartImage, goldImage, wallImage, doorImage, keyImage, npc1Image, upStairsImage, downStairsImage); break;
                case 's': move_player(&player, 1, 0, floor1State, floor2State, currentFloor, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, heartImage, goldImage, wallImage, doorImage, keyImage, npc1Image, upStairsImage, downStairsImage); break;
                case 'd': move_player(&player, 0, 1, floor1State, floor2State, currentFloor, playerImage, playerWithSwordImage, swordImage, orangeImage, enemyImage, heartImage, goldImage, wallImage, doorImage, keyImage, npc1Image, upStairsImage, downStairsImage); break;
                case 'e':
                    if (player.hasSword) {
                        player.hasSword = 0;
                        player.attack = 2; // 更新攻击力
                        if (currentFloor == 1) {
                            floor1State.map[player.x][player.y] = SWORD; // 将宝剑丢在地上
                        } else {
                            floor2State.map[player.x][player.y] = SWORD; // 将宝剑丢在地上
                        }
                    } else if (currentFloor == 1 && floor1State.map[player.x][player.y] == SWORD) {
                        player.hasSword = 1;
                        player.attack = 5; // 更新攻击力
                        floor1State.map[player.x][player.y] = EMPTY; // 拿起宝剑后将其从地图上移除
                    } else if (currentFloor == 2 && floor2State.map[player.x][player.y] == SWORD) {
                        player.hasSword = 1;
                        player.attack = 5; // 更新攻击力
                        floor2State.map[player.x][player.y] = EMPTY; // 拿起宝剑后将其从地图上移除
                    }
                    break; // 装备/取下宝剑
                case 'u':
                    if (player.hasGoldOrange) {
                        player.hp = 6; // 回满血量，假设初始最大血量为5
                        player.hasGoldOrange = 0; // 使用后金色橙子消失
                    }
                    break;
            }
        }
        Sleep(100); // 控制游戏速度
    }

    closegraph();
    return 0;
}
