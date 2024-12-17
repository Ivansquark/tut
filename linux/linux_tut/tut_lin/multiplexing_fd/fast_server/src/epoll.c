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
        return 1;
    }
    int reuse = 1;
    int result = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void*)&reuse,
                            sizeof(reuse));
    if (result < 0) {
        perror("setsockopt\n");
        return 1;
    }

    if (bind(sock, (const struct sockaddr*)&addr, sizeof(struct sockaddr_in)) <
        0) {
        perror("bind\n");
        return 1;
    }

    if (listen(sock, SOMAXCONN) < 0) {
        perror("listen\n");
        return -1;
    }
    return sock;
}

int threat_sock(int num) {
    // after accept;
    printf("threat_sock %d\n", num);

    int epfd = epoll_create1(EPOLL_CLOEXEC);
    if (epfd < 0) {
        perror("epoll\n");
        return -1;
    }
    struct epoll_event evt = {.events = EPOLLIN | EPOLLOUT | EPOLLET,
                              .data.fd = 0};
    epoll_ctl(epfd, EPOLL_CTL_ADD, num, &evt);
    // evt.events = EPOLLOUT;
    // evt.data.fd = 1;
    // epoll_ctl(epfd, EPOLL_CTL_ADD, num, &evt);
    char buf[4096] = {0};
    epoll_wait(epfd, &evt, 1, -1);
    if (evt.data.fd == STDIN_FILENO) {
        int res = 0;
        while ((res = read(num, buf, sizeof(buf))) >= 0) {
            if (errno == EAGAIN) {
                perror("readall");
            }
            if (!res) {
                printf("Disconnect %d\n", num);
                break;
            } else {
                // int res = parse(buf);
                write(num, buf, res); // echo make nonblock
            }
        }
    }
    close(num);
    close(epfd);
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
    // int count = 0;
    while (1) {

        int connection = accept(sock, NULL, NULL);
        printf("Connection %d\n", connection);
        if (connection < 0) {
            perror("accept error");
            return 2;
        }
        fptr f = {threat_sock, connection};
        // fptr f = {threat_sock, count++};
        threadpool_add_task(&f);
    }

    return 0;
}
