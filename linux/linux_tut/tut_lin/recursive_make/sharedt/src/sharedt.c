#include "sharedt.h"

#include <ctype.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void* pf1(void* arg);
void* pf2(void* arg);

void print(char* str) {
    pthread_t p1;
    pthread_t p2;
    pthread_attr_t attr1;
    pthread_create(&p1, NULL, pf1, str);
    pthread_create(&p2, NULL, pf2, NULL);
    pthread_detach(p2);
    pthread_join(p1, NULL);
}

void* pf1(void* arg) {
    char* str = (char*)arg;
    int count = 0;
    while (1) {
        printf("thread 1\r\n");
        printf("%s\r\n", str);
        usleep(1000000);
        count++;
        if(count >= 5) break;
    }
    return 0;
}

void* pf2(void* arg) {
    int count = 0;
    while (1) {
        printf("thread 2\r\n");
        usleep(200000);
        count++;
        //if(count >= 7) break;
    }
    return 0;
}
