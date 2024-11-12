#include "pipe.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv) {
    printf("argc = %d\n", argc);
    int pf[2];
    int pid1;
    if (argc < 1) {
        fprintf(stderr, "Too few arguments\n");
        return 1;
    }
    if (pipe(pf) == -1) {
        fprintf(stderr, "pipe() error\n");
        return 1;
    }
    // out first to next in
    for (int i = 0; i < argc - 1; ++i) {
        printf("i = %d\n", i);
        if (!(pid1 = fork())) {
            if (i > 0) {
                dup2(pf[1], 1); // stdout
                close(pf[0]);
            }
            if (i < argc + 1) {
                dup2(pf[0], 0); // stdin
                close(pf[1]);
            }
            execlp(argv[i + 1], argv[i + 1], NULL);
            fprintf(stderr, "exec() [1] error\n");
            return 1;
        }

        close(pf[1]);
        close(pf[0]);
        waitpid(pid1, NULL, 0);
    }

    return 0;
}
