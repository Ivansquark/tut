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

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;

void* func([[maybe_unused]] void* arg) {
    // printf("thread num = %ld\n", gettid());
    printf("thread num = %ld\n", syscall(186));
    // printf("thread num = %d\n", pthread_self());

    // get task from queue
    sleep(5);
    // unblock all first time
    pthread_cond_broadcast(&cv);
    while (1) {
        pthread_cond_wait(&cv, &mutex);
        fptr task;
        printf("thread num = %ld Task:\n", gettid());
        if (!queue_pop(queue, &task)) {
            task.foo(task.arg);
        }
    }

    return 0;
}

void threadpool_create() {
    queue = newQueue(4096);
    // create nproc -1 threads array
    pool.Num = get_nproc();
    printf("Num of processors = %d\n", pool.Num);
    pthread_t threadsArr[pool.Num];
    for (int i = 0; i < pool.Num; ++i) {
        // TODO set array of functions
        pthread_create(&threadsArr[i], NULL, func, NULL);
    }
}

int threadpool_add_task(fptr* f) {
    if (!queue_push(queue, f)) {
        // unblock one thread
        pthread_cond_signal(&cv);
        // unblock all threads
        // pthread_cond_broadcast(&cv);
    } else {
        return -1;
    }
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
    return nproc;
}
