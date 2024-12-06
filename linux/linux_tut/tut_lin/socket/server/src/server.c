#include "server.h"

#ifndef __USE_XOPEN2K
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

int create_listner(char* service, char* p) {
    struct addrinfo* res = NULL;
    int gai_err;
    struct addrinfo hint = {
        .ai_family = AF_UNSPEC, // ip4 and ip6
        .ai_socktype = SOCK_STREAM,
        .ai_flags = AI_PASSIVE,
    };
    if ((gai_err = getaddrinfo(service, p, &hint, &res))) {
        fprintf(stderr, "gai_err %s\n", gai_strerror(gai_err));
        return -1;
    }
    int sock = -1;
    // get all addresses
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
    freeaddrinfo(res);
    // sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        goto err;
    }
    int one = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));

    unsigned int ip;
    inet_pton(AF_INET, "127.0.0.1", &ip);
    unsigned short port = htons(55555);
    struct sockaddr_in addr = {
        .sin_family = AF_INET, .sin_addr.s_addr = ip, .sin_port = port};

    if (bind(sock, (struct sockaddr*)&addr, sizeof(struct sockaddr_in)) < 0) {
        perror("bind");
        goto err;
    }

    if (listen(sock, SOMAXCONN) < 0) {
        perror("listen");
        goto err;
    }

    printf("create_listner\n");
    return sock;
err:
    close(sock);
    return -1;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        fprintf(stderr, "USAGE %s SERVICE\n", argv[0]);
        return 1;
    }
    int sock = create_listner(argv[1], argv[2]);
    if (sock < 0) {
        return 1;
    }
    char buf[1024] = {0};
    while (1) {
        int connection = accept(sock, NULL, NULL);
        if (connection < 0) {
            perror("connection");
        }
        // TODO: forks
        while (1) {
            printf("connection num = %d\n", connection);
            int res = 0;
            if ((res = read(connection, buf, sizeof(buf))) < 0) {
                perror("read");
                continue;
            }
            printf("readed:\n%s\n", buf);
            write(connection, buf, res);
        }
    }

    return 0;
}
