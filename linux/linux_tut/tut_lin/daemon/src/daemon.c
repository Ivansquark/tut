#include "daemon.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHMEM_SIZE 4096

int main() {
    // start free, read stdout check awk free mem, increase mem
    int fd = 0;
    int shm_id = 0;
    shm_id = shmget(0x123456, SHMEM_SIZE, IPC_RMID | 0600);
    shmctl(shm_id, IPC_RMID, NULL);
    // proc daemon (date to shamem)
    if (!(fd = fork())) {
        int fd_fifo = 0;
        int shm_id = 0;
        char* shm_buf;
        size_t shm_size;
        struct shmid_ds ds;
        char buf[4096] = {0};

        shm_id = shmget(0x123456, SHMEM_SIZE, IPC_CREAT | IPC_EXCL | 0600);

        if (shm_id == -1) {
            fprintf(stderr, "shmget() error \n");
            return 1;
        }

        shm_buf = (char*)shmat(shm_id, NULL, 0);
        if (shm_buf == (char*)-1) {
            fprintf(stderr, "error: shmat()\n");
            return 1;
        }

        shmctl(shm_id, IPC_STAT, &ds);

        shm_size = ds.shm_segsz;
        
        int f = 0;
        while (1) {
            fd_fifo = mkfifo("fif", 0644);
            f = open("fif", O_RDWR, 0644);
            if(f < 0) {
                perror("cant open file\n");
                return 1;
            }
            system("date > fif &");
            if(read(f, buf, sizeof(buf)) < 0) {
                perror("cant read fifo\n");
                return 1;
            }
            close(fd_fifo);
            sleep(1);
            unlink("fif");
            strcpy(shm_buf, buf);
            //printf("%s\n", buf);
            memset(buf, 0, sizeof(buf));
            sleep(1);
        }
        //TODO: threat signal to close shared mem
    }
    // parent must kill to make daemon
    printf("Parent id = %d \n", getpid());
    printf("Child free id = %d \n", fd);

    return 0;
}
