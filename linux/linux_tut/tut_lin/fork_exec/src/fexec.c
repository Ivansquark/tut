#include "fexec.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, [[maybe_unused]] char** argv) {
    [[maybe_unused]] extern char** environ;
    if (argc < 2) {
        fprintf(stderr, "low arguments\r\n");
        return 1;
    }
    pid_t res;
    int exit_status;
    res = fork();
    time_t now = time(NULL);
    int child_counter = 0, parent_counter = 0;
    if (res == -1) {
        fprintf(stderr, "fork error\r\n");
        return 1;
    }
    if (res == 0) {
        while (time(NULL) < now + 2) child_counter++;
        fprintf(stdout, "Child num = %d\r\n", getpid());
        fprintf(stdout, "Child parent num = %d\r\n", getppid());
        fprintf(stdout, "Child counter = %d\r\n", child_counter);
        // execlp(argv[1], "ls", "-l", "-a", NULL);
        execlp("sleep", "sleep", "30", NULL);
#if 0
        const char* arg[] = {
            "ls",
            "-l",
            NULL
        };
        execve(argv[1], arg, NULL);
        //execve(argv[1], arg, environ);
#endif
    }
    //--------- WAIT -------------------------------------------
    // int childpid = wait(&exit_status);
    int childpid = waitpid(res, &exit_status, 0);
    if (WIFEXITED(exit_status)) {
        printf("Process with PID=%d "
               "has exited with code=%d\n",
               childpid, WEXITSTATUS(exit_status));
    } else if (WIFSIGNALED(exit_status)) {
        // childpid = WSTOPSIG(exit_status);
        printf("Process with PID=%d "
               "has exited with signal.\n",
               childpid);
    }
    while (time(NULL) < now + 2) parent_counter++;
    fprintf(stdout, "Parent num = %d\r\n", getpid());
    fprintf(stdout, "Parent counter = %d\r\n", parent_counter);
    return 0;
}
