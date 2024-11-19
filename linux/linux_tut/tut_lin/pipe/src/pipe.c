#include "pipe.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv) {
    int pf[2];
    int pid1, pid2;
    if (argc < 1) {
        fprintf(stderr, "Too few arguments\n");
        return 1;
    }
    if (pipe(pf) == -1) {
        fprintf(stderr, "pipe() error\n");
        return 1;
    }
    if (!(pid1 = fork())) {
        dup2(pf[1], STDOUT_FILENO); //stdout
        close(pf[0]);
        close(pf[1]);
        execlp("ls", "ls", "-la", NULL);
        fprintf(stderr, "exec() [1] error\n");
        return 1;
    }
    if (!(pid2 = fork())) {
        dup2(pf[0], STDIN_FILENO); // stdin
        close(pf[0]);
        close(pf[1]);
        //execlp("grep", "grep", argv[1], NULL);
        execlp("tail", "tail", argv[1], NULL);
        fprintf(stderr, "exec() [2] error\n");
        return 1;
    }

    close(pf[1]);
    waitpid(pid1, NULL, 0);
    close(pf[0]);
    waitpid(pid2, NULL, 0);
    return 0;
}
