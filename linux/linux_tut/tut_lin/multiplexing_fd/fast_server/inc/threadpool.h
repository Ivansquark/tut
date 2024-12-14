#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "queue.h"

#include <pthread.h>
#include <stdlib.h>

typedef enum {
    THREAD_READY,
    THREAD_IN_WORK
} THREAD_STATES;

typedef struct {
    int Num;
    THREAD_STATES* threads_arr;
} Threadpool;

#endif // THREADPOOL_H
