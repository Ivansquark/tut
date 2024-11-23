#include "fifo.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

char arr[1024] = "opa\n";

void* thread_fifo(void* arg) {
    FILE* f;
    int fd;
    f = fopen("myfifo", "r+");
    printf("File des Num thread = %d\n", f->_fileno);
    fd = f->_fileno;
    while (1) {
        int sz = read(fd, arr, 1024);
        if (sz > 0) {
            printf(arr);
            break;
        }
    }
    strcpy(arr, "jopa\n");
    write(fd, arr, 6);
    close(fd);
    return 0;
}

int main(int argc, char** argv) {
    FILE* f;
    int fd = 0;
    pthread_t pt1;
    if (mkfifo("myfifo", 0644) == -1) {
        fprintf(stderr, "error: fifo not created\r\n");
    }
    pthread_create(&pt1, NULL, thread_fifo, NULL);
    f = fopen("myfifo", "r+");
    // blocked till opened on read
    fd = f->_fileno;
    printf("File des Num = %d\n", f->_fileno);
    write(fd, arr, 4);
    pthread_join(pt1, NULL);
    while (1) {
        int sz = read(fd, arr, 1024);
        if (sz > 0) {
            printf(arr);
            break;
        }
    }
    close(fd);
    unlink("myfifo");
    return 0;
}
