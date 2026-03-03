#include "storage.h"

#include <stdio.h>
#include <stdlib.h>

#define STORAGE_DIR "./.config/wally"
#define FILE_NAME "/storage"
#define MAX_PATH_LENGTH 256

int wally_storage_init() {
    const char* home_dir = getenv("HOME");
    if (!home_dir) {
        printf("Error: home dir not found");
        return 0;
    }

    char* storage_dir_path = malloc(MAX_PATH_LENGTH * sizeof(char));
    if (!storage_dir_path) {
        printf("Error: malloc returned null");
        return 0;
    }
    snprintf(storage_dir_path, sizeof(storage_dir_path), "%s%s", home_dir,
             STORAGE_DIR);

    struct stat st = {0};
    if (stat(storage_dir_path, &st) == -1) {
        if (mkdir(storage_dir_path, 0700) == -1) {
            printf("Error: failed to create dir");
            free(storage_dir_path);
            return 0;
        }
        printf("Created a storage dir");
    }

    free(storage_dir_path);

    char* file_path = malloc(MAX_PATH_LENGTH * sizeof(char));
    if (!file_path) {
        printf("Error: malloc returned null");
        return 0;
    }
    snprintf(file_path, sizeof(file_path), "%s%s%s", home_dir, STORAGE_DIR,
             FILE_NAME);

    FILE* file = fopen(file_path, "w");
    if (!file) {
        printf("Error: opening a storage file");
        free(file_path);
        return 0;
    }

    fprintf(file, "# Wally storage file\n");
    fclose(file);
    free(file_path);

    return 1;
}

int wally_storage_save(const char* path) {
    const char* home_dir = getenv("HOME");

    char* file_path = malloc(MAX_PATH_LENGTH * sizeof(char));
    if (!file_path) {
        printf("Error: malloc returned null");
        return 0;
    }
    snprintf(file_path, sizeof(file_path), "%s%s%s", home_dir, STORAGE_DIR,
             FILE_NAME);

    FILE* file = fopen(file_path, "w");
    if (!file) {
        printf("Error: failed to open storage file");
        free(file_path);
        return 0;
    }

    fprintf(file, "%s", path);
    fclose(file);
    free(file_path);

    return 1;
}

int wally_storage_forget(const char* path) {}
