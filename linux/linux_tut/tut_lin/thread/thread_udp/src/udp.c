#include "udp.h"

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

char buf_w[2000] = {0};

void* udp_read(void* args) {
    char buf[2000] = {0};
    uint16_t port = *(uint16_t*)(args);
    fprintf(stdout, "port_r = %d\n", port);
    int sockfd_in = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in saddr_in;
    saddr_in.sin_family = AF_INET;
    saddr_in.sin_port = htons(port);
    saddr_in.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sockfd_in, (struct sockaddr*)&saddr_in, sizeof(saddr_in)) < 0) {
        perror("bind is false");
        close(sockfd_in);
        exit(3);
    }
    while (1) {
        // int size = read(sockfd_in, buf, sizeof(buf));
        int size = recvfrom(sockfd_in, buf, sizeof(buf), 0, NULL, NULL);
        if (!size) continue;
        printf("read - %s\n", buf);
        int res = strcmp(buf, "exit\n");
        if (!res) {
            break;
        }
    }
    fprintf(stderr, "read_close\n");
    close(sockfd_in);
    return 0;
}

void* udp_write(void* args) {
    uint16_t port = *(uint16_t*)(args);
    fprintf(stdout, "port_w = %d\n", port);
    int sockfd_out = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in saddr_out;
    saddr_out.sin_family = AF_INET;
    saddr_out.sin_port = htons(port);
    uint32_t ip = 0;
    inet_pton(AF_INET, "192.168.1.200", &ip);
    printf("ip = %u\n", ip);
    saddr_out.sin_addr.s_addr = ip; // htonl(ip);
    // saddr_out.sin_addr.s_addr = inet_addr("192.168.1.200");
    if (bind(sockfd_out, (struct sockaddr*)&saddr_out, sizeof(saddr_out)) < 0) {
        perror("bind is false");
        close(sockfd_out);
        exit(3);
    }
    while (1) {
        int sz = strlen(buf_w);
        if (!sz) continue;
        printf("write - %s", buf_w);
        struct sockaddr_in out;
        out.sin_port = htons(4000);
        uint32_t ip = 0;
        inet_pton(AF_INET, "192.168.1.200", &ip);
        printf("ip = %u\n", ip);
        out.sin_addr.s_addr = ip; // htonl(ip);
        int size =
            sendto(sockfd_out, buf_w, sz, 0, &out, sizeof(struct sockaddr));
        // int size = write(sockfd_out, buf_w, sz);
        if (!size) continue;
        // sleep(5);
        if (!strcmp(buf_w, "exit\n")) {
            break;
        }
        memset(buf_w, 0, sizeof(buf_w));
    }
    close(sockfd_out);
    fprintf(stderr, "write_close\n");
    return 0;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        perror("Low args");
        return 1;
    }
    pthread_t udp_r;
    pthread_t udp_w;
    uint16_t port_read = atoi(argv[1]);
    uint16_t port_write = atoi(argv[2]);
    pthread_create(&udp_r, NULL, udp_read, &port_read);
    pthread_create(&udp_w, NULL, udp_write, &port_write);

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
    pthread_join(udp_w, NULL);
}
