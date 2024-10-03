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
    setfillcolor(BLACK); // 设置背景颜色为黑色
    bar(0, 0, WIDTH * CELL_SIZE + STATUS_BAR_WIDTH, HEIGHT * CELL_SIZE);

    setcolor(WHITE); // 设置文本颜色为白色
    setbkmode(TRANSPARENT);
    setfont(30, 0, _T("宋体"));
    outtextxy(100, 100, _T("主菜单"));
    outtextxy(100, 200, _T("1. 新游戏"));
    outtextxy(100, 300, _T("2. 载入游戏"));
    outtextxy(100, 400, _T("3. 选择皮肤"));
    outtextxy(100, 500, _T("4. 其他"));
    outtextxy(100, 600, _T("5. 退出游戏"));

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
    setfillcolor(BLACK); // 设置背景颜色为黑色
    bar(0, 0, WIDTH * CELL_SIZE + STATUS_BAR_WIDTH, HEIGHT * CELL_SIZE);

    setcolor(WHITE); // 设置文本颜色为白色
    setbkmode(TRANSPARENT);
    setfont(30, 0, _T("宋体"));
    outtextxy(100, 100, _T("其他"));
    outtextxy(100, 200, _T("1. 音乐"));
    outtextxy(100, 300, _T("2. 新手教程"));

    if (selectedOption == 1) {
        outtextxy(80, 200, _T(">"));
    } else if (selectedOption == 2) {
        outtextxy(80, 300, _T(">"));
    }
}

void draw_music_menu(int selectedOption, const char* musicFiles[], int numFiles) {
    cleardevice();
    setfillcolor(BLACK); // 设置背景颜色为黑色
    bar(0, 0, WIDTH * CELL_SIZE + STATUS_BAR_WIDTH, HEIGHT * CELL_SIZE);

    setcolor(WHITE); // 设置文本颜色为白色
    setbkmode(TRANSPARENT);
    setfont(30, 0, _T("宋体"));
    outtextxy(100, 100, _T("选择音乐"));

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
                case 13:  // 回车键
                    if (selectedOption == 1) {
                        show_music_menu();
                    }else if (selectedOption == 2) {
                        int scrollOffset = 0;
                        const int scrollStep = 20;
                        const int maxScrollOffset = 1600; // 根据实际文本内容高度调整
                        bool display = true;

                        while (display) {
                            cleardevice();

                            setcolor(WHITE); // 设置文本颜色为白色
                            setbkmode(TRANSPARENT);

                            // 滚动提示
                            setfont(20, 0, _T("宋体"));
                            outtextxy(50, 0 - scrollOffset, _T("按“W”键和“S”键滚动阅读"));

                            // 设置标题字体为更大或加粗
                            setfont(30, 0, _T("宋体"));
                            outtextxy(50, 40 - scrollOffset, _T("新手教程：《橙子的冒险》"));

                            // 设置子标题字体为更大或加粗
                            setfont(25, 0, _T("宋体"));
                            outtextxy(50, 80 - scrollOffset, _T("背景故事:"));

                            // 设置正文字体
                            setfont(20, 0, _T("宋体"));
                            outtextxy(50, 110 - scrollOffset, _T("在遥远的斯维驰大陆上，有一个繁荣的王国，"));
                            outtextxy(50, 140 - scrollOffset, _T("王国中有一位善良而美丽的橙子公主。帕乐尔，"));
                            outtextxy(50, 170 - scrollOffset, _T("是公主的忠实侍卫和好朋友，他们一起度过了无数美好的时光。"));
                            outtextxy(50, 200 - scrollOffset, _T("然而，有一天，邪恶的魔王入侵了王国，绑架了橙子公主，"));
                            outtextxy(50, 230 - scrollOffset, _T("将她囚禁在一个秘密的地方。魔王施加了强大的魔法封印，"));
                            outtextxy(50, 260 - scrollOffset, _T("只有勇敢且心怀正义的人才能打破封印，救出公主。"));
                            outtextxy(50, 290 - scrollOffset, _T("帕乐尔毫不犹豫地踏上了冒险之旅，他需要找到传说中的金色橙子，"));
                            outtextxy(50, 320 - scrollOffset, _T("打败魔王，救出他心爱的公主，解救王国的人民。勇敢的帕乐尔，你准备好了吗？"));

                            // 游戏操作
                            setfont(25, 0, _T("宋体"));
                            outtextxy(50, 360 - scrollOffset, _T("游戏操作:"));

                            setfont(20, 0, _T("宋体"));
                            outtextxy(50, 390 - scrollOffset, _T("W键：向上移动"));
                            outtextxy(50, 420 - scrollOffset, _T("A键：向左移动"));
                            outtextxy(50, 450 - scrollOffset, _T("S键：向下移动"));
                            outtextxy(50, 480 - scrollOffset, _T("D键：向右移动"));
                            outtextxy(50, 510 - scrollOffset, _T("E键：取下或装备宝剑"));
                            outtextxy(50, 540 - scrollOffset, _T("U键：使用金色橙子恢复生命"));
                            outtextxy(50, 570 - scrollOffset, _T("P键：保存游戏"));
                            outtextxy(50, 600 - scrollOffset, _T("ESC键：退出游戏"));

                            // 游戏目标
                            setfont(25, 0, _T("宋体"));
                            outtextxy(50, 640 - scrollOffset, _T("游戏目标:"));

                            setfont(20, 0, _T("宋体"));
                            outtextxy(50, 670 - scrollOffset, _T("1. 收集宝剑：帕乐尔需要找到并装备宝剑，以增强攻击力。"));
                            outtextxy(50, 700 - scrollOffset, _T("2. 打败敌人：使用宝剑击败所有阻挡在前进道路上的敌人。"));
                            outtextxy(50, 730 - scrollOffset, _T("3. 收集金色橙子：使用金色橙子可以在紧急时刻恢复生命值。"));
                            outtextxy(50, 760 - scrollOffset, _T("4. 找到钥匙：收集钥匙以打开被锁住的门。"));
                            outtextxy(50, 790 - scrollOffset, _T("5. 探索地图：仔细探索每一层，找到所有重要的物品和线索。"));
                            outtextxy(50, 820 - scrollOffset, _T("6. 救出橙子公主：找到并救出被囚禁在第二层的橙子公主，完成冒险。"));

                            // 物品介绍
                            setfont(25, 0, _T("宋体"));
                            outtextxy(50, 860 - scrollOffset, _T("物品介绍:"));

                            setfont(20, 0, _T("宋体"));
                            outtextxy(50, 890 - scrollOffset, _T("宝剑：增加帕乐尔的攻击力，找到宝剑后按E键装备。"));
                            outtextxy(50, 920 - scrollOffset, _T("橙子：增加帕乐尔的生命值，吃掉后自动恢复一点生命值。"));
                            outtextxy(50, 950 - scrollOffset, _T("金色橙子：完全恢复帕乐尔的生命值，并暂时提高一点生命值上限，按U键使用。"));
                            outtextxy(50, 980 - scrollOffset, _T("钥匙：用来打开被锁住的门。"));
                            outtextxy(50, 1010 - scrollOffset, _T("金币：收集金币，可以在特定地点使用。"));

                            // 敌人介绍
                            setfont(25, 0, _T("宋体"));
                            outtextxy(50, 1050 - scrollOffset, _T("敌人介绍:"));

                            setfont(20, 0, _T("宋体"));
                            outtextxy(50, 1080 - scrollOffset, _T("史莱姆"));
                            outtextxy(80, 1110 - scrollOffset, _T("生命值：5"));
                            outtextxy(80, 1140 - scrollOffset, _T("攻击力：3"));
                            outtextxy(80, 1170 - scrollOffset, _T("描述：普通的敌人，出现在游戏的第一层。它们会阻挡帕乐尔的前进，需要勇士用宝剑击败它们。"));

                            outtextxy(50, 1210 - scrollOffset, _T("魔龙"));
                            outtextxy(80, 1240 - scrollOffset, _T("生命值：5"));
                            outtextxy(80, 1270 - scrollOffset, _T("攻击力：5"));
                            outtextxy(80, 1300 - scrollOffset, _T("描述：强大的敌人，出现在游戏的第二层。它们比普通敌人更强，需要更加小心对付。"));

                            // 角色介绍
                            setfont(25, 0, _T("宋体"));
                            outtextxy(50, 1350 - scrollOffset, _T("角色介绍:"));

                            setfont(20, 0, _T("宋体"));
                            outtextxy(50, 1380 - scrollOffset, _T("帕乐尔 (Player)"));
                            outtextxy(80, 1410 - scrollOffset, _T("生命值：5"));
                            outtextxy(80, 1440 - scrollOffset, _T("攻击力：初始攻击力为2，装备宝剑后攻击力增加到5。"));
                            outtextxy(80, 1470 - scrollOffset, _T("描述：年轻的勇士，热爱冒险。他的目标是解除斯维驰大陆的魔王封印，并救出橙子公主。"));

                            outtextxy(50, 1510 - scrollOffset, _T("丧彪"));
                            outtextxy(80, 1540 - scrollOffset, _T("描述：友好的NPC，会给帕乐尔提供重要的信息和帮助。"));

                            outtextxy(50, 1580 - scrollOffset, _T("橙子公主"));
                            outtextxy(80, 1610 - scrollOffset, _T("描述：被魔王囚禁的橙子公主，帕乐尔需要救出的关键人物。当帕乐尔成功解救她时即可触发结局。"));

                            // 游戏小贴士
                            setfont(25, 0, _T("宋体"));
                            outtextxy(50, 1650 - scrollOffset, _T("游戏小贴士:"));

                            setfont(20, 0, _T("宋体"));
                            outtextxy(50, 1680 - scrollOffset, _T("保存进度：记得定期使用P键保存游戏进度，避免意外导致的进度丢失。"));
                            outtextxy(50, 1710 - scrollOffset, _T("合理使用道具：在合适的时机使用金色橙子，可以帮助你在关键时刻反败为胜。"));
                            outtextxy(50, 1740 - scrollOffset, _T("探索每一个角落：游戏中的每一个角落都有可能藏着宝贵的道具和线索，勇敢探索吧！"));
                            outtextxy(50, 1770 - scrollOffset, _T("注意敌人的位置：每个敌人都有不同的攻击力和生命值，根据情况合理选择战斗策略。"));

                            // 游戏流程
                            setfont(25, 0, _T("宋体"));
                            outtextxy(50, 1810 - scrollOffset, _T("游戏流程:"));

                            setfont(20, 0, _T("宋体"));
                            outtextxy(50, 1840 - scrollOffset, _T("1. 探索第一层：收集宝剑、钥匙和橙子，打败史莱姆。"));
                            outtextxy(50, 1870 - scrollOffset, _T("2. 找到上楼的楼梯：进入第二层继续冒险。"));
                            outtextxy(50, 1900 - scrollOffset, _T("3. 探索第二层：打败更强大的魔龙，寻找橙子公主的位置。"));
                            outtextxy(50, 1930 - scrollOffset, _T("4. 找到橙子公主：在第二层找到橙子公主，成功解救公主后展示最终页面，游戏胜利！"));

                            // 结束画面
                            setfont(25, 0, _T("宋体"));
                            outtextxy(50, 1970 - scrollOffset, _T("结束画面:"));

                            setfont(20, 0, _T("宋体"));
                            outtextxy(50, 2000 - scrollOffset, _T("当帕乐尔找到并解救橙子公主时，游戏会展示一张庆祝成功的图片，表示帕乐尔成功救出公主。"));
                            outtextxy(50, 2030 - scrollOffset, _T("祝你在《橙子的冒险》中玩得愉快，勇士帕乐尔的传奇冒险等你来开启！"));

                            setfont(25, 0, _T("宋体"));
                            outtextxy(50, 2070 - scrollOffset, _T("按 ESC 键退出教程界面"));


                            // 检测键盘输入以实现滚动
                            if (kbhit()) {
                                char key = getch();
                                if (key == 'w' && scrollOffset > 0) {
                                    scrollOffset -= scrollStep;
                                } else if (key == 's' && scrollOffset < maxScrollOffset) {
                                    scrollOffset += scrollStep;
                                } else if (key == 27) { // ESC 键退出教程界面
                                    display = false;
                                }
                            }

                            Sleep(50);
                        }
                    }

                    return;
                case 27:  // ESC 键
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
            // 检查文件是否是常规文件且扩展名是 .wav 或 .mp3
            char filepath[256];
            sprintf(filepath, "%s/%s", MUSIC_FOLDER, ent->d_name);

            if (GetFileAttributes(filepath) & FILE_ATTRIBUTE_DIRECTORY) {
                continue;
            }

            // 只添加 .wav 和 .mp3 文件
            if (strstr(ent->d_name, ".wav") != NULL || strstr(ent->d_name, ".mp3") != NULL) {
                musicFiles[numFiles] = strdup(ent->d_name); // 复制文件名
                numFiles++;
            }
        }
        closedir(dir);
    } else {
        perror("无法打开音乐文件夹");
        return;
    }

    int selectedOption = 1;

    while (1) {
        draw_music_menu(selectedOption, musicFiles, numFiles);

        if (kbhit()) {
            int command = getch();
            if (command >= '1' && command <= '0' + numFiles) {
                selectedOption = command - '0';
            } else if (command == 13) {  // 回车键
                play_music(musicFiles[selectedOption - 1]);
                cleardevice();
                setcolor(WHITE); // 设置文本颜色为白色
                setbkmode(TRANSPARENT);
                setfont(30, 0, _T("宋体"));
                outtextxy((WIDTH * CELL_SIZE + STATUS_BAR_WIDTH) / 2 - 100, HEIGHT * CELL_SIZE / 2, _T("音乐选择成功"));
                outtextxy((WIDTH * CELL_SIZE + STATUS_BAR_WIDTH) / 2 - 150, HEIGHT * CELL_SIZE / 2 + 50, _T("按任意键返回"));
                getch();
                return;
            } else if (command == 27) {  // ESC 键
                return;
            }
        }
        Sleep(100);
    }
}

void play_music(const char *filename) {
    char filepath[256];
    sprintf(filepath, "%s\\%s", MUSIC_FOLDER, filename);

    // 使用 PlaySound 播放音频文件
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
                case 13:  // 回车键
                    *selectedSkin = selectedOption;
                    cleardevice();
                    setcolor(WHITE); // 设置文本颜色为白色
                    setbkmode(TRANSPARENT);
                    setfont(30, 0, _T("宋体"));
                    outtextxy((WIDTH * CELL_SIZE + STATUS_BAR_WIDTH) / 2 - 100, HEIGHT * CELL_SIZE / 2, _T("皮肤选择成功"));
                    outtextxy((WIDTH * CELL_SIZE + STATUS_BAR_WIDTH) / 2 - 150, HEIGHT * CELL_SIZE / 2 + 50, _T("按任意键返回"));
                    getch();
                    return;
                case 27:  // ESC 键
                    return;
            }
        }
        Sleep(100);
    }
}

void draw_skin_menu(int selectedOption, int selectedSkin) {
    cleardevice();
    setfillcolor(BLACK); // 设置背景颜色为黑色
    bar(0, 0, WIDTH * CELL_SIZE + STATUS_BAR_WIDTH, HEIGHT * CELL_SIZE);

    setcolor(WHITE); // 设置文本颜色为白色
    setbkmode(TRANSPARENT);
    setfont(30, 0, _T("宋体"));
    outtextxy(100, 100, _T("选择皮肤"));
    outtextxy(100, 200, _T("1. 皮肤 1"));
    outtextxy(100, 300, _T("2. 皮肤 2"));

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
                case 13:  // 回车键
                    if (selectedOption == 1) {
                        initialize_game(gameState, true);
                        return;
                    } else if (selectedOption == 2) {
                        show_load_menu(gameState, running, restart);
                        if (*restart) return; // 如果需要重启游戏，直接返回
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
                case 27:  // ESC 键
                    *running = false;
                    return;
            }
        }
        Sleep(100);
    }
}

void draw_load_menu(int selectedOption, char saveFiles[][100], int numFiles) {
    cleardevice();
    setfillcolor(BLACK); // 设置背景颜色为黑色
    bar(0, 0, WIDTH * CELL_SIZE + STATUS_BAR_WIDTH, HEIGHT * CELL_SIZE);

    setcolor(WHITE); // 设置文本颜色为白色
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
                        *restart = true;  // 设置为需要重启游戏
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
