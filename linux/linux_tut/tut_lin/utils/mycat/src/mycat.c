#include "mycat.h"

#ifndef __USE_POSIX
    #define __USE_POSIX
    #define __USE_XOPEN_EXTENDED
    #define __USE_XOPEN2K
#endif

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    //char buf[4096] = {0};
    char buf[100] = {0};
    int res = 0;
    int fd = 0;
    if (argc < 2) {
        fd = STDIN_FILENO;
    } else {
        if ((fd = open(argv[1], O_RDONLY, 0600)) < 0) {
            fprintf(stderr, "cant open file for read %s", argv[1]);
            return EXIT_FAILURE;
        }
    }

    while ((res = read(fd, buf, sizeof(buf))) >= 0) {
        if (!res) {
            perror("EOF");
            close(fd);
            return EOF;
        } else {
            if (argc == 3) {
                int fd_w = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
                if (fd_w < 0) {
                    fprintf(stderr, "cant open file for write %s", argv[2]);
                    return 2;
                }
                write(fd_w, buf, res);
            } else {
                write(STDOUT_FILENO, buf, res);
            }
        }
    }
    return 0;
}
