#include "run.h"

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
    execv(argv[1], argv + 2);
    perror(argv[1]);
    _exit(127); //not flush stdout
}
