#include "server.h"

#ifndef __USE_POSIX
    #define __USE_POSIX
    #define __USE_XOPEN_EXTENDED
    #define __USE_XOPEN2K
#endif

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void grimReaper([[maybe_unused]] int sig) {
    printf("%s%d\n", "delete zombie - ", sig);
    int savedErrno = 0;
    savedErrno = errno;
    int status = 0;
    int pid = 0;
    sleep(5);
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        printf("SIGCHILD pid = %d, exit status = %x\n", pid, status);
        continue;
    }
    errno = savedErrno;
}

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
        .sin_family = AF_INET, .sin_addr.s_addr = INADDR_ANY, .sin_port = port};
    //.sin_family = AF_INET, .sin_addr.s_addr = ip, .sin_port = port};

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

    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = grimReaper;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sig child");
        exit(EXIT_FAILURE);
    }

    int sock = create_listner(argv[1], argv[2]);
    if (sock < 0) {
        return 1;
    }
    char buf[1024] = {0};
    while (1) {
        // block
        int connection = accept(sock, NULL, NULL);
        if (connection < 0) {
            perror("connection");
            continue;
        }
        printf("connection num = %d\n", connection);
        pid_t pid = 0;
        if (!(pid = fork())) {
            // child
            close(sock); // no need listen socket
            while (1) {
                int res = 0;
                if ((res = read(connection, buf, sizeof(buf))) < 0) {
                    perror("read");
                    return 1;
                    continue;
                }
                if (!res) {
                    // received EOF when connection closed on client side
                    close(connection);
                    return 0;
                }
                printf("readed on connection %d:\n%s\n", connection, buf);
                write(connection, buf, res);
                memset(buf, 0, sizeof(buf));
                if (!connection) {
                    return 1;
                }
            }
        }
        printf("pid = %d\n", pid);
        close(connection);
    }

    return 0;
}
