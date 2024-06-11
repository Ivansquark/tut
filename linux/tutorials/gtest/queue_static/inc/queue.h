#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>
#include <string.h>

namespace Queue {

template <int SIZE = 4, int SIZE_ARR = 256>
class Queue {
  public:
    struct Data {
        const uint8_t* data;
        uint8_t len;
    };
    static uint8_t size();
    static Data pop();
    static bool push(const uint8_t* arr, uint8_t len);

  private:
    static uint8_t* last;
    static uint8_t* first;
    static uint8_t bufLenInd[SIZE];
    static uint8_t buf[SIZE][SIZE_ARR];
    static bool mutex;
};

template <int SIZE, int SIZE_ARR>
uint8_t* Queue<SIZE, SIZE_ARR>::last = nullptr;
template <int SIZE, int SIZE_ARR>
uint8_t* Queue<SIZE, SIZE_ARR>::first = nullptr;
template <int SIZE, int SIZE_ARR>
uint8_t Queue<SIZE, SIZE_ARR>::bufLenInd[SIZE] = {0};
template <int SIZE, int SIZE_ARR>
uint8_t Queue<SIZE, SIZE_ARR>::buf[SIZE][SIZE_ARR] = {0};
template <int SIZE, int SIZE_ARR>
bool Queue<SIZE, SIZE_ARR>::mutex = false;

template <int SIZE, int SIZE_ARR>
uint8_t Queue<SIZE, SIZE_ARR>::size() {
    if (first == nullptr) {
        return 0;
    } else if (first == last) {
        return 1;
    } else if (first < last) {
        return (last - first) + 1;
    } else {
        return (SIZE + 1 - (first - last));
    }
}

template <int SIZE, int SIZE_ARR>
typename Queue<SIZE, SIZE_ARR>::Data Queue<SIZE, SIZE_ARR>::pop() {
    if (mutex) {
        Data data{nullptr, 0};
        return data;
    };
    mutex = true;
    if (first == nullptr) {
        mutex = false;
        Data data{nullptr, 0};
        return data;
    } else if (first == last) {
        // one value in queue
        uint8_t temp = first - bufLenInd;
        first = nullptr;
        last = nullptr;
        mutex = false;
        Data data{&buf[temp][0], bufLenInd[temp]};
        return data;
    } else if (first < last) {
        uint8_t temp = first - bufLenInd;
        // uint8_t temp = *first;
        first++;
        mutex = false;
        Data data{&buf[temp][0], bufLenInd[temp]};
        return data;
    } else {
        uint8_t temp = first - bufLenInd;
        // int temp = *first;
        Data data{&buf[temp][0], bufLenInd[temp]};
        if (first < &bufLenInd[SIZE] - 1) {
            first++;
        } else {
            first = &bufLenInd[0];
        }
        mutex = false;
        return data;
    }
    Data data{nullptr, 0};
    return data;
    mutex = false;
}

template <int SIZE, int SIZE_ARR>
bool Queue<SIZE, SIZE_ARR>::push(const uint8_t* arr, uint8_t len) {
    if (mutex) return false;
    mutex = true;
    if (first == nullptr) {
        bufLenInd[0] = len;
        memcpy(buf, arr, len);
        first = bufLenInd;
        last = bufLenInd;
    } else if (first == last) {
        // one element
        if (last == &bufLenInd[SIZE - 1]) {
            last = bufLenInd;
            bufLenInd[0] = len;
            memcpy(buf, arr, len);
        } else {
            last++;
            bufLenInd[last - bufLenInd] = len;
            memcpy(&buf[last - bufLenInd][0], arr, len);
        }
    } else if (first < last) {
        if (last < &(bufLenInd[SIZE]) - 1) {
            last++;
            bufLenInd[last - bufLenInd] = len;
            memcpy(&buf[last - bufLenInd][0], arr, len);
        } else {
            if (first != &bufLenInd[0]) {
                last = bufLenInd;
                bufLenInd[0] = len;
                memcpy(buf, arr, len);
            } else {
                mutex = false;
                return false;
            }
        }
    } else {
        if (last < first - 1) {
            last++;
            bufLenInd[last - bufLenInd] = len;
            memcpy(&buf[last - bufLenInd][0], arr, len);
        } else {
            mutex = false;
            return false;
        }
    }
    mutex = false;
    return true;
}

using MrtReceive = Queue<4, 256>;
using MrtSend = Queue<2, 128>;
using XrayReceive = Queue<3, 64>;
using XraySend = Queue<2, 64>;

} // namespace Queue
#endif // QUEUE_H
