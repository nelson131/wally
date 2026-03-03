#ifndef STORAGE_H
#define STORAGE_H

#include "errno.h"
#include "string.h"
#include "sys/stat.h"

int wally_storage_init();
int wally_storage_save(const char* path);
int wally_storage_forget(const char* path);

int wally_storage_get();

#endif
