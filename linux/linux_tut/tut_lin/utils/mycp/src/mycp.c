#include "mycp.h"

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
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#ifndef BUF_SIZE
    #define BUF_SIZE 1024
#endif

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    int inputFd, outputFd, openFlags;
    mode_t filePerms;
    ssize_t numRead;
    char buf[BUF_SIZE];

    if (argc != 3 || !strcmp(argv[1], "--help")) {
        perror(argv[0]);
        return EXIT_FAILURE;
    }
    inputFd = open(argv[1], O_RDONLY, 0400);
    if (inputFd < 0) {
        perror("Cant open");
        printf("%s\n", argv[1]);
        return EXIT_FAILURE;
    }
    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    /* rw-rw-rw- */
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    outputFd = open(argv[2], openFlags, filePerms);
    if (outputFd == -1) {
        perror("Cant open");
        printf("%s\n", argv[2]);
        return EXIT_FAILURE;
    }

    while ((numRead = read(inputFd, buf, sizeof(buf))) > 0) {
        write(outputFd, buf, numRead);
    }
    if(numRead == -1) {
        perror("Read Error");
        return EXIT_FAILURE;
    }
    if(close(inputFd) == -1) {
        perror("close inputFd");
        return EXIT_FAILURE;
    }
    if(close(outputFd) == -1) {
        perror("close outputFd");
        return EXIT_FAILURE;
    }
    
    exit(EXIT_SUCCESS);
    return 0;
}
