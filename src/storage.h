#ifndef STORAGE_H
#define STORAGE_H

#include "errno.h"
#include "string.h"
#include "sys/stat.h"

int wally_storage_init();
int wally_storage_save(const char* path);
int wally_storage_forget(const char* path);
int wally_storage_get();

char* wally_get_storage_dir_path();
char* wally_get_storage_file_path(const char* key);

#endif
