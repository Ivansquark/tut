#ifndef QUEUE_TEST_H
#define QUEUE_TEST_H

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <thread>

extern "C" {
#include "queue.h"
}
extern "C" int foo(int arg) {
    printf("Arg = %d\n", arg);
    return 0;
}

void push(void* arg1, void* arg2) {
    int counter = 0;
    Queue* q = (Queue*)arg1;
    fptr* fp = (fptr*)arg2;
    while(1) {
        fp->arg = counter++;
        queue_push(q, fp);
        if(counter > 1000) break;
    }
    return;
}

void pop(void* arg1, void* arg2, void* arg3, void* arg4) {
    int counter = 0;
    Queue* q = (Queue*)arg1;
    fptr* fp = (fptr*)arg2;
    Queue* q1 = (Queue*)arg3;
    fptr* fp1 = (fptr*)arg4;
    while(1) {
        if(queue_pop(q, fp) != QUEUE_ERR_EMPTY) {
            fp1->arg = fp->arg;
            queue_push(q1, fp1);
            if(fp1->arg > 900) break;
        }
    }
    return;
}

TEST(TestGroupName, QUEUE_TEST) {
    // Arrange
    bool TestPassed = false;
    int counter_push = 0;
    int counter_push_next = 0;
    int counter_pop = 0;
    

    Queue* q = newQueue(4096);
    fptr f1_push = {foo, 0};
    fptr f1_pop = {foo, 0};
    std::thread t1(push, q, &f1_push);
    
    
    Queue* qres = newQueue(4096);
    fptr fres_push = {foo, 0};
    fptr fres_pop = {foo, 0};
    std::thread t2(pop, q, &f1_pop, qres, &fres_push);
    queue_push(q, &f1_push);

    //f1_pop.foo(f1_pop.arg);
    //fres_push.arg = f1_pop.arg;
    queue_push(qres, &fres_push);

    // one thread producer
    // several threads consumers
    // Act
    printf("Test started\n");
    // Assert
    int prev = fres_pop.arg;
    int curr = fres_pop.arg;
    t1.join();
    while(queue_pop(qres, &fres_pop) != QUEUE_ERR_EMPTY) {
        curr = fres_pop.arg;
        prev = curr;
    }
    
    ASSERT_EQ(TestPassed, true);
}

#endif // QUEUE_TEST_H
