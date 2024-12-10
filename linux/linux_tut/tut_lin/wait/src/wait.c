#include "wait.h"

#ifndef __USE_POSIX
    #define __USE_POSIX
    #define __USE_XOPEN_EXTENDED
    #define __USE_XOPEN2K
#endif

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

char buf[1024] = {0};

void sigChildHandler(int sig) {
    printf("sig - %d DELETE ZOMBIE\n", sig);
    //errno = 0;
    int savedErrno = 0;
    savedErrno = errno;
    int wStatus = 0;
    printf("errno = %d\n", errno);
    int status = 0;
    while ((wStatus = waitpid(-1, &status, WNOHANG)) > 0) {
        printf("Status = %x, WaitStatus = %d\n", status, wStatus);
    }
    errno = savedErrno;
    if (savedErrno) {
        printf("SavedErrno = %d\n", savedErrno);
        perror("SavedErrno num");
    }
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    // register signal handler
    struct sigaction sig_stru;
    sigemptyset(&sig_stru.sa_mask);
    sig_stru.sa_flags = SA_RESTART;
    sig_stru.sa_handler = sigChildHandler;
    if (sigaction(SIGCHLD, &sig_stru, NULL) == -1) {
        perror("sig child");
        exit(EXIT_FAILURE);
    }

    pid_t fd = 0;
    pid_t fd1 = 0;

    if (!(fd = fork())) {
        // child
        printf("child, parent pid = %d, child pid = %d\n", getppid(), getpid());
        usleep(100);
        return 1;
    }
    if (!(fd1 = fork())) {
        // child
        printf("child, parent pid = %d, child pid = %d\n", getppid(), getpid());
        usleep(200);
        return 2;
    }
    // parent
    sleep(1); // exit from here on SIGCHILD signal ???
    sleep(1); // exit from here on SIGCHILD signal ???
    //int status = 0;
    //pid_t ch = wait(&status);
    //if (WIFEXITED(status)) {
    //    printf("child exit status = %x, nstat %x ch = %d\n", status,
    //           WEXITSTATUS(status), ch);
    //} else if (WIFSIGNALED(status)) {
    //    // childpid = WSTOPSIG(exit_status);
    //    printf("Process with PID=%d "
    //           "has exited with signal %d\n",
    //           ch, WTERMSIG(status));
    //}
    
    printf("parent, child pid = %d\n", fd);
    printf("parent, child pid = %d\n", fd1);

    return 0;
}
