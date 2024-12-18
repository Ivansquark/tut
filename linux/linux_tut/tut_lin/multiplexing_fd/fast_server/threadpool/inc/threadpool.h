#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "queue.h"

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int Num;
} Threadpool;

void threadpool_create();
int threadpool_add_task(fptr* f);
int get_nproc();
#endif // THREADPOOL_H
