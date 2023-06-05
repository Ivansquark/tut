#include "main.h"
#include "pthread.h"
#include "tcp.h"
#include "time.h"
#include "wait.h"
#include <chrono>
#include <iostream>
#include <stdio.h>
#include <thread>
#include <unistd.h>

void threadFunction();
int main(int argc, char **argv) {
    //Tcp::instance();
    std::thread thr(threadFunction);
    thr.join();
    return 0;
}
void threadFunction() {
    std::cout << "new c++ thread ID: " << std::this_thread::get_id() << std::endl;
    Tcp::instance();
    Tcp::instance()->init_server(); // call constructor
    while (1) {
        //auto end = std::chrono::system_clock::now();
        //time_t end_time = std::chrono::system_clock::to_time_t(end);
        //std::string str = ctime(&end_time);
        // To sleep a thread for 200 Milliseconds
        //std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        //system("clear");
    }
}
