#include "queue.h"

#include <pthread.h>

pthread_mutex_t mut_q = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t notEmpty = PTHREAD_COND_INITIALIZER;
int NoEmpty = 0;

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

#include <stdio.h>

int queue_push(Queue* q, fptr* c) {
#ifdef SAFE
    pthread_mutex_lock(&mut_q);
#endif
    if (q == NULL) {
#ifdef SAFE
        pthread_mutex_unlock(&mut_q);
        printf("ERR_NULL\n");
#endif
        return QUEUE_ERR_NULL;
    }

    if ((q->writeptr == q->readptr) && q->full) {
#ifdef SAFE
        pthread_mutex_unlock(&mut_q);
        printf("ERR_FULL\n");
#endif
        return QUEUE_ERR_FULL;
    }

    *(q->writeptr) = *c;

    fptr* tmp = (fptr*)(q->writeptr + 1);
    if ((char*)tmp >= (char*)q->end) {
        tmp = q->start;
    }
    if (tmp == q->readptr) {
        q->full = -1;
    }
    q->writeptr = tmp;

#ifdef SAFE
    pthread_mutex_unlock(&mut_q);
#endif
    return QUEUE_OK;
}

int queue_pop(Queue* q, fptr* c) {
#ifdef SAFE
    pthread_mutex_lock(&mut_q);
#endif
    if (!c) {
#ifdef SAFE
        pthread_mutex_unlock(&mut_q);
#endif
        return QUEUE_ERR_NULL;
    }
    if (q == NULL) {
#ifdef SAFE
        pthread_mutex_unlock(&mut_q);
#endif
        return QUEUE_ERR_EMPTY;
    }

    if ((q->readptr == q->writeptr) && (!q->full)) {
        c = NULL;
#ifdef SAFE
        pthread_mutex_unlock(&mut_q);
#endif
        return QUEUE_ERR_EMPTY;
    }

    *c = *q->readptr;

    // char* tmp = rb->readptr + 1;
    fptr* tmp = (fptr*)(q->readptr + 1);
    if ((char*)tmp >= (char*)q->end) {
        tmp = q->start;
    }
    if (tmp == q->writeptr) {
        q->full = 0;
    }
    q->readptr = tmp;

#ifdef SAFE
    pthread_mutex_unlock(&mut_q);
#endif
    return QUEUE_OK;
}
