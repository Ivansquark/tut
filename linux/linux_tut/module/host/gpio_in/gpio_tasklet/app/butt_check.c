#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>

#define DEVICE_PATH "/dev/zynq_gpio_buttons"

void signal_handler(int signo, siginfo_t *info) {
    int fd;
    int button_states[5];

    // Open the device file
    fd = open(DEVICE_PATH, O_RDONLY);
    if (fd < 0) {
        perror("Failed to open device file");
        return;
    }

    // Read the button states
    if (read(fd, button_states, sizeof(button_states)) < 0) {
        perror("Failed to read button states");
    } else {
        printf("Button states: %d %d %d %d %d\n", 
               button_states[0], button_states[1], 
               button_states[2], button_states[3], 
               button_states[4]);
    }

    // Close the device file
    close(fd);
}

int main() {
    struct sigaction sa;

    // Set up the signal handler
    sa.sa_sigaction = signal_handler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);

    // Open the device file
    int fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("Failed to open device file");
        return EXIT_FAILURE;
    }

    // Pass PID to the kernel module
    pid_t pidd = getpid();
    if (ioctl(fd, 0, &pidd) < 0) {
        perror("Failed to send PID to kernel module");
        close(fd);
        return EXIT_FAILURE;
    }

    printf("Listening for button presses... (PID: %d)\n", getpid());

    // Keep the application running
    while (1) {
        pause(); // Wait for signals
    }

    // Close the device file
    close(fd);
    return EXIT_SUCCESS;
}
