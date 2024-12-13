#include "daemon_server.h"

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <syslog.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        perror("Low args\n");
        return 1;
    }
    pid_t id = 0;
    if ((id = fork())) {
        // parent
        printf("Parent id = %d child ip = %d\n", getpid(), id);
        return 0;
    }
    printf("Child id = %d \n", getpid());
    // child
    // create server
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Sock err\n");
    }
    int port = atoi(argv[1]);
    unsigned int ip = 0;
    struct sockaddr_in addr = {.sin_family = AF_INET,
                               .sin_addr.s_addr = INADDR_ANY,
                               //.sin_addr.s_addr =
                               //    inet_pton(AF_INET, "127.0.0.1", &ip),
                               .sin_port = htons(port)};

    if ((bind(sock, (struct sockaddr*)&addr, sizeof(struct sockaddr_in))) < 0) {
        perror("bind false\n");
        return 1;
    }

    // create daemon
    // block pid file
    int pid = open(argv[2], O_CREAT | O_WRONLY, 0600);
    if (pid < 0) {
        perror("Open failed\n");
        return 1;
    }
    int flock_res = flock(pid, LOCK_EX | LOCK_NB);
    if (flock_res < 0) {
        perror("flock\n");
        return 1;
    }
    close(0);
    close(1);
    close(2);

    // setsid to
    const char* daemon_name = "daemon_server";
    openlog(daemon_name, LOG_PID, LOG_DAEMON);
    syslog(LOG_INFO, "Hello echo server started");
    // block here
    if ((listen(sock, SOMAXCONN)) < 0) {
        perror("listen false\n");
    }

    pid_t my_pid = setsid(); // set session id leader
    if (my_pid < 0) {
        syslog(LOG_ERR, "cant setsid %s\n", strerror(errno));
        return 1;
    }
    FILE* pidFile = fdopen(pid, "w");
    if (!pidFile) {
        syslog(LOG_ERR, "cant open file %s\n", strerror(errno));
        return 1;
    }
    if (fprintf(pidFile, "%d", getpid()) < 0) {
        syslog(LOG_ERR, "cant write file %s\n", strerror(errno));
        return 1;
    }
    char buf[1024] = {0};
    while (1) {
        int conn = accept(sock, NULL, NULL);
        if (conn < 0) {
            syslog(LOG_ERR, "bad accept %s\n", strerror(errno));
        }
        if (!fork()) {
            while (1) {
                int res = 0;
                if ((res = read(conn, buf, sizeof(buf))) < 0) {
                    syslog(LOG_ERR, "read false");
                    return 1;
                }
                if (!res) {
                    close(conn);
                    return 0;
                }
                write(conn, buf, res);
                memset(buf, 0, sizeof(buf));
            }
        }
        close(conn);
        // TODO wait pid all to reduce zombies
    }

    return 0;
}
