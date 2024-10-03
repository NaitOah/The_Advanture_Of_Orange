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
    srand(time(NULL)); // ��ʼ�������������
    initgraph(WIDTH * CELL_SIZE + STATUS_BAR_WIDTH, HEIGHT * CELL_SIZE + DIALOGUE_BOX_HEIGHT);

    bool globalRunning = true;

    while (globalRunning) {
        show_start_screen();

        GameState gameState;
        bool running = true;
        bool restart = false;  // ��� restart ����

        while (running) {
            show_main_menu(&gameState, &running, &restart);

            if (restart) {
                restart = false;
                continue;  // ����������Ϸ
            }

            if (running) {
                game_loop(&gameState);
            } else {
                globalRunning = false;  // ȷ���˳�ʱ�˳�������Ϸ
            }
        }
    }

    closegraph();
    return 0;
}
