#include <unistd.h>
#include <stdio.h>
#include "wait.h"
#include "pthread.h"
#include "main.h"
#include "time.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "tcp.h"

Tcp* tcpPtr = nullptr;

void threadFunction();
void threadFunctionRead();
int main(int argc, char** argv) {
    std::thread thread1(threadFunction);
    std::thread thread2(threadFunctionRead);
    thread1.join();
    thread2.join();
    return 0;
}
void threadFunctionRead() {
    sleep(1);
    std::cout<<"threadRead started \n";
    while(1) {
        int temp = tcpPtr->readFromServer();
        if(temp == -1) {
            std::cout << "Error" << std::endl;
            break;
        } else if(temp != 0) {
            system("clear");
            std::cout<<"Size= "<<temp<<std::endl;            
            for(int i = 0; i< temp; i++) {
                std::cout << tcpPtr->buff[i];
            }
            std::cout << std::endl;
            if(tcpPtr->buff[0]=='e' && tcpPtr->buff[1]=='x' &&
                   tcpPtr->buff[2]=='i' && tcpPtr->buff[3]=='t') {
                tcpPtr->closeIT();
                _exit(0);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void threadFunction() {
    Tcp tcpclient;
    tcpPtr = &tcpclient;
    std::cout << "new c++ thread ID: " << std::this_thread::get_id() << std::endl; 
    while(1) {
        std::string str;
        std::cout << "Enter string\n";
        char s[10];
        std::cin >> s;
        str.append(s);
        tcpclient.sendToServer(str);
        //std::cout << str << std::endl;
        //auto end = std::chrono::system_clock::now();
        //time_t end_time = std::chrono::system_clock::to_time_t(end);
        //std::string str1 = ctime(&end_time);
        //To sleep a thread for 200 Milliseconds
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        //system("clear");
    }   
}
