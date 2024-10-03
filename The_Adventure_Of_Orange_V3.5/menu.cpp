#include <windows.h>
#include <mmsystem.h>
#include <graphics.h>
#include <conio.h>
#include <tchar.h>
#include <stdio.h>
#include <time.h>
#include <dirent.h>
#include "menu.h"
#include "game.h"
#include "save_load.h"

#define CELL_SIZE 50
#define STATUS_BAR_WIDTH 200
#define MUSIC_FOLDER "music"

void draw_main_menu(int selectedOption) {
    cleardevice();
    setfillcolor(BLACK); // ���ñ�����ɫΪ��ɫ
    bar(0, 0, WIDTH * CELL_SIZE + STATUS_BAR_WIDTH, HEIGHT * CELL_SIZE);

    setcolor(WHITE); // �����ı���ɫΪ��ɫ
    setbkmode(TRANSPARENT);
    setfont(30, 0, _T("����"));
    outtextxy(100, 100, _T("���˵�"));
    outtextxy(100, 200, _T("1. ����Ϸ"));
    outtextxy(100, 300, _T("2. ������Ϸ"));
    outtextxy(100, 400, _T("3. ѡ��Ƥ��"));
    outtextxy(100, 500, _T("4. ����"));
    outtextxy(100, 600, _T("5. �˳���Ϸ"));

    if (selectedOption == 1) {
        outtextxy(80, 200, _T(">"));
    } else if (selectedOption == 2) {
        outtextxy(80, 300, _T(">"));
    } else if (selectedOption == 3) {
        outtextxy(80, 400, _T(">"));
    } else if (selectedOption == 4) {
        outtextxy(80, 500, _T(">"));
    } else if (selectedOption == 5) {
        outtextxy(80, 600, _T(">"));
    }
}

void draw_other_menu(int selectedOption) {
    cleardevice();
    setfillcolor(BLACK); // ���ñ�����ɫΪ��ɫ
    bar(0, 0, WIDTH * CELL_SIZE + STATUS_BAR_WIDTH, HEIGHT * CELL_SIZE);

    setcolor(WHITE); // �����ı���ɫΪ��ɫ
    setbkmode(TRANSPARENT);
    setfont(30, 0, _T("����"));
    outtextxy(100, 100, _T("����"));
    outtextxy(100, 200, _T("1. ����"));
    outtextxy(100, 300, _T("2. ���ֽ̳�"));

    if (selectedOption == 1) {
        outtextxy(80, 200, _T(">"));
    } else if (selectedOption == 2) {
        outtextxy(80, 300, _T(">"));
    }
}

void draw_music_menu(int selectedOption, const char* musicFiles[], int numFiles) {
    cleardevice();
    setfillcolor(BLACK); // ���ñ�����ɫΪ��ɫ
    bar(0, 0, WIDTH * CELL_SIZE + STATUS_BAR_WIDTH, HEIGHT * CELL_SIZE);

    setcolor(WHITE); // �����ı���ɫΪ��ɫ
    setbkmode(TRANSPARENT);
    setfont(30, 0, _T("����"));
    outtextxy(100, 100, _T("ѡ������"));

    int yOffset = 150;
    for (int i = 0; i < numFiles; i++) {
        outtextxy(120, yOffset + i * 60, musicFiles[i]);
        if (selectedOption == i + 1) {
            outtextxy(100, yOffset + i * 60, _T(">"));
        }
    }
}

void show_other_menu() {
    int selectedOption = 1;

    while (1) {
        draw_other_menu(selectedOption);

        if (kbhit()) {
            int command = getch();
            switch (command) {
                case '1':
                    selectedOption = 1;
                    break;
                case '2':
                    selectedOption = 2;
                    break;
                case 13:  // �س���
                    if (selectedOption == 1) {
                        show_music_menu();
                    }else if (selectedOption == 2) {
                        int scrollOffset = 0;
                        const int scrollStep = 20;
                        const int maxScrollOffset = 1600; // ����ʵ���ı����ݸ߶ȵ���
                        bool display = true;

                        while (display) {
                            cleardevice();

                            setcolor(WHITE); // �����ı���ɫΪ��ɫ
                            setbkmode(TRANSPARENT);

                            // ������ʾ
                            setfont(20, 0, _T("����"));
                            outtextxy(50, 0 - scrollOffset, _T("����W�����͡�S���������Ķ�"));

                            // ���ñ�������Ϊ�����Ӵ�
                            setfont(30, 0, _T("����"));
                            outtextxy(50, 40 - scrollOffset, _T("���ֽ̳̣������ӵ�ð�ա�"));

                            // �����ӱ�������Ϊ�����Ӵ�
                            setfont(25, 0, _T("����"));
                            outtextxy(50, 80 - scrollOffset, _T("��������:"));

                            // ������������
                            setfont(20, 0, _T("����"));
                            outtextxy(50, 110 - scrollOffset, _T("��ңԶ��˹ά�۴�½�ϣ���һ�����ٵ�������"));
                            outtextxy(50, 140 - scrollOffset, _T("��������һλ�����������ĳ��ӹ��������ֶ���"));
                            outtextxy(50, 170 - scrollOffset, _T("�ǹ�������ʵ�����ͺ����ѣ�����һ��ȹ����������õ�ʱ�⡣"));
                            outtextxy(50, 200 - scrollOffset, _T("Ȼ������һ�죬а���ħ������������������˳��ӹ�����"));
                            outtextxy(50, 230 - scrollOffset, _T("����������һ�����ܵĵط���ħ��ʩ����ǿ���ħ����ӡ��"));
                            outtextxy(50, 260 - scrollOffset, _T("ֻ���¸����Ļ�������˲��ܴ��Ʒ�ӡ���ȳ�������"));
                            outtextxy(50, 290 - scrollOffset, _T("���ֶ�������ԥ��̤����ð��֮�ã�����Ҫ�ҵ���˵�еĽ�ɫ���ӣ�"));
                            outtextxy(50, 320 - scrollOffset, _T("���ħ�����ȳ����İ��Ĺ�������������������¸ҵ����ֶ�����׼��������"));

                            // ��Ϸ����
                            setfont(25, 0, _T("����"));
                            outtextxy(50, 360 - scrollOffset, _T("��Ϸ����:"));

                            setfont(20, 0, _T("����"));
                            outtextxy(50, 390 - scrollOffset, _T("W���������ƶ�"));
                            outtextxy(50, 420 - scrollOffset, _T("A���������ƶ�"));
                            outtextxy(50, 450 - scrollOffset, _T("S���������ƶ�"));
                            outtextxy(50, 480 - scrollOffset, _T("D���������ƶ�"));
                            outtextxy(50, 510 - scrollOffset, _T("E����ȡ�»�װ������"));
                            outtextxy(50, 540 - scrollOffset, _T("U����ʹ�ý�ɫ���ӻָ�����"));
                            outtextxy(50, 570 - scrollOffset, _T("P����������Ϸ"));
                            outtextxy(50, 600 - scrollOffset, _T("ESC�����˳���Ϸ"));

                            // ��ϷĿ��
                            setfont(25, 0, _T("����"));
                            outtextxy(50, 640 - scrollOffset, _T("��ϷĿ��:"));

                            setfont(20, 0, _T("����"));
                            outtextxy(50, 670 - scrollOffset, _T("1. �ռ����������ֶ���Ҫ�ҵ���װ������������ǿ��������"));
                            outtextxy(50, 700 - scrollOffset, _T("2. ��ܵ��ˣ�ʹ�ñ������������赲��ǰ����·�ϵĵ��ˡ�"));
                            outtextxy(50, 730 - scrollOffset, _T("3. �ռ���ɫ���ӣ�ʹ�ý�ɫ���ӿ����ڽ���ʱ�ָ̻�����ֵ��"));
                            outtextxy(50, 760 - scrollOffset, _T("4. �ҵ�Կ�ף��ռ�Կ���Դ򿪱���ס���š�"));
                            outtextxy(50, 790 - scrollOffset, _T("5. ̽����ͼ����ϸ̽��ÿһ�㣬�ҵ�������Ҫ����Ʒ��������"));
                            outtextxy(50, 820 - scrollOffset, _T("6. �ȳ����ӹ������ҵ����ȳ��������ڵڶ���ĳ��ӹ��������ð�ա�"));

                            // ��Ʒ����
                            setfont(25, 0, _T("����"));
                            outtextxy(50, 860 - scrollOffset, _T("��Ʒ����:"));

                            setfont(20, 0, _T("����"));
                            outtextxy(50, 890 - scrollOffset, _T("�������������ֶ��Ĺ��������ҵ�������E��װ����"));
                            outtextxy(50, 920 - scrollOffset, _T("���ӣ��������ֶ�������ֵ���Ե����Զ��ָ�һ������ֵ��"));
                            outtextxy(50, 950 - scrollOffset, _T("��ɫ���ӣ���ȫ�ָ����ֶ�������ֵ������ʱ���һ������ֵ���ޣ���U��ʹ�á�"));
                            outtextxy(50, 980 - scrollOffset, _T("Կ�ף������򿪱���ס���š�"));
                            outtextxy(50, 1010 - scrollOffset, _T("��ң��ռ���ң��������ض��ص�ʹ�á�"));

                            // ���˽���
                            setfont(25, 0, _T("����"));
                            outtextxy(50, 1050 - scrollOffset, _T("���˽���:"));

                            setfont(20, 0, _T("����"));
                            outtextxy(50, 1080 - scrollOffset, _T("ʷ��ķ"));
                            outtextxy(80, 1110 - scrollOffset, _T("����ֵ��5"));
                            outtextxy(80, 1140 - scrollOffset, _T("��������3"));
                            outtextxy(80, 1170 - scrollOffset, _T("��������ͨ�ĵ��ˣ���������Ϸ�ĵ�һ�㡣���ǻ��赲���ֶ���ǰ������Ҫ��ʿ�ñ����������ǡ�"));

                            outtextxy(50, 1210 - scrollOffset, _T("ħ��"));
                            outtextxy(80, 1240 - scrollOffset, _T("����ֵ��5"));
                            outtextxy(80, 1270 - scrollOffset, _T("��������5"));
                            outtextxy(80, 1300 - scrollOffset, _T("������ǿ��ĵ��ˣ���������Ϸ�ĵڶ��㡣���Ǳ���ͨ���˸�ǿ����Ҫ����С�ĶԸ���"));

                            // ��ɫ����
                            setfont(25, 0, _T("����"));
                            outtextxy(50, 1350 - scrollOffset, _T("��ɫ����:"));

                            setfont(20, 0, _T("����"));
                            outtextxy(50, 1380 - scrollOffset, _T("���ֶ� (Player)"));
                            outtextxy(80, 1410 - scrollOffset, _T("����ֵ��5"));
                            outtextxy(80, 1440 - scrollOffset, _T("����������ʼ������Ϊ2��װ�������󹥻������ӵ�5��"));
                            outtextxy(80, 1470 - scrollOffset, _T("�������������ʿ���Ȱ�ð�ա�����Ŀ���ǽ��˹ά�۴�½��ħ����ӡ�����ȳ����ӹ�����"));

                            outtextxy(50, 1510 - scrollOffset, _T("ɥ��"));
                            outtextxy(80, 1540 - scrollOffset, _T("�������Ѻõ�NPC��������ֶ��ṩ��Ҫ����Ϣ�Ͱ�����"));

                            outtextxy(50, 1580 - scrollOffset, _T("���ӹ���"));
                            outtextxy(80, 1610 - scrollOffset, _T("��������ħ�������ĳ��ӹ��������ֶ���Ҫ�ȳ��Ĺؼ���������ֶ��ɹ������ʱ���ɴ�����֡�"));

                            // ��ϷС��ʿ
                            setfont(25, 0, _T("����"));
                            outtextxy(50, 1650 - scrollOffset, _T("��ϷС��ʿ:"));

                            setfont(20, 0, _T("����"));
                            outtextxy(50, 1680 - scrollOffset, _T("������ȣ��ǵö���ʹ��P��������Ϸ���ȣ��������⵼�µĽ��ȶ�ʧ��"));
                            outtextxy(50, 1710 - scrollOffset, _T("����ʹ�õ��ߣ��ں��ʵ�ʱ��ʹ�ý�ɫ���ӣ����԰������ڹؼ�ʱ�̷���Ϊʤ��"));
                            outtextxy(50, 1740 - scrollOffset, _T("̽��ÿһ�����䣺��Ϸ�е�ÿһ�����䶼�п��ܲ��ű���ĵ��ߺ��������¸�̽���ɣ�"));
                            outtextxy(50, 1770 - scrollOffset, _T("ע����˵�λ�ã�ÿ�����˶��в�ͬ�Ĺ�����������ֵ�������������ѡ��ս�����ԡ�"));

                            // ��Ϸ����
                            setfont(25, 0, _T("����"));
                            outtextxy(50, 1810 - scrollOffset, _T("��Ϸ����:"));

                            setfont(20, 0, _T("����"));
                            outtextxy(50, 1840 - scrollOffset, _T("1. ̽����һ�㣺�ռ�������Կ�׺ͳ��ӣ����ʷ��ķ��"));
                            outtextxy(50, 1870 - scrollOffset, _T("2. �ҵ���¥��¥�ݣ�����ڶ������ð�ա�"));
                            outtextxy(50, 1900 - scrollOffset, _T("3. ̽���ڶ��㣺��ܸ�ǿ���ħ����Ѱ�ҳ��ӹ�����λ�á�"));
                            outtextxy(50, 1930 - scrollOffset, _T("4. �ҵ����ӹ������ڵڶ����ҵ����ӹ������ɹ���ȹ�����չʾ����ҳ�棬��Ϸʤ����"));

                            // ��������
                            setfont(25, 0, _T("����"));
                            outtextxy(50, 1970 - scrollOffset, _T("��������:"));

                            setfont(20, 0, _T("����"));
                            outtextxy(50, 2000 - scrollOffset, _T("�����ֶ��ҵ�����ȳ��ӹ���ʱ����Ϸ��չʾһ����ף�ɹ���ͼƬ����ʾ���ֶ��ɹ��ȳ�������"));
                            outtextxy(50, 2030 - scrollOffset, _T("ף���ڡ����ӵ�ð�ա��������죬��ʿ���ֶ��Ĵ���ð�յ�����������"));

                            setfont(25, 0, _T("����"));
                            outtextxy(50, 2070 - scrollOffset, _T("�� ESC ���˳��̳̽���"));


                            // ������������ʵ�ֹ���
                            if (kbhit()) {
                                char key = getch();
                                if (key == 'w' && scrollOffset > 0) {
                                    scrollOffset -= scrollStep;
                                } else if (key == 's' && scrollOffset < maxScrollOffset) {
                                    scrollOffset += scrollStep;
                                } else if (key == 27) { // ESC ���˳��̳̽���
                                    display = false;
                                }
                            }

                            Sleep(50);
                        }
                    }

                    return;
                case 27:  // ESC ��
                    return;
            }
        }
        Sleep(100);
    }
}

void show_music_menu() {
    DIR *dir;
    struct dirent *ent;
    const char *musicFiles[100];
    int numFiles = 0;

    if ((dir = opendir(MUSIC_FOLDER)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            // ����ļ��Ƿ��ǳ����ļ�����չ���� .wav �� .mp3
            char filepath[256];
            sprintf(filepath, "%s/%s", MUSIC_FOLDER, ent->d_name);

            if (GetFileAttributes(filepath) & FILE_ATTRIBUTE_DIRECTORY) {
                continue;
            }

            // ֻ��� .wav �� .mp3 �ļ�
            if (strstr(ent->d_name, ".wav") != NULL || strstr(ent->d_name, ".mp3") != NULL) {
                musicFiles[numFiles] = strdup(ent->d_name); // �����ļ���
                numFiles++;
            }
        }
        closedir(dir);
    } else {
        perror("�޷��������ļ���");
        return;
    }

    int selectedOption = 1;

    while (1) {
        draw_music_menu(selectedOption, musicFiles, numFiles);

        if (kbhit()) {
            int command = getch();
            if (command >= '1' && command <= '0' + numFiles) {
                selectedOption = command - '0';
            } else if (command == 13) {  // �س���
                play_music(musicFiles[selectedOption - 1]);
                cleardevice();
                setcolor(WHITE); // �����ı���ɫΪ��ɫ
                setbkmode(TRANSPARENT);
                setfont(30, 0, _T("����"));
                outtextxy((WIDTH * CELL_SIZE + STATUS_BAR_WIDTH) / 2 - 100, HEIGHT * CELL_SIZE / 2, _T("����ѡ��ɹ�"));
                outtextxy((WIDTH * CELL_SIZE + STATUS_BAR_WIDTH) / 2 - 150, HEIGHT * CELL_SIZE / 2 + 50, _T("�����������"));
                getch();
                return;
            } else if (command == 27) {  // ESC ��
                return;
            }
        }
        Sleep(100);
    }
}

void play_music(const char *filename) {
    char filepath[256];
    sprintf(filepath, "%s\\%s", MUSIC_FOLDER, filename);

    // ʹ�� PlaySound ������Ƶ�ļ�
    if (!PlaySound(filepath, NULL, SND_FILENAME | SND_LOOP | SND_ASYNC)) {
        printf("Error playing file: %lu\n", GetLastError());
    }
}

void show_skin_menu(int *selectedSkin) {
    int selectedOption = 1;

    while (1) {
        draw_skin_menu(selectedOption, *selectedSkin);

        if (kbhit()) {
            int command = getch();
            switch (command) {
                case '1':
                    selectedOption = 1;
                    break;
                case '2':
                    selectedOption = 2;
                    break;
                case 13:  // �س���
                    *selectedSkin = selectedOption;
                    cleardevice();
                    setcolor(WHITE); // �����ı���ɫΪ��ɫ
                    setbkmode(TRANSPARENT);
                    setfont(30, 0, _T("����"));
                    outtextxy((WIDTH * CELL_SIZE + STATUS_BAR_WIDTH) / 2 - 100, HEIGHT * CELL_SIZE / 2, _T("Ƥ��ѡ��ɹ�"));
                    outtextxy((WIDTH * CELL_SIZE + STATUS_BAR_WIDTH) / 2 - 150, HEIGHT * CELL_SIZE / 2 + 50, _T("�����������"));
                    getch();
                    return;
                case 27:  // ESC ��
                    return;
            }
        }
        Sleep(100);
    }
}

void draw_skin_menu(int selectedOption, int selectedSkin) {
    cleardevice();
    setfillcolor(BLACK); // ���ñ�����ɫΪ��ɫ
    bar(0, 0, WIDTH * CELL_SIZE + STATUS_BAR_WIDTH, HEIGHT * CELL_SIZE);

    setcolor(WHITE); // �����ı���ɫΪ��ɫ
    setbkmode(TRANSPARENT);
    setfont(30, 0, _T("����"));
    outtextxy(100, 100, _T("ѡ��Ƥ��"));
    outtextxy(100, 200, _T("1. Ƥ�� 1"));
    outtextxy(100, 300, _T("2. Ƥ�� 2"));

    PIMAGE skin1Image = newimage();
    PIMAGE skin2Image = newimage();
    getimage(skin1Image, "images/player.png");
    getimage(skin2Image, "images/player_2.png");

    putimage_withalpha(NULL, skin1Image, 300, 200);
    putimage_withalpha(NULL, skin2Image, 300, 300);

    if (selectedOption == 1) {
        outtextxy(80, 200, _T(">"));
    } else if (selectedOption == 2) {
        outtextxy(80, 300, _T(">"));
    }
}

void show_main_menu(GameState *gameState, bool *running, bool *restart, int *selectedSkin) {
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
                case '4':
                    selectedOption = 4;
                    break;
                case '5':
                    selectedOption = 5;
                    break;
                case 13:  // �س���
                    if (selectedOption == 1) {
                        initialize_game(gameState, true);
                        return;
                    } else if (selectedOption == 2) {
                        show_load_menu(gameState, running, restart);
                        if (*restart) return; // �����Ҫ������Ϸ��ֱ�ӷ���
                        if (*running) return;
                    } else if (selectedOption == 3) {
                        show_skin_menu(selectedSkin);
                    } else if (selectedOption == 4) {
                        show_other_menu();
                    } else if (selectedOption == 5) {
                        *running = false;
                        return;
                    }
                    break;
                case 27:  // ESC ��
                    *running = false;
                    return;
            }
        }
        Sleep(100);
    }
}

void draw_load_menu(int selectedOption, char saveFiles[][100], int numFiles) {
    cleardevice();
    setfillcolor(BLACK); // ���ñ�����ɫΪ��ɫ
    bar(0, 0, WIDTH * CELL_SIZE + STATUS_BAR_WIDTH, HEIGHT * CELL_SIZE);

    setcolor(WHITE); // �����ı���ɫΪ��ɫ
    setbkmode(TRANSPARENT);
    setfont(20, 0, _T("����"));
    outtextxy(100, 50, _T("������Ϸ"));

    int yOffset = 150;
    for (int i = 0; i < numFiles; i++) {
        TCHAR displayText[120];
        _stprintf(displayText, _T("%d. %s"), i + 1, saveFiles[i]); // ������
        outtextxy(120, yOffset + i * 60, displayText);
        if (selectedOption == i + 1) {
            outtextxy(100, yOffset + i * 60, _T(">"));
        }
    }

    outtextxy(120, yOffset + (numFiles + 1) * 60, _T("�� D ɾ���浵"));

    if (selectedOption == numFiles + 1) {
        outtextxy(100, yOffset + numFiles * 60, _T(">"));
    }
}

void show_load_menu(GameState *gameState, bool *running, bool *restart) {
    int selectedOption = 1;
    char saveFiles[6][100];
    int numFiles = 0;

    for (int i = 1; i <= 5; i++) {
        if (check_save_exists(i)) {
            sprintf(saveFiles[numFiles], "�浵 %d (%s)", i, get_save_time(i));
            numFiles++;
        } else {
            sprintf(saveFiles[numFiles], "�浵 %d (��)", i);
            numFiles++;
        }
    }
    sprintf(saveFiles[numFiles], "�������˵�");
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
                                sprintf(saveFiles[i-1], "�浵 %d (%s)", i, get_save_time(i));
                            } else {
                                sprintf(saveFiles[i-1], "�浵 %d (��)", i);
                            }
                        }
                    }
                    break;
                case 13:  // �س���
                    if (selectedOption >= 1 && selectedOption <= 5) {
                        if (check_save_exists(selectedOption)) {
                            load_game(gameState, selectedOption);
                            return;
                        }
                    } else if (selectedOption == 6) {
                        *restart = true;  // ����Ϊ��Ҫ������Ϸ
                        return;
                    }
                    break;
                case 27:  // ESC ��
                    return;
            }
        }
        Sleep(100);
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
    setbkmode(TRANSPARENT); // ���ñ���ģʽΪ͸��
    setfont(30, 0, _T("����"));
    outtextxy((WIDTH * CELL_SIZE + STATUS_BAR_WIDTH) / 2 - 100, 450, _T("���������ʼ��Ϸ"));

    getch();
    cleardevice();
}
