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
    int selectedSkin = 1;  // Ĭ��Ƥ��

    while (globalRunning) {
        show_start_screen();

        GameState gameState;
        bool running = true;
        bool restart = false;

        while (running) {
            show_main_menu(&gameState, &running, &restart, &selectedSkin);  // ���º�������

            if (restart) {
                restart = false;
                continue;  // ����������Ϸ
            }

            if (running) {
                game_loop(&gameState, selectedSkin);  // ���º�������
            } else {
                globalRunning = false;  // ȷ���˳�ʱ�˳�������Ϸ
            }
        }
    }

    closegraph();
    return 0;
}
