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

int arrSum[2] = {1,2};

Udp udp;

void threadFunction() {
    std::cout << "new c++ thread ID: " << std::this_thread::get_id() << std::endl; 
    while(1) {
        auto end = std::chrono::system_clock::now();
        time_t end_time = std::chrono::system_clock::to_time_t(end);
        std::string str = ctime(&end_time);
        //char x[4] = "opa";
        //write(1,x,3);
        int sentSize = udp.send(str);
        std::cout << "Time: " << str << "sentSize = " << sentSize;
        //To sleep a thread for 200 Milliseconds
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        system("clear");
    }   
}
int main(int argc, char** argv) {
    pthread_t thread;
    int result = pthread_create(&thread, nullptr, sum, arrSum);
    pthread_join(thread, (void**)&result);
    while(1) {
        if(!result) break; 
    }
    udp.send("opa");
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
        //system("clear");
    } while(sum--);
    return nullptr;
}
