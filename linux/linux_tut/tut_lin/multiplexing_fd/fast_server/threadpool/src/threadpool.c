#include "threadpool.h"

#ifndef __USE_MISC
    #define __USE_MISC
#endif
#ifndef _GNU_SOURCE
    #define _GNU_SOURCE
    #define gettid() syscall(SYS_gettid)
#endif
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

Threadpool pool;
Queue* queue;
fptr fArr[16] = {{NULL, 0}};
int StartQueue = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;

void* func([[maybe_unused]] void* arg) {
    // printf("thread num = %ld\n", gettid());
    printf("thread num = %ld\n", syscall(186));
    // printf("thread num = %d\n", pthread_self());

    // unblock all first time
    // pthread_cond_broadcast(&cv);
    fptr task;
    while (1) {
        pthread_mutex_lock(&mutex);
        while (!StartQueue) {
            pthread_cond_wait(&cv, &mutex);
        }
        //StartQueue = 0;
        StartQueue--;
        if (!queue_pop(queue, &task)) {
            pthread_mutex_unlock(&mutex);
            //printf("thread num = %ld Task: %d\n", gettid(), task.arg);
            task.foo(task.arg);
            close(task.arg);
        } else {
            StartQueue = 0;
            printf("Queue NULL\n");
            pthread_mutex_unlock(&mutex);
        }
    }

    return 0;
}

void threadpool_create() {
    queue = newQueue(2048);
    pool.Num = get_nproc() - 1;
    ////////////////////////////
    //pool.Num = 2;
    ////////////////////////////
    if (pool.Num < 2) pool.Num = 1;
    printf("Num of processors = %d\n", pool.Num);
    pthread_t threadsArr[pool.Num];
    for (int i = 0; i < pool.Num; ++i) {
        // TODO set array of functions
        pthread_create(&threadsArr[i], NULL, func, NULL);
    }
}

int threadpool_add_task(fptr* f) {
    pthread_mutex_lock(&mutex);
    //StartQueue = 1;
    StartQueue++;
    if (!queue_push(queue, f)) {
        // unblock one thread
        StartQueue = 1;
        pthread_cond_signal(&cv);
        // unblock all threads
        //pthread_cond_broadcast(&cv);
    } else {
        //printf("Queue FULL\n");
        close(f->arg);
        StartQueue = 1;
        pthread_cond_broadcast(&cv);
        pthread_mutex_unlock(&mutex);
        return -1;
    }
    pthread_mutex_unlock(&mutex);
    return 0;
}

int get_nproc() {
    mkfifo("nproc.fif", 0644);
    int fd = open("nproc.fif", O_RDWR, 0600);
    system("nproc > nproc.fif");
    char buf[10] = {0};
    read(fd, buf, sizeof(buf));
    close(fd);
    int nproc = atoi(buf);
    unlink("nproc.fif");
    // TODO remake through fork exec
    return nproc;
}
