#include "cv.h"

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

char data[2000] = {0};

pthread_cond_t cv = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutx = PTHREAD_MUTEX_INITIALIZER;

int buffer_not_empty(char* b) { return strlen(b); }

void* consumer([[maybe_unused]] void* arg) {
    while (1) {
        pthread_mutex_lock(&mutx);
        while (!buffer_not_empty(data)) {
            pthread_cond_wait(&cv, &mutx); // unlock mutx (and lock if wake_up)
            // wake_up => check buffer not empty
        }
        pthread_mutex_unlock(&mutx);
        printf("%s\n", data);
        memset(data, 0, sizeof(data));
    }
    return 0;
}
void* producer([[maybe_unused]] void* arg) {
    int count = 0;
    // char count_buf[10] = {0};
    char buf[4096] = {0};
    while (1) {
        pthread_mutex_lock(&mutx);
        // sprintf(count_buf, "%d", count);
        sprintf(buf, "%s, %d\n", "Consumer num = ", count);
        strcpy(data, buf);
        count++;
        pthread_mutex_unlock(&mutx);
        pthread_cond_signal(&cv);
        sleep(1);
    }
    return 0;
}

int main() {
    pthread_t consume;
    pthread_t produce;
    pthread_create(&consume, NULL, consumer, NULL);
    pthread_create(&produce, NULL, producer, NULL);
    pthread_join(consume, NULL);
    pthread_join(produce, NULL);
}
