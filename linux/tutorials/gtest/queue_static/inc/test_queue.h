#ifndef TEST_QUEUE_H
#define TEST_QUEUE_H

#include "print.h"
#include "queue.h"
#include <cassert>
#include <gtest/gtest.h>

TEST(TestGroupName, test_queue) {
    print("Test", "queue");
    uint8_t arr1[] = "1";
    uint8_t arr2[] = "_2";
    uint8_t arr3[] = "__3";
    uint8_t arr4[] = "___4";
    uint8_t arr5[] = "____5";
    Queue::MrtReceive q;
    Queue::MrtReceive::Data d;
    q.push(arr1,sizeof(arr1));
    print("size", (int)q.size());
    q.push(arr2,sizeof(arr2));
    print("size", (int)q.size());
    d = q.pop();
    print(d.data);
    print("size", (int)q.size());
    q.push(arr3,sizeof(arr3));
    print("size", (int)q.size());
    d = q.pop();
    print(d.data);
    print("size", (int)q.size());
    q.push(arr1,sizeof(arr1));
    print("size", (int)q.size());
    q.push(arr2,sizeof(arr2));
    print("size", (int)q.size());
    q.push(arr3,sizeof(arr3));
    print("size", (int)q.size());
    d = q.pop();
    print(d.data);
    print("size", (int)q.size());
    q.push(arr4,sizeof(arr4));
    print("size", (int)q.size());
    d = q.pop();
    print(d.data);
    print("size", (int)q.size());
    d = q.pop();
    print(d.data);
    print("size", (int)q.size());
    d = q.pop();
    print(d.data);
    print("size", (int)q.size());
    q.push(arr1,sizeof(arr1));
    print("size", (int)q.size());
    d = q.pop();
    print(d.data);
    print("size", (int)q.size());
    q.push(arr2,sizeof(arr2));
    print("size", (int)q.size());
    q.push(arr3,sizeof(arr3));
    print("size", (int)q.size());
    q.push(arr4,sizeof(arr4));
    print("size", (int)q.size());
    q.push(arr4,sizeof(arr4));
    q.push(arr4,sizeof(arr4));
    print("size", (int)q.size());
    print("size", (int)q.size());
    d = q.pop();
    print(d.data);
    print("size", (int)q.size());
    d = q.pop();
    print(d.data);
    print("size", (int)q.size());
    q.push(arr5,sizeof(arr5));
    print("size", (int)q.size());
    d = q.pop();
    print(d.data);
    print("size", (int)q.size());
    d = q.pop();
    print(d.data);
    print("size", (int)q.size());
    print((int)d.len);
    d = q.pop();
    print(d.data);
    print("size", (int)q.size());
    print((int)d.len);
    // Arrange
    // std::static_assert((2 + 2 == 5), ("opa"));
    // const int i = 0;
    // assert(i == 1.5);
    //EXPECT_EQ(res, 5);
}

#endif // TEST_QUEUE_H
