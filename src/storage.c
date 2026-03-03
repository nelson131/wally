#include "storage.h"

#include <stdio.h>
#include <stdlib.h>

#define STORAGE_DIR "/.config/wally"
#define FILE_NAME "/storage"
#define MAX_PATH_LENGTH 256

int wally_storage_init() {
    char* storage_dir_path = wally_get_storage_dir_path();
    if (!storage_dir_path) return 0;

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

    char* file_path = wally_get_storage_file_path(NULL);
    if (!file_path) return 0;

    FILE* file = fopen(file_path, "a");
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
    char* file_path = wally_get_storage_file_path(NULL);
    if (!file_path) return 0;

    FILE* file = fopen(file_path, "a");
    if (!file) {
        printf("Error: failed to open storage file");
        free(file_path);
        return 0;
    }

    fprintf(file, "%s\n", path);
    fclose(file);
    free(file_path);

    return 1;
}

int wally_storage_forget(const char* path) {
    char* original_path = wally_get_storage_file_path(NULL);
    if (!original_path) return 0;

    FILE* original = fopen(original_path, "r");
    if (!original) {
        printf("Error: failed to open original file");
        free(original_path);
        return 0;
    }

    char* temp_path = wally_get_storage_file_path("temp");
    if (!temp_path) {
        free(original_path);
        return 0;
    }

    FILE* temp = fopen(temp_path, "w");
    if (!temp) {
        printf("Error: failed to open temp file");
        free(original_path);
        free(temp_path);
        fclose(original);
        return 0;
    }

    char* buffer = malloc(MAX_PATH_LENGTH * sizeof(char));
    if (!buffer) {
        printf("Error: malloc returned null");
        free(original_path);
        free(temp_path);
        fclose(original);
        fclose(temp);
        return 0;
    }

    char* line = malloc(MAX_PATH_LENGTH * sizeof(char));
    if (!line) {
        printf("Error: malloc returned null");
        free(original_path);
        free(temp_path);
        free(buffer);
        fclose(original);
        fclose(temp);
        return 0;
    }
    snprintf(line, MAX_PATH_LENGTH, "%s\n", path);

    while (fgets(buffer, MAX_PATH_LENGTH, original)) {
        if (strcmp(buffer, line) == 0) {
            continue;
        }

        fputs(buffer, temp);
    }

    fclose(original);
    fclose(temp);

    remove(original_path);
    rename(temp_path, original_path);

    free(original_path);
    free(temp_path);

    return 1;
}

char* wally_get_storage_dir_path() {
    const char* home_dir = getenv("HOME");

    char* dir_path = malloc(MAX_PATH_LENGTH * sizeof(char));
    if (!dir_path) {
        printf("Error: malloc returned null");
        return NULL;
    }

    snprintf(dir_path, MAX_PATH_LENGTH, "%s%s", home_dir, STORAGE_DIR);

    return dir_path;
}

char* wally_get_storage_file_path(const char* key) {
    const char* home_dir = getenv("HOME");
    if (!home_dir) {
        printf("Error: failed to get home dir");
        return NULL;
    }

    char* file_path = malloc(MAX_PATH_LENGTH * sizeof(char));
    if (!file_path) {
        printf("Error: malloc returned null");
        return NULL;
    }

    if (key) {
        snprintf(file_path, MAX_PATH_LENGTH, "%s%s%s%s", home_dir, STORAGE_DIR,
                 "/", key);
    } else {
        snprintf(file_path, MAX_PATH_LENGTH, "%s%s%s", home_dir, STORAGE_DIR,
                 FILE_NAME);
    }

    return file_path;
}
