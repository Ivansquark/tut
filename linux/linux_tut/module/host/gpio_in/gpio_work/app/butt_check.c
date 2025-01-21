#include <iostream>
#include <fstream>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define DEVICE_PATH "/dev/button_driver"  // Path to the kernel device file

// Global variable to store the PID of the process
pid_t pid = -1;

// Signal handler for SIGUSR1
void signal_handler(int signum) {
    if (signum == SIGUSR1) {
        // If a signal is received, read the current button state
        std::ifstream button_device(DEVICE_PATH);
        if (!button_device.is_open()) {
            std::cerr << "Failed to open device file." << std::endl;
            return;
        }

        std::string line;
        while (std::getline(button_device, line)) {
            std::cout << line << std::endl;  // Output the pressed button(s)
        }
    }
}

// Function to set the process ID (PID) to send signals to the kernel module
void set_pid(pid_t process_pid) {
    std::ofstream button_device(DEVICE_PATH);
    if (!button_device.is_open()) {
        std::cerr << "Failed to open device file for writing PID." << std::endl;
        return;
    }

    button_device << process_pid << std::endl;
    button_device.close();
}

int main() {
    // Register the signal handler
    if (signal(SIGUSR1, signal_handler) == SIG_ERR) {
        std::cerr << "Error registering signal handler." << std::endl;
        return 1;
    }

    std::cout << "Enter the PID of this process to send signals: ";
    std::cin >> pid;

    // Set the PID in the kernel module
    set_pid(pid);

    // Notify the user
    std::cout << "Press buttons to send signals to this process..." << std::endl;

    // Infinite loop to keep the program running and receiving signals
    while (true) {
        pause();  // Wait for signals to be received
    }

    return 0;
}

