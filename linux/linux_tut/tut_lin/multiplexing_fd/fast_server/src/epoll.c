#include "epoll.h"

#ifndef __USE_GNU
    #define __USE_GNU
    #define _GNU_SOURCE /* See feature_test_macros(7) */
#endif

#include <arpa/inet.h>
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
#include <threadpool.h>
#include <unistd.h>

int create_listner(char* service) {
    int port = atoi(service);
    int sock = 0;
    int ip = 0;
    inet_pton(AF_INET, "127.0.0.1", &ip);

    struct sockaddr_in addr = {
        .sin_family = AF_INET, .sin_addr.s_addr = ip, .sin_port = htons(port)};

    sock = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (sock < 0) {
        perror("socket\n");
    }

    if (bind(sock, (const struct sockaddr*)&addr, sizeof(struct sockaddr_in)) <
        0) {
        perror("bind\n");
        return -1;
    }

    if (listen(sock, SOMAXCONN) < 0) {
        perror("listen\n");
        return -1;
    }
    return sock;
}

void threat_sock(int num) {
    // after accept;
    printf("threat_sock %d\n", num);
}
void threat_stdStream(int num) {
    // after accept;
    printf("threat_stream %d\n", num);
}

int main(int argc, char** argv) {
    extern Queue* queue;
    threadpool_create();
    fptr f = {threat_sock, 5};
    queue_push(queue, &f);
    f.arg = 6;
    queue_push(queue, &f);
    fptr s = {threat_stdStream, 1};
    queue_push(queue, &s);
    while(1) {
        //threadpool_handler(&pool, &queue);
    }

    return 0;
    if (argc != 2) {
        fprintf(stderr, "USAGE %s SERVICE\n", argv[0]);
        return 1;
    }

    int sock = create_listner(argv[1]);
    if (sock < 0) {
        return 1;
    }

    int ep = epoll_create1(EPOLL_CLOEXEC);
    if (ep < 0) {
        perror("epoll\n");
        return 1;
    }

    struct epoll_event evt = {.events = EPOLLIN | EPOLLET, .data.fd = sock};
    epoll_ctl(ep, EPOLL_CTL_ADD, sock, &evt);

    while (1) {
        int timeout = -1; // forever
        errno = 0;
        if (epoll_wait(ep, &evt, 1, timeout) < 0) {
            if (errno == EINTR) {
                perror("signal");
                continue;
            }
        }
        // epoll triggered
        int connection = 0;
        if (evt.data.fd == sock) {
            // was connection
            connection = accept4(sock, NULL, NULL, SOCK_NONBLOCK);
            if (connection < 0) {
                perror("connection");
                continue;
            }
            printf("con num = %d\n", connection);
            evt.events = EPOLLIN | EPOLLOUT | EPOLLET;
            evt.data.fd = connection;
            epoll_ctl(ep, EPOLL_CTL_ADD, connection, &evt);

        } else {
            // epoll on connection read or write descriptors
            char buf[1024] = {0};
            int res = 0;

            while ((res = read(evt.data.fd, buf, sizeof(buf)) >= 0)) {
                if (errno == EAGAIN) {
                    printf("readall");
                    break;
                }
                if (errno == EINTR) {
                    printf("errno\n");
                    continue;
                }
                if (!res) {
                    close(evt.data.fd);
                } else {
                    write(evt.data.fd, buf, res);
                    printf("received on %d - %s\n", evt.data.fd, buf);
                }
            }
        }
    }

    return 0;
}
