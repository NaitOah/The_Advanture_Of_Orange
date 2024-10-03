#include <graphics.h>
#include <conio.h>
#include <tchar.h>
#include <stdio.h>
#include <time.h>
#include "menu.h"
#include "game.h"
#include "save_load.h"

#define CELL_SIZE 50
#define STATUS_BAR_WIDTH 200

void draw_main_menu(int selectedOption) {
    cleardevice();
    setfillcolor(BLACK);
    bar(0, 0, WIDTH * CELL_SIZE + STATUS_BAR_WIDTH, HEIGHT * CELL_SIZE);

    setcolor(WHITE);
    setbkmode(TRANSPARENT);
    setfont(30, 0, _T("宋体"));
    outtextxy(100, 100, _T("主菜单"));
    outtextxy(100, 200, _T("1. 新游戏"));
    outtextxy(100, 300, _T("2. 载入游戏"));
    outtextxy(100, 400, _T("3. 退出游戏"));

    if (selectedOption == 1) {
        outtextxy(80, 200, _T(">"));
    } else if (selectedOption == 2) {
        outtextxy(80, 300, _T(">"));
    } else if (selectedOption == 3) {
        outtextxy(80, 400, _T(">"));
    }
}

void draw_load_menu(int selectedOption, char saveFiles[][100], int numFiles) {
    cleardevice();
    setfillcolor(BLACK);
    bar(0, 0, WIDTH * CELL_SIZE + STATUS_BAR_WIDTH, HEIGHT * CELL_SIZE);

    setcolor(WHITE);
    setbkmode(TRANSPARENT);
    setfont(20, 0, _T("宋体"));
    outtextxy(100, 50, _T("载入游戏"));

    int yOffset = 150;
    for (int i = 0; i < numFiles; i++) {
        TCHAR displayText[120];
        _stprintf(displayText, _T("%d. %s"), i + 1, saveFiles[i]); // 添加序号
        outtextxy(120, yOffset + i * 60, displayText);
        if (selectedOption == i + 1) {
            outtextxy(100, yOffset + i * 60, _T(">"));
        }
    }

    outtextxy(120, yOffset + (numFiles + 1) * 60, _T("按 D 删除存档"));

    if (selectedOption == numFiles + 1) {
        outtextxy(100, yOffset + numFiles * 60, _T(">"));
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

void show_main_menu(GameState *gameState, bool *running, bool *restart) {
    int selectedOption = 1;

    while (1) {
        draw_main_menu(selectedOption);

        if (kbhit()) {
            int command = getch();
            switch (command) {
                case '1':
                    selectedOption = 1;
                    break;
                case '2':
                    selectedOption = 2;
                    break;
                case '3':
                    selectedOption = 3;
                    break;
                case 13:  // 回车键
                    if (selectedOption == 1) {
                        initialize_game(gameState, true);
                        return;
                    } else if (selectedOption == 2) {
                        show_load_menu(gameState, running, restart);
                        if (*restart) return; // 如果需要重启游戏，直接返回
                        if (*running) return;
                    } else if (selectedOption == 3) {
                        *running = false;
                        return;
                    }
                    break;
                case 27:  // ESC 键
                    *running = false;
                    return;
            }
        }
        Sleep(100);
    }
}

void show_load_menu(GameState *gameState, bool *running, bool *restart) {
    int selectedOption = 1;
    char saveFiles[6][100];
    int numFiles = 0;

    for (int i = 1; i <= 5; i++) {
        if (check_save_exists(i)) {
            sprintf(saveFiles[numFiles], "存档 %d (%s)", i, get_save_time(i));
            numFiles++;
        } else {
            sprintf(saveFiles[numFiles], "存档 %d (空)", i);
            numFiles++;
        }
    }
    sprintf(saveFiles[numFiles], "返回主菜单");
    numFiles++;

    while (1) {
        draw_load_menu(selectedOption, saveFiles, numFiles);

        if (kbhit()) {
            int command = getch();
            switch (command) {
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                    selectedOption = command - '0';
                    break;
                case 'd':
                case 'D':
                    if (selectedOption >= 1 && selectedOption <= 5 && check_save_exists(selectedOption)) {
                        delete_save(selectedOption);
                        for (int i = 1; i <= 5; i++) {
                            if (check_save_exists(i)) {
                                sprintf(saveFiles[i-1], "存档 %d (%s)", i, get_save_time(i));
                            } else {
                                sprintf(saveFiles[i-1], "存档 %d (空)", i);
                            }
                        }
                    }
                    break;
                case 13:  // 回车键
                    if (selectedOption >= 1 && selectedOption <= 5) {
                        if (check_save_exists(selectedOption)) {
                            load_game(gameState, selectedOption);
                            return;
                        }
                    } else if (selectedOption == 6) {
                        *restart = true;  // 重新启动游戏
                        return;
                    }
                    break;
                case 27:  // ESC 键
                    return;
            }
        }
        Sleep(100);
    }
}
