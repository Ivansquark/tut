#include "file.h"

#include "fcntl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

char buf[1024] = {0};

int main(int argc, char** argv) {
    int fd;
    if (argc == 1) {
        int r_sz;
        char buff[1024] = {0};
        while ((r_sz = read(STDIN_FILENO, buff, 1024)) > 0) {
            printf("r_sz = %d\n", r_sz);
        }
        fprintf(stdout, "%s\n", buff);
        return 0;
    }
    fd = open("file.txt", O_CREAT | O_RDWR, 00644);
    if (fd == -1) {
        perror("error: no creation");
    }
    char* buf_w = argv[1];
    int w_sz = write(fd, buf_w, strlen(buf_w));
    printf("w_size = %d\n", w_sz);
    close(fd);
    fd = open("file.txt", O_RDONLY, 00644);
    // int r_sz = read(fd, buf, 16);
    int r_sz;
    while ((r_sz = read(fd, buf, 1024)) > 0) {
        printf("r_sz = %d\n", r_sz);
    }
    close(fd);
    fprintf(stdout, "%s\n", buf);

    return 0;
}
