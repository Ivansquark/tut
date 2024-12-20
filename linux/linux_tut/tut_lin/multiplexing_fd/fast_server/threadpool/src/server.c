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
    //printf("threat_sock %d\tid = %d\n", num, gettid());
    // for (volatile int i = 0; i < 90000000; ++i) {
    //     __asm("nop");
    // }
    //  return 0;

    int epfd = epoll_create1(EPOLL_CLOEXEC);
    if (epfd < 0) {
        perror("epoll\n");
        return -1;
    }
#ifdef SERVERNONBLOCK
    // struct epoll_event evt = {.events = EPOLLIN | EPOLLOUT | EPOLLET,
    //                           .data.fd = 0};
    struct epoll_event evt = {.events = EPOLLIN | EPOLLET, .data.fd = 0};
    epoll_ctl(epfd, EPOLL_CTL_ADD, num, &evt);
    char buf[4096 * 16] = {0};
    epoll_wait(epfd, &evt, 2, -1);
    if (evt.data.fd == STDIN_FILENO) {
        int res = 0;
        do {
            res = read(num, buf, sizeof(buf));
            // if (res == -1) {
            //     if (errno == EAGAIN) {
            //         perror("EAGAIN");
            //         continue;
            //     }
            // }
        } while (res == -1 && errno == EINTR);

        if (!res) {
            // printf("Disconnect %d\n", num);
        } else {
            // int res = parse(buf);
            // printf("buf = %s", buf);
            char head[4096] = {0};
            // char data[4096*16] = {0};
            char* data = NULL;
            size_t size = 0;
            http_parse(buf, head, &data, &size);
            // write(num, head, strlen(head));
            // write(num, data, size);
            size_t len = strlen(head);
            size_t sent = 0;
            //TODO: check what wrong (broken pipe cause client FIN very fast)
            //
            //
            //char arr[4096*16] = {0};
            //memcpy(arr, head, len);
            //memcpy(arr + len, data, size);
            //len = len + size;
            //send(num, arr, len, MSG_NOSIGNAL);
            
            //while (sent < len) {
            //    ssize_t n = 0;
            //    if ((n = send(num, arr + sent, len - sent,
            //                  MSG_NOSIGNAL)) == -1) {
            //        if (errno == EAGAIN || errno == EWOULDBLOCK) continue;
            //        perror("send failed head");
            //        exit(1);
            //    }
            //    sent += n;
            //}

            //while (sent < len) {
            //    ssize_t n = 0;
            //    if ((n = send(num, head + sent, len - sent,
            //                  MSG_NOSIGNAL)) == -1) {
            //        if (errno == EAGAIN || errno == EWOULDBLOCK) continue;
            //        perror("send failed head");
            //        exit(1);
            //    }
            //    sent += n;
            //}
            //sent = 0;
            //len = size;
            //while (sent < len) {
            //    ssize_t n = 0;;
            //    if ((n = send(num, data + sent, len - sent, MSG_NOSIGNAL)) == -1) {
            //        if (errno == EAGAIN || errno == EWOULDBLOCK) continue;
            //        perror("send failed data");
            //        //exit(1);
            //    }
            //    sent += n;
            //    printf("n - %lu\n", sent);
            //}

            send(num, head, strlen(head), MSG_NOSIGNAL);
            send(num, data, size, MSG_NOSIGNAL);
            //  usleep(1000000);
            //   TODO: check if need to close connection
        }
    }
    // if (evt.data.fd == STDOUT_FILENO) {
    //     // here send data
    //     printf("EPOLL STD_OUT \n");
    // }
#else
    char buf[4096 * 16] = {0};
    struct epoll_event evt = {.events = EPOLLIN, .data.fd = 0};
    epoll_ctl(epfd, EPOLL_CTL_ADD, num, &evt);
    epoll_wait(epfd, &evt, 1, -1);
    while (1) {
        if (evt.data.fd == STDIN_FILENO) {
            int res = 0;
            if ((res = read(num, buf, sizeof(buf))) < 0) {
                perror("read");
                break;
            }
            if (!res) {
                break;
            } else {
                // int res = parse(buf);
                // printf("buf = %s", buf);
                char head[4096 * 16] = {0};
                // char data[4096*16] = {0};
                char* data = NULL;
                size_t size = 0;
                http_parse(buf, head, &data, &size);
                // write(num, head, strlen(head)); // echo make nonblock
                // write(num, data, size);         // echo make nonblock
                send(num, head, strlen(head),
                     MSG_NOSIGNAL);                  // echo make nonblock
                send(num, data, size, MSG_NOSIGNAL); // echo make nonblock
                // TODO: check if need to close connection
                break;
            }
        }
    }
#endif

    close(epfd);
    return 0;
}

void threat_stdStream(int num) { printf("threat_stream %d\n", num); }
