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

    sock = socket(AF_INET, SOCK_STREAM, 0);
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

int threat_sock(int num) {
    // after accept;
    // TODO: read write through epoll
    printf("threat_sock %d\n", num);
    while (1) {}

    int epfd = epoll_create1(EPOLL_CLOEXEC);
    if (epfd < 0) {
        perror("epoll\n");
        return -1;
    }
    struct epoll_event evt = {.events = EPOLLIN, .data.fd = 0};
    epoll_ctl(epfd, EPOLL_CTL_ADD, num, &evt);
    evt.events = EPOLLOUT;
    evt.data.fd = 1;
    epoll_ctl(epfd, EPOLL_CTL_ADD, num, &evt);
    char buf[4096] = {0};
    while (1) {
        epoll_wait(epfd, &evt, 1, -1);
        if (evt.data.fd == STDIN_FILENO) {
            int res = 0;
            if ((res = read(num, buf, sizeof(buf))) < 0) {
                perror("read");
                close(num);
                return -1;
            } else if (!res) {
                printf("Disconnect %d\n", num);
                break;
            }
            // int res = parse(buf);
            write(num, buf, res); // echo make nonblock
        } else if (evt.data.fd == STDOUT_FILENO) {
            printf("writed: %s", buf);
            memset(buf, 0, sizeof(buf));
            // timer to close connection
        }
    }
    close(num);
    return 0;
}
void threat_stdStream(int num) { printf("threat_stream %d\n", num); }

int main(int argc, char** argv) {
    threadpool_create();
    // fptr f = {threat_sock, 5};
    // threadpool_add_task(&f);

    if (argc < 2) {
        fprintf(stderr, "USAGE %s SERVICE\n", argv[0]);
        return 1;
    }

    int sock = create_listner(argv[1]);
    if (sock < 0) {
        return 1;
    }

    while (1) {
        int connection = accept(sock, NULL, NULL);
        printf("Connection %d\n", connection);
        if (connection < 0) {
            perror("accept error");
            return 2;
        }
        fptr f = {threat_sock, connection};
        threadpool_add_task(&f);
    }

    return 0;
}
