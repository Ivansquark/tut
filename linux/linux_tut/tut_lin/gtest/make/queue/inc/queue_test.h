#ifndef QUEUE_TEST_H
#define QUEUE_TEST_H

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <thread>

#define MAX 100

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

extern "C" {
#include "queue.h"
}
extern "C" int foo(int arg) {
    printf("Arg = %d\n", arg);
    return 0;
}

void push(void* arg1, void* arg2) {
    // int counter = 0;
    std::atomic<int> counter = 0;
    Queue* q = (Queue*)arg1;
    fptr* fp = (fptr*)arg2;
    while (1) {
        fp->arg = counter;
        counter++;
        pthread_mutex_lock(&mutex);
        queue_push(q, fp);
        pthread_mutex_unlock(&mutex);
        if (counter > MAX) break;
        // printf("thread - 1\n");
        //   usleep(1);
    }
    return;
}

void pop(void* arg1, void* arg2, void* arg3, void* arg4) {
    Queue* q = (Queue*)arg1;
    fptr* fp = (fptr*)arg2;
    Queue* q1 = (Queue*)arg3;
    fptr* fp1 = (fptr*)arg4;
    int counter = 0;
    // pthread_mutex_lock(&mutex);
    int ret = 0;
    while (1) {
        if ((ret = queue_pop(q, fp)) != QUEUE_ERR_EMPTY) {
            pthread_mutex_lock(&mutex);
            fp1->arg = fp->arg;
            queue_push(q1, fp1);
            counter = 0;
            printf("thread - 2 %d, ret = %d fp->arg = %d\n", gettid(), ret,
                   fp->arg);
            pthread_mutex_unlock(&mutex);
            if (fp1->arg > MAX - 1) break;
        } else {
            printf("------------WAIT--------------\n");
            counter++;
            if (counter > MAX) {
                return;
            }
            // usleep(100);
        }
        // usleep(1);
    }
    return;
}

TEST(TestGroupName, QUEUE_TEST) {
    // Arrange
    bool TestPassed = true;
    int counter_push = 0;
    int counter_push_next = 0;
    int counter_pop = 0;

    Queue* q = newQueue(MAX + 1);
    fptr f1_push = {foo, 0};
    fptr f1_pop = {foo, 0};

    Queue* qres = newQueue(MAX + 1);
    fptr fres_push = {foo, 0};
    fptr fres_pop = {foo, 0};

    // Act
    printf("Threads started\n");
    std::thread t1(push, q, &f1_push);
    // sleep(2);
    std::thread t2(pop, q, &f1_pop, qres, &fres_push);
    std::thread t3(pop, q, &f1_pop, qres, &fres_push);

    // one thread producer
    // several threads consumers
    t1.join();
    t2.join();
    t3.join();
    // t3.detach();
    //   Assert
    int prev = fres_pop.arg;
    int curr = fres_pop.arg;
    printf("Threads finished\n");
    // std::atomic<int> counter = 0;
    int counter = 0;
    // pthread_mutex_lock(&mutex);
    while (queue_pop(qres, &fres_pop) != QUEUE_ERR_EMPTY) {
        curr = fres_pop.arg;
        printf("curr = %d\n", curr);
        // if (curr > prev + 1) TestPassed = false;
        ASSERT_EQ(curr, counter);
        if (curr != counter) {
            // TestPassed = false;
        }
        prev = curr;
        counter++;
    }
    // pthread_mutex_unlock(&mutex);
    // if (curr != MAX) TestPassed = false;
    // printf("curr = %d\n", curr);

    ASSERT_EQ(TestPassed, true);
    // t3.join();
}
//$bash -c while build/gtest.elf; do; done;

#endif // QUEUE_TEST_H