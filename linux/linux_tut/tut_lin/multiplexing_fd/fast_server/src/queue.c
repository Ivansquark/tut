#include "queue.h"

#include <pthread.h>

pthread_mutex_t mut_q = PTHREAD_MUTEX_INITIALIZER;
Queue* newQueue(unsigned long int capacity) {
    char* mem = malloc(capacity * CHAR_SIZE * sizeof(fptr));
    if (mem == NULL) {
        return NULL;
    }

    Queue* q = malloc(sizeof(Queue));
    if (q == NULL) {
        free(mem);
        return NULL;
    }

    q->start = (fptr*)mem;
    q->end = (fptr*)(mem + capacity * (sizeof(fptr)));
    q->readptr = (fptr*)mem;
    q->writeptr = (fptr*)mem;
    q->full = 0;

    return q;
}
void deleteQueue(Queue* q) {
    if (q == NULL) return;
    free((char*)q->start);
    free(q);
}

int queue_push(Queue* q, fptr* c) {
    pthread_mutex_lock(&mut_q);
    if (q == NULL) goto ret_queue_err_null;

    if ((q->writeptr == q->readptr) && q->full) goto ret_queue_err_full;

    *(q->writeptr) = *c;

    fptr* tmp = (fptr*)((char*)q->writeptr + 1 * sizeof(fptr));
    if ((char*)tmp >= (char*)q->end) {
        tmp = q->start;
    }
    if (tmp == q->readptr) {
        q->full = -1;
    }
    q->writeptr = tmp;
    pthread_mutex_unlock(&mut_q);

    return QUEUE_OK;

ret_queue_err_null:
    pthread_mutex_unlock(&mut_q);
    return QUEUE_ERR_NULL;

ret_queue_err_full:
    pthread_mutex_unlock(&mut_q);
    return QUEUE_ERR_FULL;
}

int queue_pop(Queue* q, fptr* c) {
    pthread_mutex_lock(&mut_q);
    if (!c) goto ret_queue_err_null;
    if (q == NULL) goto ret_queue_err_null;

    if ((q->readptr == q->writeptr) && (!q->full)) {
        c = NULL;
        goto ret_queue_err_empty;
    }

    *c = *(q->readptr);

    // char* tmp = rb->readptr + 1;
    fptr* tmp = (fptr*)(q->readptr + 1);
    if ((char*)tmp >= (char*)q->end) {
        tmp = q->start;
    }
    if (tmp == q->writeptr) {
        q->full = 0;
    }
    q->readptr = tmp;
    pthread_mutex_unlock(&mut_q);

    return QUEUE_OK;

ret_queue_err_null:
    pthread_mutex_unlock(&mut_q);
    return QUEUE_ERR_NULL;

ret_queue_err_empty:
    pthread_mutex_unlock(&mut_q);
    return QUEUE_ERR_EMPTY;
}
