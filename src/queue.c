#include "queue.h"

#include <stdio.h>
#include <string.h>

#define MAX_PATH_LENGTH 256

WallyQueue* wally_queue_create(size_t size) {
    WallyQueue* queue = malloc(sizeof(WallyQueue));
    if (!queue) {
        printf("Error: queue malloc returned null\n");
        return NULL;
    }

    queue->size = size;
    queue->head = 0;
    queue->tail = 0;

    queue->data = malloc(size * sizeof(char*));
    if (!queue->data) {
        printf("Error: queue data malloc returned null\n");
        free(queue);
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        queue->data[i] = malloc(MAX_PATH_LENGTH * sizeof(char));
        if (!queue->data[i]) {
            printf("Error: queue data malloc returned null\n");
            wally_queue_free(queue);
            free(queue);
            return NULL;
        }
    }

    return queue;
}

int wally_queue_free(WallyQueue* queue) {
    if (!queue) {
        printf("Error: failed to free queue cause queue is null\n");
        return 0;
    }

    if (!queue->data) {
        printf("Warning: there is nothing to free in the queue\n");
        return 1;
    }

    for (size_t i = 0; i < queue->size; i++) {
        if (queue->data[i]) {
            free(queue->data[i]);
        }
    }

    free(queue->data);
    free(queue);
    return 1;
}

int wally_queue_push(WallyQueue* queue, char* path) {
    if (!queue) {
        printf("Error: failed to push, queue is null\n");
        return 0;
    }

    if (!path) {
        printf("Error: failed to push, path is null\n");
        return 0;
    }

    if (wally_queue_is_full(queue)) {
        printf("Error: failed to push, queue is full\n");
        return 0;
    }

    strncpy(queue->data[queue->tail], path, MAX_PATH_LENGTH - 1);
    queue->data[queue->tail][MAX_PATH_LENGTH - 1] = '\0';
    queue->tail = (queue->tail + 1) % queue->size;

    return 1;
}

char* wally_queue_get(WallyQueue* queue) {
    if (!queue) {
        printf("Error: failed to get, queue is null\n");
        return NULL;
    }

    if (wally_queue_is_empty(queue)) {
        printf("Error: failed to get, queue is empty\n");
        return NULL;
    }

    char* output = malloc(MAX_PATH_LENGTH * sizeof(char));
    if (!output) {
        printf("Error: failed to get, malloc returned null\n");
        return NULL;
    }
    strcpy(output, queue->data[queue->head]);
    queue->head = (queue->head + 1) % queue->size;

    return output;
}

int wally_queue_is_full(WallyQueue* queue) {
    if (!queue) {
        printf("Error: failed to check queue, queue is null\n");
        return 0;
    }

    return ((queue->tail + 1) % queue->size) == queue->head;
}

int wally_queue_is_empty(WallyQueue* queue) {
    if (!queue) {
        printf("Error: failed to check queue, queue is null\n");
        return 0;
    }

    return queue->head == queue->tail;
}
