#include <atomic>
#include <chrono>
#include <ctime>
#include <errno.h> /* ERROR Number Definitions           */
#include <fcntl.h> /* File Control Definitions           */
#include <iostream>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <unistd.h>

#include <fstream>
#include <mutex>

#include "image.h"

#include <string.h>

void read_task(int fd);
void write_task(int fd);
void receive_task(int fd);

bool Start = false;
std::atomic<bool> WaitReply;
std::mutex mut;

uint8_t arrSend[64] = {0};

int main(int argc, char** argv) {
    system("stty -F /dev/ttyACM0 921600 raw -clocal -echo icrnl");
    int fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);
    if (fd < 0) { /* Error Checking */
        printf("\n  Error! in Opening ttyACM0  ");
        exit(0);
    }
    printf("\n  ttyACM0 Opened Successfully ");

    // std::thread threadWrite(write_task, fd);
    // std::thread threadRead(read_task, fd);
    // threadWrite.join();
    // threadRead.join();
    //
    WaitReply.store(false);
    std::thread threadReceive(receive_task, fd);
    while (1) {
        write_task(fd);
        read_task(fd);
    }
    // while (1) {}
    return 0;
}

void write_task(int fd) {
    char sym = 0;
    while (1) {
        std::cout << "Write char" << std::endl;
        std::cin >> sym;
        if (sym == 's') {
            Start = true;
            break;
        }
    }
}

void read_task(int fd) {
    if (!Start) { return; }
    // system("rm raw.bin");
    // std::fstream rawFile;
    // std::ios::out gives us an output filestream
    // std::ios::app is the open mode "append" meaning
    // new data will be written to the end of the file.
    // rawFile.open("raw.bin", std::ios::app);
    // if (!rawFile.is_open()) { std::cout << "Can't open file " << std::endl; }

    /* Buffer to store the data received              */
    ////////////    write in file  ///////////////////////////
    //uint8_t sizePage[256] = {0};
    //memset(sizePage, 0xff, sizeof(sizePage));
    // uint8_t sizePage = sizeof(image) / 40960;
    // rawFile.write((const char*)sizePage, sizeof(sizePage));
    // rawFile.write((const char*)image, sizeof(image));
    // rawFile.flush();
    // rawFile.close();
    //////////////////////////////////////////////////////////

    char startArr[5] = {'S', 'T', 'A', 'R', 'T'};
    write(fd, (uint8_t*)startArr, 5);
    mut.lock();
    WaitReply = true;
    while (WaitReply) {}
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    //for (int i = 0; i < 4; i++) {
    //    write(fd, (uint8_t*)sizePage + i * 64, 64);
    //    WaitReply = true;
    //    while (WaitReply) {}
    //}
    //uint8_t* ptr = (uint8_t*)image;
    //*ptr = sizePage[0];
    //image[1] = sizePage[0];
    std::cout << "image_size = " << sizeof(image) << std::endl;
    uint8_t sizePage = sizeof(image) / 40960;
    int len = sizeof(image) / 64;
    for (int i = 0; i < len; i++) {
        memcpy(arrSend, (uint8_t*)image + i * 64, 64);
        if(!i) {
            arrSend[0] = sizePage;
        }
        write(fd, (uint8_t*)arrSend, 64);
        WaitReply = true;
        mut.lock();
        while (WaitReply) {}
        std::cout << "number = " << i << "\t\t from len = " << len << std::endl;
    }
    char stopArr[5] = {'S', 'T', 'O', 'P'};
    write(fd, (uint8_t*)stopArr, 4);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "FINISH";
    exit(0);
}

void receive_task(int fd) {
    while (1) {
        if (WaitReply) {
            uint8_t arr[1] = {0};
            int i = read(fd, arr, 1);
            if (arr[0] == 1) { 
                arr[0] = 0;
                mut.unlock();
                WaitReply.store(false);
            }
        }
    }
}
