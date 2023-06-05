#include <unistd.h>
#include <stdio.h>
#include "wait.h"
#include "pthread.h"
#include "main.h"
#include "time.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "udp.h"

int arrSum[2] = {5,6};

void threadFunction() {
    std::cout << "new c++ thread ID: " << std::this_thread::get_id() << std::endl;    
}
int main(int argc, char** argv) {
    int tempVar = 0;
    pid_t status = fork();
    if(!status) {
        tempVar++;
        printf("Child tempVar=%d\n", tempVar);
        sleep(1);
        return 0;
    } else {
        printf("Parent tempVar=%d\n", tempVar);
        tempVar--;
    }

    pid_t childID = wait(&status);
    pid_t parentID = getpid();
    printf("\nParent ID=%d\n", parentID);
    printf("child ID was %d\n", childID);
    printf("Parent tempVar=%d\n", tempVar);
    pthread_t thread;
    int result = pthread_create(&thread, nullptr, sum, arrSum);
    pthread_join(thread, (void**)&result);
    while(1) {
        if(!result) break; 
    }
    auto end = std::chrono::system_clock::now();
    time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "Time: " <<ctime(&end_time);
    

    Udp udp;
    udp.send("opa");
    //udp.read();
    std::thread thr(threadFunction);
    thr.join();

    return 0;
}

void* sum(void* arg) {
    int* tempArr = (int*)arg;
    int sum = tempArr[0] + tempArr[1];
    time_t tim;
    do {
        printf("sum =%d\n", sum);
        time(&tim);
        printf(" time=%d\n", (int)tim);
        usleep(500000);
        system("clear");
    } while(sum--);
    return nullptr;
}
