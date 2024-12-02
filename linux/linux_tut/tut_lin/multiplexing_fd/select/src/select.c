#include "select.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <unistd.h>

const char arr[] = "Popeye sailor";

void child(int* pipe) {
    int counter = 0;
    close(pipe[0]);
    while (1) {
        sleep(1);
        dprintf(pipe[1], "%d %d\n", getpid(), counter++);
    }
}

void fork_child(int* pipes, size_t i) {
    pipe(pipes + i * 2);
    if (!fork()) {
        child(pipes + i * 2);
        _exit(0);
    }
}

sig_atomic_t need_fork;

void handler([[maybe_unused]] int sig) { need_fork = 1; }

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    printf("%s\n", arr);
    if (argc < 2) {
        exit(1);
    }
    size_t N = atoi(argv[1]);
    int pipes[N * 2];
    size_t existed_children = 0;

    signal(SIGUSR1, handler);

    sigset_t sigset, oldmask;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGUSR1);
    sigprocmask(SIG_BLOCK, &sigset, &oldmask);

    fd_set readfds;
    while (1) {
        if (need_fork) {
            fork_child(pipes, existed_children++);
            need_fork = 0;
        }
        FD_ZERO(&readfds);
        int max = 0;
        for (size_t i = 0; i < existed_children; ++i) {
            int fd = pipes[i * 2];
            FD_SET(fd, &readfds);
            max = max < fd ? fd : max;
        }
        struct timespec tv;
        tv.tv_sec = 10;
        tv.tv_nsec = 0;

        if (pselect(max + 1, &readfds, NULL, NULL, &tv, &oldmask) < 0) {
            if (errno == EINTR) {
                continue;
            }
            perror("select");
            return 1;
        }
        for (size_t i = 0; i < existed_children; i++) {
            int fd = pipes[i * 2];
            if (FD_ISSET(fd, &readfds)) {
                char buf[1024] = {0};
                read(fd, buf, sizeof(buf) - 1);
                printf("%s (%ld sec %ld nsec left)\n", buf, tv.tv_sec,
                       tv.tv_nsec);
            }
        }
    }
}
