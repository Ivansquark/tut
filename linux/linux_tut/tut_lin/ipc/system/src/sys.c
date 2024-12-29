#include "sys.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

char buf[4096] = {0};

int main(int argc, char** argv) {
    int fd = 0;
    fd = mkfifo("fifo", 0644);
    if (fd < 0) {
        perror("cant create fifo");
        return -1;
    }

    system("ls -la > fifo &");
    //system("bash -c ls > fifo &");
    //system("ls | tee fifo &");

    //sleep(1);
    //usleep(1);
    printf("wait\n");
    fd = open("fifo", O_RDWR, 0644);

    int sz = 0;
    if ((sz = read(fd, buf, sizeof(buf))) < 0) {
        perror("cant open fifo");
        return -1;
    }
    close(fd);

    printf("buf = \n%s\n", buf);

    unlink("fifo");

    return 0;
}
