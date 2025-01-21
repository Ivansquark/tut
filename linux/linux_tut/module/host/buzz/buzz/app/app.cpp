#include <cstring>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define DEVICE_PATH "/dev/buzz"
#define SYSFS_PATH "/sys/kernel/buzz"

// Function to write data to the device file
int write_to_device(const std::string& data) {
    int fd = open(DEVICE_PATH, O_WRONLY);
    if (fd < 0) {
        std::cerr << "Error opening device: " << strerror(errno) << std::endl;
        return -1;
    }

    ssize_t ret = write(fd, data.c_str(), data.size());
    if (ret < 0) {
        std::cerr << "Error writing to device: " << strerror(errno)
                  << std::endl;
        close(fd);
        return -1;
    }

    std::cout << "Data written to device: " << data << std::endl;
    close(fd);
    return 0;
}

// Function to read from a sysfs file
int read_from_sysfs(const std::string& attr) {
    std::ifstream file(SYSFS_PATH + attr);
    if (!file.is_open()) {
        std::cerr << "Error opening sysfs file: " << strerror(errno)
                  << std::endl;
        return -1;
    }

    std::string value;
    std::getline(file, value);
    std::cout << attr << ": " << value << std::endl;
    return 0;
}

// Function to write to a sysfs file
int write_to_sysfs(const std::string& attr, const std::string& value) {
    std::ofstream file(SYSFS_PATH + attr);
    if (!file.is_open()) {
        std::cerr << "Error opening sysfs file: " << strerror(errno)
                  << std::endl;
        return -1;
    }

    file << value;
    if (!file) {
        std::cerr << "Error writing to sysfs file: " << strerror(errno)
                  << std::endl;
        return -1;
    }

    std::cout << "Data written to sysfs: " << attr << " = " << value
              << std::endl;
    return 0;
}

int main() {
    std::string user_input;

    // Test writing to device
    std::cout << "Enter frequency and time (e.g., 1000,500): ";
    std::getline(std::cin, user_input);

    if (write_to_device(user_input) < 0) {
        return -1;
    }

    // Test writing to sysfs (setting frequency and time)
    std::string frequency, time;
    std::cout << "Enter frequency value (Hz): ";
    std::getline(std::cin, frequency);

    std::cout << "Enter time value (ms): ";
    std::getline(std::cin, time);

    if (write_to_sysfs("frequency", frequency) < 0) return -1;
    if (write_to_sysfs("time", time) < 0) return -1;

    // Test starting PWM signal via sysfs
    if (write_to_sysfs("start", "1") < 0) return -1;

    // Optionally, stop PWM after a short delay
    sleep(3);
    if (write_to_sysfs("start", "0") < 0) return -1;

    // Test reading frequency and time from sysfs
    if (read_from_sysfs("frequency") < 0) return -1;
    if (read_from_sysfs("time") < 0) return -1;

    return 0;
}
