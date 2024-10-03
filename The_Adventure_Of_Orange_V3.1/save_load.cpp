#include "save_load.h"
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>
#include <direct.h> // 使用这个头文件来使用 mkdir

const char *SAVE_DIR = "saves/";

bool check_save_exists(int slot) {  // 修改返回类型为 bool
    char filename[100];
    sprintf(filename, "%s/save%d.dat", SAVE_DIR, slot);
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return true;  // 返回 true 表示存在
    }
    return false;  // 返回 false 表示不存在
}

void save_game(GameState *gameState, int slot) {
    char filename[100];
    sprintf(filename, "%s/save%d.dat", SAVE_DIR, slot);
    FILE *file = fopen(filename, "wb");
    if (file) {
        fwrite(gameState, sizeof(GameState), 1, file);
        fclose(file);
    }
}

void load_game(GameState *gameState, int slot) {
    char filename[100];
    sprintf(filename, "%s/save%d.dat", SAVE_DIR, slot);
    FILE *file = fopen(filename, "rb");
    if (file) {
        fread(gameState, sizeof(GameState), 1, file);
        fclose(file);
    }
}

const char* get_save_time(int slot) {
    static char timeStr[100];
    char filename[100];
    sprintf(filename, "%s/save%d.dat", SAVE_DIR, slot);

    struct stat st;
    if (stat(filename, &st) == 0) {
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localtime(&st.st_mtime));
    } else {
        strcpy(timeStr, "未知");
    }

    return timeStr;
}

int get_oldest_save_slot() {
    int oldestSlot = 1;
    time_t oldestTime = time(NULL);

    for (int i = 1; i <= MAX_SAVES; i++) {
        if (check_save_exists(i)) {
            char filename[100];
            sprintf(filename, "%s/save%d.dat", SAVE_DIR, i);
            struct stat st;
            if (stat(filename, &st) == 0) {
                if (st.st_mtime < oldestTime) {
                    oldestTime = st.st_mtime;
                    oldestSlot = i;
                }
            }
        } else {
            return i; // 如果存在空槽，则使用它
        }
    }

    return oldestSlot;
}

void ensure_save_dir_exists() {
    struct stat st = {0};
    if (stat(SAVE_DIR, &st) == -1) {
        mkdir(SAVE_DIR);  // 使用 mkdir 创建目录
    }
}

void delete_save(int slot) {
    char filename[100];
    sprintf(filename, "%s/save%d.dat", SAVE_DIR, slot);
    remove(filename);
}
