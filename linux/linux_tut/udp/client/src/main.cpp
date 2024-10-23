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
        //auto end = std::chrono::system_clock::now();
        //time_t end_time = std::chrono::system_clock::to_time_t(end);
        std::string str;
        int len = udp.read();
        if(len == -1) {
            std::cout << "Error!!!" << std::endl;
        } else if(len > 0) {
            //! receive packet
            system("clear");
            std::cout<<"data:\n";
            std::cout << str.append(udp.buff,len) << std::endl; 
        }
        //To sleep a thread for 200 Milliseconds
        //std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }   
}
int main(int argc, char** argv) {
    pthread_t thread;
    int result = pthread_create(&thread, nullptr, sum, arrSum);
    pthread_join(thread, (void**)&result);
    while(1) {
        if(!result) break; 
    }
    std::cout<< "udpfd = " << udp.sockfd << std::endl;
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
        system("clear");
    } while(sum--);
    return nullptr;
}
