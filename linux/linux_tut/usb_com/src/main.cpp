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

#include <iomanip>
#include <list>
#include <sstream>
struct __attribute__((__packed__)) Temperatures {
    uint8_t num0 = 0;
    float temp0 = 0;
    uint8_t num1 = 1;
    float temp1 = 0;
    uint8_t num2 = 2;
    float temp2 = 0;
    uint8_t num3 = 3;
    float temp3 = 0;
    uint8_t num4 = 4;
    float temp4 = 0;
    uint8_t num5 = 5;
    float temp5 = 0;
    uint8_t num6 = 6;
    float temp6 = 0;
};
std::string getTimeStr() {
    std::time_t now =
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string s(30, '\0');
    std::strftime(&s[0], s.size(), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return s;
}

void write_task(int fd);
void read_task(int fd);

int main(int argc, char** argv) {
    system("stty -F /dev/ttyACM0 9600 raw -clocal -echo icrnl");
    int fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);
    if (fd < 0) { /* Error Checking */
        printf("\n  Error! in Opening ttyACM0  ");
        exit(0);
    }
    printf("\n  ttyACM0 Opened Successfully ");

    std::thread threadWrite(write_task, fd);
    std::thread threadRead(read_task, fd);
    threadWrite.join();
    threadRead.join();
    while (1) {}
    return 0;
}

void write_task(int fd) {
    char sym = 0;
    while (1) {
        std::cout << "Write char" << std::endl;
        std::cin >> sym;
        std::cout << "Entered char = " << sym << std::endl;

        if (sym == 'q') {
            std::cout << "Quit" << std::endl;
            exit(0);
        }
        /*-------------- Write data to serial port _-------------------------*/
        write(fd, &sym, 1);
    }
}

void read_task(int fd) {
    system("rm logTemperature.csv");
    std::fstream logFile;
    // std::ios::out gives us an output filestream
    // std::ios::app is the open mode "append" meaning
    // new data will be written to the end of the file.
    logFile.open("logTemperature.csv", std::ios::app);
    if (!logFile.is_open()) { std::cout << "Can't open file " << std::endl; }
    /*------------------ Read data from serial port -------------------------*/
    /* Buffer to store the data received              */
    uint8_t read_buffer[sizeof(Temperatures)] = {0};
    int bytes_read = 0; /* Number of bytes read by the read() system call */
    auto start_time = std::chrono::high_resolution_clock::now();
    while (1) {
        /* Read the data */
        //TODO poll function
        bytes_read = read(fd, &read_buffer, sizeof(Temperatures));
        system("clear");
        if (bytes_read < 0) {
            std::cout << "Error: " << bytes_read << std::endl;
        } else if (!bytes_read) {
            std::cout << "No DATA: " << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            continue;
        }
        /* Print the number of bytes read */
        Temperatures* tPtr = (Temperatures*)read_buffer;
        printf("T1 = %.2f \u2103\t", tPtr->temp0);
        printf("T2 = %.2f \u2103\t", tPtr->temp1);
        printf("T3 = %.2f \u2103\t", tPtr->temp2);
        printf("T4 = %.2f \u2103\t", tPtr->temp3);
        printf("T5 = %.2f \u2103\t", tPtr->temp4);
        printf("T6 = %.2f \u2103\t", tPtr->temp5);
        std::cout << getTimeStr() << std::endl;

        std::string str = "";
        auto current_time = std::chrono::high_resolution_clock::now();
        str.append(
            std::to_string(std::chrono::duration_cast<std::chrono::seconds>(
                               current_time - start_time)
                               .count()) +
            ",");
        std::stringstream stream0;
        stream0 << std::fixed << std::setprecision(2) << tPtr->temp0;
        std::string s0 = stream0.str();
        std::stringstream stream1;
        stream1 << std::fixed << std::setprecision(2) << tPtr->temp1;
        std::string s1 = stream1.str();
        std::stringstream stream2;
        stream2 << std::fixed << std::setprecision(2) << tPtr->temp2;
        std::string s2 = stream2.str();
        std::stringstream stream3;
        stream3 << std::fixed << std::setprecision(2) << tPtr->temp3;
        std::string s3 = stream3.str();
        std::stringstream stream4;
        stream4 << std::fixed << std::setprecision(2) << tPtr->temp4;
        std::string s4 = stream4.str();
        std::stringstream stream5;
        stream5 << std::fixed << std::setprecision(2) << tPtr->temp5;
        std::string s5 = stream5.str();
        str.append(s0 + "," + s1 + "," + s2 + "," + s3 + "," + s4 + "," + s5);
        str.append("\n");
        //std::cout << str << std::endl;
        ////////////    write in file  ///////////////////////////
        // logFile.write(str.data(), str.size());
        logFile << str; // << std::endl;
        logFile.flush();
        //////////////////////////////////////////////////////////
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    logFile.close();
    /* Close the serial port */
    close(fd);
}
