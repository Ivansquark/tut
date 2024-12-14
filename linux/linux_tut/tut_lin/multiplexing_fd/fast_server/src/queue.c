#include "queue.h"

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

    q->start = (fptr)mem;
    q->end = (fptr)(mem + capacity * (sizeof(fptr)));
    q->readptr = (fptr)mem;
    q->writeptr = (fptr)mem;
    q->full = 0;
    q->empty = -1;

    return q;
}
void deleteQueue(Queue* q) {
    if (q == NULL) return;
    free((char*)q->start);
    free(q);
}

int queue_push(Queue* q, fptr c) {
    if (q == NULL) return QUEUE_ERR_NULL;

    if ((q->writeptr == q->readptr) && q->full) return QUEUE_ERR_FULL;

    (q->writeptr) = c;

    fptr tmp = (fptr)((char*)q->writeptr + 1 * sizeof(fptr));
    if ((char*)tmp >= (char*)q->end) {
        tmp = q->start;
    }
    if (tmp == q->readptr) {
        q->full = -1;
    }
    q->writeptr = tmp;
    q->empty = 0;

    return QUEUE_OK;
}

int queue_pop(Queue* q, fptr c) {
    if(!c) {
        return QUEUE_ERR_NULL;
    }
    if (q == NULL) return QUEUE_ERR_NULL;

    if ((q->readptr == q->writeptr) && (!q->full)) {
        c = NULL;
        q->empty = -1;
        return QUEUE_ERR_EMPTY;
    }

    c = q->readptr;

    //char* tmp = rb->readptr + 1;
    fptr tmp = (fptr)((char*)q->readptr + 1 * sizeof(fptr));
    if ((char*)tmp >= (char*)q->end) {
        tmp = q->start;
    }
    if (tmp == q->writeptr){
        q->full = 0;
    }
    q->readptr = tmp;

    return QUEUE_OK;
}
