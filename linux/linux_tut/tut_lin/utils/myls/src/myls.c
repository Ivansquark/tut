#include "myls.h"

#ifndef __USE_POSIX
    #define __USE_POSIX
    #define __USE_XOPEN_EXTENDED
    #define __USE_XOPEN2K
#endif

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#define MAXPATH 1000

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    if(argc < 2) {
        perror(argv[0]);
        return EXIT_FAILURE;
    }
    const char* dirname = argv[1];
    DIR *d = opendir(dirname);
    struct dirent* ent;
    while((ent = readdir(d))) {
        char buf[MAXPATH];
        snprintf(buf, sizeof(buf), "%s/%s", dirname, ent->d_name);
        printf("%s\n", buf);
    }
    return 0;
}
