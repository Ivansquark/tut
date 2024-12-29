#include "free.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    // start free, read stdout check awk free mem, increase mem
    int fd = 0;
    int pfd[2] = {0};
    while (1) {
        pipe(pfd);
        // free
        if (!(fd = fork())) {
            dup2(pfd[1], STDOUT_FILENO);
            close(pfd[1]);
            close(pfd[0]);
            execlp("free", "free", NULL);
            perror("free false");
            exit(1);
        }
        // parent
        printf("Parent id = %d \n", getpid());
        printf("Child free id = %d \n", fd);
        wait(NULL);
        char buf[4096] = {0};
        read(pfd[0], buf, sizeof(buf));
        // printf("str = \n%s \nopa\n", buf);
        close(pfd[0]);
        close(pfd[1]);

        char* arr = 0;
        arr = strtok(buf, "\n");
        // printf("arr = \n%s \narr\n", arr);
        arr = strtok(NULL, " ");
        // printf("arr = \n%s \narr\n", arr);
        arr = strtok(NULL, " ");
        // printf("arr = \n%s \narr\n", arr);
        arr = strtok(NULL, " ");
        // printf("arr = \n%s \narr\n", arr);
        long unsigned mem = atoi(arr);
        printf("\nUsed Mem = %lu\n", mem);
        memset(buf, 0, sizeof(buf));
        close(pfd[1]);
        close(pfd[0]);

        char mall[255] = {0};
        int mall_int = {0};
        int sz = 0;
        if ((sz = read(STDIN_FILENO, mall, sizeof(buf))) > 0) {
            mall_int = atoi(mall);
        }
        printf("mall_int = %d\n", mall_int);
        volatile int* pmall = NULL;
        pmall = (int*)malloc(mall_int * sizeof(int));
        for(volatile int i = 0; i < mall_int; ++i) {
            pmall[i] = i;
        }
        // break;
    }

    return 0;
}
