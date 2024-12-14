#include "threadpool.h"

void threadpool_create(Threadpool* pool) {
    // create nproc -1 threads array
    pool->Num = 16;
    pthread_t threadsArr[pool->Num];
    for(int i = 0; i < pool->Num; ++i) {
        // TODO set array of functions
        //pthread_create(threadsArr[i], NULL, Foo[i], NULL);
    }
}

int threadpool_get_free_thread(Threadpool* pool) {
    for (int i = 0; i < pool->Num; ++i) {
        if (pool->threads_arr[i] == THREAD_READY) {
            return i;
        }
    }
    return -1;
}

void threadpool_add_task(Threadpool* pool, Queue* q, void* (*fptr)(void*)) {
    for (int i = 0; i < pool->Num; ++i) {
        if (pool->threads_arr[i] == THREAD_READY) {
            pool->threads_arr[i] = THREAD_IN_WORK;
        }
    }
    // add task
    // wakeup thread (cv notify one)
}

void threadpool_handler(Threadpool* pool, Queue* q) {
    // if queue not empty pop queue to thread
    if (!q->empty) {
        int threadNum = -1;
        if ((threadNum = threadpool_get_free_thread(pool)) != -1) {
            // add task to thread
            fptr task = NULL;
            if (!queue_pop(q, task)) {
                threadpool_add_task(pool, q, task);
            }
        } else {
            // wait for cv wakeup
        }
    }
}
