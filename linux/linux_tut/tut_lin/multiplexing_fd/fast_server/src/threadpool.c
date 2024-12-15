#include "threadpool.h"

Threadpool pool;
Queue* queue;
fptr fArr[16] = {{NULL, 0}};

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* func(void* arg) {
    printf("thread num = %d\n", gettid());

    // get task from queue
    while (1) {
        // threadpool_handler(&pool, &queue);
        // cond var wait
        pthread_mutex_lock(&mutex);
        fptr task;
        if (!queue->empty) {
            queue_pop(queue, &task);
            task.foo(task.arg);
        }
        pthread_mutex_unlock(&mutex);
        // sock threat function
        //
    }

    return 0;
}

void threadpool_create() {
    queue = newQueue(4096);
    // create nproc -1 threads array
    pool.Num = 16;
    pthread_t threadsArr[pool.Num];
    for (int i = 0; i < pool.Num; ++i) {
        // TODO set array of functions
        pthread_create(&threadsArr[i], NULL, func, NULL);
    }
}

static int threadpool_get_free_thread(Threadpool* pool) {
    for (int i = 0; i < pool->Num; ++i) {
        if (pool->threads_arr[i] == THREAD_READY) {
            return i;
        }
    }
    return -1;
}

void threadpool_add_task(fptr f) {
    for (int i = 0; i < pool.Num; ++i) {
        if (pool.threads_arr[i] == THREAD_READY) {
            pool.threads_arr[i] = THREAD_IN_WORK;
        }

        return;
    }
    // add task
    // set bool
    // set sock
    //

    // wakeup thread (cv notify one)
}

void threadpool_handler() {
    // if queue not empty pop queue to thread
    if (!queue->empty) {
        int threadNum = -1;
        if ((threadNum = threadpool_get_free_thread(&pool)) != -1) {
            // add task to thread
            fptr task = {NULL, 0};
            if (!queue_pop(&queue, &task)) {
                threadpool_add_task(task);
            }
            // notify one
        } else {
            // wait for cv wakeup
        }
    }
}
