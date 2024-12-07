#include "client.h"

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

int get_addr(char* service) {
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
        // TODO: return address IP
    }
    freeaddrinfo(res);
    printf("create_listner\n");
    return sock;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "USAGE %s SERVICE\n", argv[0]);
        return 1;
    }
    int addr = get_addr(argv[1]);

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    int ip = 0;
    inet_pton(AF_INET, "127.0.0.1", &ip);

    struct sockaddr_in adr = {
        .sin_family = AF_INET, .sin_addr.s_addr = ip, .sin_port = htons(55555)};

    if(connect(sock, (struct sockaddr*)&adr, sizeof(struct sockaddr_in)) < 0) {
        perror("no connection");
        return 1;
    }
    char buf[256] = {0};
    write(sock, "opa\n", 4);
    read(sock, buf, sizeof(buf));
    printf("readed: \n%s", buf);
    return 1;
    while (1) {}

    return 0;
}
