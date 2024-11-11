#include "sig.h"

#include <ctype.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <wait.h>

int ret = 0;

void sig_handler() {
    printf("get sig \r\n");
    ret = 1;
}
void sig_handler1() { printf("get sig 1\r\n"); }

int main(int argc, char** argv) {
    pid_t res;
    time_t now = time(NULL);
    int child_counter = 0, parent_counter = 0;
    int childpid = 0;
    if (argc < 2) {
        fprintf(stderr, "low arguments in %s\r\n", argv[0]);
        return 1;
    }
    res = fork();
    if (res == -1) {
        fprintf(stderr, "fork error\r\n");
        return 1;
    }
    if (!res) {
        while (time(NULL) < now + 2) child_counter++;
        childpid = getpid();
        fprintf(stdout, "Child num = %d\r\n", childpid);
        fprintf(stdout, "Child parent num = %d\r\n", getppid());
        fprintf(stdout, "Child counter = %d\r\n", child_counter);
        struct sigaction act;
        sigemptyset(&act.sa_mask);
        act.sa_handler = &sig_handler;
        act.sa_flags = NULL;
        if (sigaction(SIGINT, &act, NULL) == -1) {
            printf("NULL SIGACTION");
            fflush(stdout);
            return 1;
        }
        while (!ret) {}
        char* arg[] = {(char*)"cat",       (char*)argv[0], (char*)">",
                       (char*)"/dev/zero", (char*)"&",     NULL};
        execve("/bin/cat", arg, NULL);
    }
    //--------- WAIT -------------------------------------------
    // int childpid = wait(&exit_status);
    while (time(NULL) < now + 2) parent_counter++;
    fprintf(stdout, "Parent num = %d\r\n", getpid());
    fprintf(stdout, "Parent counter = %d\r\n", parent_counter);
    sleep(2);
    struct sigaction act1;
    sigemptyset(&act1.sa_mask);
    act1.sa_handler = &sig_handler1;
    act1.sa_flags = NULL;
    if (sigaction(SIGINT, &act1, NULL) == -1) {
        printf("NULL SIGACTION 1");
        fflush(stdout);
        return 1;
    }
    while (1) {}
    // kill(childpid, SIGABRT);
    return 0;
}
