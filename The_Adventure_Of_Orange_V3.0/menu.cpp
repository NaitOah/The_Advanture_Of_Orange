#include <graphics.h>
#include <conio.h>
#include <tchar.h> // �����һ��
#include "menu.h"
#include "map.h"

#define CELL_SIZE 50
#define STATUS_BAR_WIDTH 200

void show_start_screen() {
    cleardevice();
    setfillcolor(WHITE);
    bar(0, 0, WIDTH * CELL_SIZE + STATUS_BAR_WIDTH, HEIGHT * CELL_SIZE);

    PIMAGE logo = newimage();
    getimage(logo, "images/TAOO.png");
    putimage((WIDTH * CELL_SIZE + STATUS_BAR_WIDTH - 950) / 2, 50, logo);

    setcolor(BLACK);
    setbkmode(TRANSPARENT); // ���ñ���ģʽΪ͸��
    setfont(30, 0, _T("����"));
    outtextxy((WIDTH * CELL_SIZE + STATUS_BAR_WIDTH) / 2 - 100, 450, _T("���������ʼ��Ϸ"));

    getch();
    cleardevice();
}
