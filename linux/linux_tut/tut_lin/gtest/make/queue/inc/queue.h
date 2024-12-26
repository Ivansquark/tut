#ifndef QUEUE_H
#define QUEUE_H

//@ queue with tasks (not thread safe)

#include <stdlib.h>

#define SAFE

#define CHAR_SIZE (sizeof(char))

#define QUEUE_OK (0)
#define QUEUE_ERR_NULL (-1)
#define QUEUE_ERR_EMPTY (-2)
#define QUEUE_ERR_FULL (-3)

typedef int (*f_ptr)(int);

typedef struct {
    f_ptr foo;
    int arg;
} fptr;

typedef struct {
	fptr* start;
	fptr* end;
	volatile fptr* readptr;
	volatile fptr* writeptr;
	volatile int full;
} Queue;

Queue* newQueue(unsigned long int capacity);
void deleteQueue(Queue* q);
int queue_push(Queue* q, fptr* c);
int queue_pop(Queue* q, fptr* c);

#endif //QURE_H
