#include "epoll.h"

#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int create_listner(char* service) {
    struct addrinfo* res = NULL;
    int gai_err;
    struct addrinfo hint = {
        .ai_family = AF_UNSPEC,
        .ai_socktype = SOCK_STREAM,
        .ai_flags = AI_PASSIVE,
    };
    if ((gai_err = getaddrinfo(NULL, service, &hint, &res))) {
        fprintf(stderr, "gai_err %s\n", gai_strerror(gai_err));
        return -1;
    }
    int sock = -1;
    for (struct addrinfo* ai = res; ai; ai = ai->ai_next) {
        sock = socket(ai->ai_family, ai->ai_socktype, 0);
        if (sock < 0) {
            perror("socket");
            continue;
        }
        int one = 1;
        setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
        if (bind(sock, ai->ai_addr, ai->ai_addrlen) < 0) {
            perror("bind");
            close(sock);
            sock = -1;
            continue;
        }
        break;
    }
    freeaddrinfo(res);
    return sock;
}

int main(int argc, char** argv) {
    printf("epoll\n");
    if (argc != 2) {
        fprintf(stderr, "USAGE %s SERVICE\n", argv[0]);
        return 1;
    }
    int sock = create_listner(argv[1]);
    if (sock < 0) {
        return 1;
    }

    int epollfd = epoll_create1(0);
    if (epollfd < 0) {
        perror("epoll");
        return 1;
    }

    struct epoll_event evt = {.events = EPOLLIN, .data.fd = sock};
    epoll_ctl(epollfd, EPOLL_CTL_ADD, sock, &evt);

    while (1) {
        int timeout = -1; // block indefinitly
        errno = 0;
        if (epoll_wait(epollfd, &evt, 1, timeout) < 1) {
            if (errno == EINTR) {
                continue;
            }
            perror("select");
            return 1;
        }
        if (evt.data.fd == sock) {
            int connection = accept(sock, NULL, NULL);

            struct epoll_event evt = {.events = EPOLLIN, .data.fd = connection};
            epoll_ctl(epollfd, EPOLL_CTL_ADD, connection, &evt);

        } else {
            char buf[1024] = {0};
            ssize_t res = read(evt.data.fd, buf, sizeof(buf) - 1);
            if (res == 0) {
                close(evt.data.fd);
            } else {
                write(evt.data.fd, buf, res);
                printf("fd %d: %s\n", evt.data.fd, buf);
            }
        }
    }

    return 0;
}
