#include "read_daemon.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHMEM_SIZE 4096

int main() {
    // start free, read stdout check awk free mem, increase mem
    int shm_id;
    char* shm_buf;
    shm_id = shmget(0x123456, 4096, 0);
    shm_buf = (char*)shmat(shm_id, 0, 0);
    while (1) {

        if (shm_buf == (char*)-1) {
            fprintf(stderr, "shmat() error\n");
            return 1;
        }
        printf("Message: \n%s\n", shm_buf);
        //shmdt(shm_buf);
        sleep(1);
    }

    return 0;
}
