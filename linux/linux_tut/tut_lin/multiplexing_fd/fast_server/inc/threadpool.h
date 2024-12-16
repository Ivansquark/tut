#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "queue.h"

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum {
    THREAD_READY,
    THREAD_IN_WORK
} THREAD_STATES;

typedef struct {
    int Num;
    THREAD_STATES* threads_arr;
} Threadpool;

void threadpool_create();
int threadpool_add_task(fptr* f);
int get_nproc();
#endif // THREADPOOL_H
