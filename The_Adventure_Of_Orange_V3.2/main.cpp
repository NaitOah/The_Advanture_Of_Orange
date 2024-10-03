#include <graphics.h>
#include <conio.h>
#include <ctime>
#include "map.h"
#include "character.h"
#include "game.h"
#include "menu.h"
#include "save_load.h"

#define CELL_SIZE 50
#define STATUS_BAR_WIDTH 200
#define DIALOGUE_BOX_HEIGHT 0

int main() {
    srand(time(NULL)); // 初始化随机数生成器
    initgraph(WIDTH * CELL_SIZE + STATUS_BAR_WIDTH, HEIGHT * CELL_SIZE + DIALOGUE_BOX_HEIGHT);

    bool globalRunning = true;
    int selectedSkin = 1;  // 默认皮肤

    while (globalRunning) {
        show_start_screen();

        GameState gameState;
        bool running = true;
        bool restart = false;

        while (running) {
            show_main_menu(&gameState, &running, &restart, &selectedSkin);  // 更新函数调用

            if (restart) {
                restart = false;
                continue;  // 重新启动游戏
            }

            if (running) {
                game_loop(&gameState, selectedSkin);  // 更新函数调用
            } else {
                globalRunning = false;  // 确保退出时退出整个游戏
            }
        }
    }

    closegraph();
    return 0;
}
