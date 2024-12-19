#include "server.h"

int server_create_listner(char* service) {
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

int server_threat_sock(int num) {
    // after accept;
    // printf("threat_sock %d\n", num);
    // for(int i = 0; i < 1000000; ++i) {
    //    __asm("nop");
    //}
    // return 0;

    int epfd = epoll_create1(EPOLL_CLOEXEC);
    if (epfd < 0) {
        perror("epoll\n");
        return -1;
    }
#ifdef SERVERNONBLOCK
    struct epoll_event evt = {.events = EPOLLIN | EPOLLOUT | EPOLLET,
                              .data.fd = 0};
    epoll_ctl(epfd, EPOLL_CTL_ADD, num, &evt);
    char buf[4096] = {0};
    epoll_wait(epfd, &evt, 1, -1);
    if (evt.data.fd == STDIN_FILENO) {
        int res = 0;
        while ((res = read(num, buf, sizeof(buf))) >= 0) {
            if (errno == EAGAIN) {
                perror("readall");
            }
            if (errno == EINTR) {
                perror("EINTR");
                continue;
            }
            if (!res) {
                printf("Disconnect %d\n", num);
                break;
            } else {
                // int res = parse(buf);
                // printf("buf = %s", buf);
                char head[4096] = {0};
                // char data[4096*16] = {0};
                char* data = NULL;
                size_t size = 0;
                http_parse(buf, head, &data, &size);
                write(num, head, strlen(head)); // echo make nonblock
                write(num, data, size);         // echo make nonblock
                // TODO: check if need to close connection
                break;
            }
        }
    }
    if (evt.data.fd == STDOUT_FILENO) {
        printf("EPOLL STD_OUT \n");
    }
#else
    char buf[4096 * 16] = {0};
    //struct epoll_event evt = {.events = EPOLLIN, .data.fd = 0};
    //epoll_ctl(epfd, EPOLL_CTL_ADD, num, &evt);
    //epoll_wait(epfd, &evt, 1, -1);
    //while (1) {
    //    if (evt.data.fd == STDIN_FILENO) {
    //        int res = 0;
    //        if ((res = read(num, buf, sizeof(buf))) < 0) {
    //            perror("read");
    //        }
    //        if (!res) {
    //            break;
    //        } else {
    //            // int res = parse(buf);
    //            // printf("buf = %s", buf);
    //            char head[4096 * 16] = {0};
    //            // char data[4096*16] = {0};
    //            char* data = NULL;
    //            size_t size = 0;
    //            http_parse(buf, head, &data, &size);
    //            write(num, head, strlen(head)); // echo make nonblock
    //            write(num, data, size);         // echo make nonblock
    //            // TODO: check if need to close connection
    //            break;
    //        }
    //    }
    //}
    int res;
    if ((res = read(num, buf, sizeof(buf))) < 0) {
        perror("read");
        close(num);
        return 1;
    }
    if (!res) {
        close(num);
    } else {
        // int res = parse(buf);
        // printf("buf = %s", buf);
        char head[4096 * 16] = {0};
        // char data[4096*16] = {0};
        char* data = NULL;
        size_t size = 0;
        http_parse(buf, head, &data, &size);
        write(num, head, strlen(head)); // echo make nonblock
        write(num, data, size);         // echo make nonblock
        // TODO: check if need to close connection
        close(num);
    }
#endif

    //close(num);
    //close(epfd);
    return 0;
}

void threat_stdStream(int num) { printf("threat_stream %d\n", num); }
