#include "save_load.h"
#include <cstdio>
#include <direct.h>
#include <cstring>
#include <ctime>
#include <sys/stat.h>

void ensure_save_dir_exists() {
    struct stat st = {0};
    if (stat(SAVE_FOLDER, &st) == -1) {
        mkdir(SAVE_FOLDER);
    }
}

bool check_save_exists(int slot) {
    char filepath[256];
    sprintf(filepath, "%s/save%d.dat", SAVE_FOLDER, slot);
    FILE *file = fopen(filepath, "rb");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}

void save_game(GameState *gameState, int slot) {
    char filepath[256];
    sprintf(filepath, "%s/save%d.dat", SAVE_FOLDER, slot);
    FILE *file = fopen(filepath, "wb");
    if (file) {
        fwrite(gameState, sizeof(GameState), 1, file);
        fclose(file);
    }
}

void load_game(GameState *gameState, int slot) {
    char filepath[256];
    sprintf(filepath, "%s/save%d.dat", SAVE_FOLDER, slot);
    FILE *file = fopen(filepath, "rb");
    if (file) {
        fread(gameState, sizeof(GameState), 1, file);
        fclose(file);
    }
}

const char* get_save_time(int slot) {
    static char timeStr[64];
    char filepath[256];
    sprintf(filepath, "%s/save%d.dat", SAVE_FOLDER, slot);
    struct stat attr;
    if (stat(filepath, &attr) == 0) {
        struct tm *tm = localtime(&attr.st_mtime);
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", tm);
        return timeStr;
    }
    return "无";
}

int get_oldest_save_slot() {
    time_t oldestTime = time(NULL);
    int oldestSlot = 1;
    for (int i = 1; i <= MAX_SAVES; i++) {
        char filepath[256];
        sprintf(filepath, "%s/save%d.dat", SAVE_FOLDER, i);
        struct stat attr;
        if (stat(filepath, &attr) == 0) {
            if (attr.st_mtime < oldestTime) {
                oldestTime = attr.st_mtime;
                oldestSlot = i;
            }
        } else {
            return i; // 如果某个存档不存在，则直接返回该存档槽
        }
    }
    return oldestSlot;
}

void delete_save(int slot) {
    char filepath[256];
    sprintf(filepath, "%s/save%d.dat", SAVE_FOLDER, slot);
    remove(filepath);
}
