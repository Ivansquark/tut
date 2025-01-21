#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// Define device path and sysfs paths for easy access
#define DEVICE_PATH "/dev/buzz"
#define SYSFS_PATH "/sys/kernel/buzz"

// Function to write data to the device
int write_to_device(const char* data) {
    int fd = open(DEVICE_PATH, O_WRONLY);
    if (fd < 0) {
        perror("Error opening device");
        return -1;
    }

    // Write the data to the device
    ssize_t ret = write(fd, data, strlen(data));
    if (ret < 0) {
        perror("Error writing to device");
        close(fd);
        return -1;
    }

    printf("Data written to device: %s\n", data);
    close(fd);
    return 0;
}

// Function to read data from the sysfs interface (e.g., frequency and time)
int read_from_sysfs(const char* attr) {
    char path[256];
    char buffer[256];
    FILE* file;
    snprintf(path, sizeof(path), "%s/%s", SYSFS_PATH, attr);

    file = fopen(path, "r");
    if (!file) {
        perror("Error opening sysfs file");
        return -1;
    }

    if (!fgets(buffer, sizeof(buffer), file)) {
        perror("Error reading sysfs file");
        fclose(file);
        return -1;
    }

    printf("%s: %s", attr, buffer);
    fclose(file);
    return 0;
}

// Function to write to the sysfs interface (e.g., setting frequency, time, or
// starting PWM)
int write_to_sysfs(const char* attr, const char* value) {
    char path[256];
    FILE* file;
    snprintf(path, sizeof(path), "%s/%s", SYSFS_PATH, attr);

    file = fopen(path, "w");
    if (!file) {
        perror("Error opening sysfs file");
        return -1;
    }

    if (fprintf(file, "%s", value) < 0) {
        perror("Error writing to sysfs file");
        fclose(file);
        return -1;
    }

    printf("Data written to sysfs: %s = %s\n", attr, value);
    fclose(file);
    return 0;
}

int main() {
    char user_input[64];

    // Test writing to device
    printf("Enter frequency and time (e.g., 1000,500): ");
    fgets(user_input, sizeof(user_input), stdin);
    user_input[strcspn(user_input, "\n")] = 0; // Remove newline character

    if (write_to_device(user_input) < 0) {
        return -1;
    }

    // Test writing to sysfs (setting frequency and time)
    char frequency[64], time[64];
    printf("Enter frequency value (Hz): ");
    fgets(frequency, sizeof(frequency), stdin);
    frequency[strcspn(frequency, "\n")] = 0;

    printf("Enter time value (ms): ");
    fgets(time, sizeof(time), stdin);
    time[strcspn(time, "\n")] = 0;

    if (write_to_sysfs("frequency", frequency) < 0) return -1;
    if (write_to_sysfs("time", time) < 0) return -1;

    // Test starting PWM signal via sysfs
    if (write_to_sysfs("start", "1") < 0) return -1;

    // Optionally, we can stop PWM after a short delay
    sleep(3);
    if (write_to_sysfs("start", "0") < 0) return -1;

    // Test reading frequency and time from sysfs
    if (read_from_sysfs("frequency") < 0) return -1;
    if (read_from_sysfs("time") < 0) return -1;

    return 0;
}
