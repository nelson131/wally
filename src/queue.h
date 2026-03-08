#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

typedef struct WallyQueue {
    char** data;
    size_t size;
    size_t head;
    size_t tail;
} WallyQueue;

WallyQueue* wally_queue_create(size_t size);
int         wally_queue_free(WallyQueue* queue);

int   wally_queue_push(WallyQueue* queue, char* path);
char* wally_queue_get(WallyQueue* queue);

int wally_queue_is_full(WallyQueue* queue);
int wally_queue_is_empty(WallyQueue* queue);

#endif
