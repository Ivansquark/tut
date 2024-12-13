#include "epoll_client.h"

#ifndef __USE_XOPEN2K
    #define __USE_GNU
    #define __USE_XOPEN2K
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
#include <unistd.h>

struct addrinfo* get_addr(char* service, char* port) {
    printf("service - %s\n", service);
    struct addrinfo* res = NULL;
    int gai_err;
    struct addrinfo hint = {
        .ai_family = AF_INET,
        //.ai_family = AF_UNSPEC,
        //.ai_socktype = SOCK_DGRAM,
        .ai_socktype = SOCK_STREAM,
        .ai_flags = AI_PASSIVE,
    };
    if ((gai_err = getaddrinfo(service, port, &hint, &res))) {
        fprintf(stderr, "gai_err %s\n", gai_strerror(gai_err));
        return 0;
    }

    for (struct addrinfo* ai = res; ai; ai = ai->ai_next) {
        char buf[1024] = {0};
        printf("ai->flags=%d, ai->fam=%d, ai->socktype=%d\n", ai->ai_flags,
               ai->ai_family, ai->ai_socktype);
        struct sockaddr_in* inet;
        struct sockaddr_in6* inet6;
        switch (ai->ai_family) {
        case AF_INET:
            inet = (struct sockaddr_in*)ai->ai_addr;
            printf("address - %s, port - %hu\n",
                   inet_ntop(ai->ai_family, &inet->sin_addr, buf, sizeof(buf)),
                   htons(inet->sin_port));
            break;
        case AF_INET6:
            inet6 = (struct sockaddr_in6*)ai->ai_addr;
            printf(
                "address - %s, port - %hu\n",
                inet_ntop(ai->ai_family, &inet6->sin6_addr, buf, sizeof(buf)),
                htons(inet6->sin6_port));
            break;
        default:
            break;
        }
    }
    // printf(res->ai_addr->sa_data);
    return res;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        fprintf(stderr, "USAGE %s SERVICE\n", argv[0]);
        return 1;
    }
    struct addrinfo* addr = get_addr(argv[1], argv[2]);
    if (!addr) {
        perror("Unknown addr");
        return 1;
    }
    int sock = socket(addr->ai_family, addr->ai_socktype, 0);
    if (sock < 0) {
        perror("socket");
    }
    int one = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    // if (bind(sock, ai->ai_addr, ai->ai_addrlen) < 0) {
    int port = atoi(argv[2]);
    struct sockaddr_in addr_con = {
        .sin_family = AF_INET,
        .sin_addr.s_addr =
            ((struct sockaddr_in*)addr->ai_addr)->sin_addr.s_addr,
        .sin_port = htons(port)};
    int con =
        connect(sock, (struct sockaddr*)&addr_con, sizeof(struct sockaddr_in));
    freeaddrinfo(addr);
    if (con < 0) {
        perror("Connect false");
        return 1;
    }
    int epollfd = epoll_create1(0);
    if (epollfd < 0) {
        perror("epoll");
        return 1;
    }

    struct epoll_event evt = {.events = EPOLLIN, .data.fd = sock};
    epoll_ctl(epollfd, EPOLL_CTL_ADD, sock, &evt);

    evt.events = EPOLLIN;
    evt.data.fd = STDIN_FILENO;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, STDIN_FILENO, &evt);

    while (1) {
        // int timeout = 10; // block indefinitly
        int timeout = -1; // block indefinitly
        errno = 0;
        if (epoll_wait(epollfd, &evt, 1, timeout) < 0) {
            if (errno == EINTR) {
                printf("errno\n");
                continue;
            }
            perror("wait error");
            return 1;
        }
        if (evt.data.fd == STDIN_FILENO) {
            // get stdin
            char buf[1024] = {0};
            int res = 0;
            if ((res = read(STDIN_FILENO, buf, sizeof(buf))) < 0) {
                perror("read err");
            }
            if (!res) {
                close(sock);
                printf("GoodBye\n");
                return 0;
            }
            write(sock, buf, res);
            memset(buf, 0, sizeof(buf));
        } else if (evt.data.fd == sock) {
            char buf[1024] = {0};
            int res = 0;
            if ((res = read(sock, buf, sizeof(buf))) < 0) {
                perror("error read from sock");
            }
            write(STDOUT_FILENO, buf, res);
        } else {
            printf("sock fd = %d\n", evt.data.fd);
            perror("something strange");
        }
    }

    return 0;
}
