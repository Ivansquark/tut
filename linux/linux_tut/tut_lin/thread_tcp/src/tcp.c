#include "tcp.h"

#include <arpa/inet.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

void* threat_function(void* args) {
    int fd_conn = *(int*)args;
    char buff[2000] = {0};
    while (1) {
        int size = recv(fd_conn, buff, sizeof(buff), 0);
        if (size > 0) {
            printf("recv: \n%s", buff);
            write(fd_conn, "OK!\n", 4);
            int ret = strcmp(buff, "exit\n");
            if (!ret) break;
        }
    }
    close(fd_conn);
    return 0;
}

char buf_w[2000] = {0};

void* tcp_client(void* args) {
    sleep(2);
    // connect to
    uint16_t port = *(uint16_t*)(args);
    fprintf(stdout, "port_w = %d\n", port);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in saddr_in;
    saddr_in.sin_family = AF_INET;
    saddr_in.sin_port = htons(port);
    uint32_t ip = 0;
    inet_pton(AF_INET, "192.168.1.200", &ip);
    printf("ip = %u\n", ip);
    saddr_in.sin_addr.s_addr = ip; // htonl(ip);
    // saddr_out.sin_addr.s_addr = inet_addr("192.168.1.200");
    //if (bind(sockfd, (struct sockaddr*)&saddr_in, sizeof(struct sockaddr_in)) <
    //    0) {
    //    perror("bind is false");
    //    close(sockfd);
    //    exit(3);
    //}
    int fd_conn = connect(sockfd, (struct sockaddr*)&saddr_in,
                          sizeof(struct sockaddr_in));
    if (!fd_conn) {
        perror("No connection\n");
        exit(EXIT_FAILURE);
    }
    while (1) {
        int sz = strlen(buf_w);
        if (sz) {
            write(fd_conn, buf_w, sz);
            memset(buf_w, 0, sizeof(buf_w));
        }
    }

    fprintf(stderr, "client_close\n");
    close(sockfd);
    return 0;
}

void* tcp_server(void* args) {
    // create server, bind, listen
    uint16_t port = *(uint16_t*)(args);
    fprintf(stdout, "port_w = %d\n", port);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in saddr_in;
    struct sockaddr saddr_connected;
    saddr_in.sin_family = AF_INET;
    saddr_in.sin_port = htons(80);
    uint32_t ip = 0;
    inet_pton(AF_INET, "192.168.1.200", &ip);
    printf("ip = %u\n", ip);
    saddr_in.sin_addr.s_addr = ip; // htonl(ip);
    // saddr_out.sin_addr.s_addr = inet_addr("192.168.1.200");
    if (bind(sockfd, (struct sockaddr*)&saddr_in, sizeof(struct sockaddr_in)) <
        0) {
        perror("bind is false");
        close(sockfd);
        exit(3);
    }
    if (listen(sockfd, 1) < 0) {
        perror("Not listened\n");
        exit(EXIT_FAILURE);
    }
    socklen_t saddr_connected_len = sizeof(saddr_in);
    while (1) {
        int sock_conn = accept(sockfd, &saddr_connected, &saddr_connected_len);
        if (sock_conn < 0) {
            perror("Not accepted");
            exit(EXIT_FAILURE);
        } else if (sock_conn > 0) {
            // new pthread function to threat connection
            pthread_t t_conn = 0;
            pthread_create(&t_conn, NULL, threat_function, &sock_conn);
        } else {
            // STDIN_FILENO - never be it
        }
    }
    close(sockfd);
    fprintf(stderr, "server_closed\n");
    return 0;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        perror("Low args");
        return 1;
    }
    pthread_t tcp_c;
    pthread_t tcp_s;
    uint16_t port_read = atoi(argv[1]);
    uint16_t port_write = atoi(argv[2]);
    pthread_create(&tcp_c, NULL, tcp_client, &port_read);
    pthread_create(&tcp_s, NULL, tcp_server, &port_write);

    char buffer[255];
    int sz = 0;
    while (1) {
        if ((sz = read(STDIN_FILENO, buffer, 255)) > 0) {
            memcpy(buf_w, buffer, sz);
            printf("buf_w = %s\n", buf_w);
            if (!strcmp(buf_w, "exit\n")) {
                break;
            }
        }
        sz = 0;
    }
    pthread_join(tcp_s, NULL);
}
