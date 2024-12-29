#include "shmmap.h"

#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/file.h>
#include <sys/mman.h>
#include <sys/shm.h>

#define SHMEM_SIZE 4096
#define SH_MESSAGE "Hello World!\n"

#define LOCK_FILE "/lock"
#define SNAME "/mysem"

int main() {
    //sem_t* sem = sem_open(SNAME, O_CREAT, 0644, 3); /* Initial value is 3. */
    int shm_fd;
    char* shm_buf;

    shm_fd = shm_open("/myshm", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, 65536);

    shm_buf = mmap(NULL, 65536, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    int count = 0;
    char buf[256] = {0};

    // int fd_lock = open(LOCK_FILE, O_CREAT);
    //
    close(shm_fd);
    int fd = shm_open(SNAME, O_CREAT | O_RDWR, 0666);
    if(fd < 0) {
        perror("NO SEM");
        return 1;
    }


    ftruncate(fd, sizeof(sem_t));
    sem_t* sem =
        mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    sem_init(sem, 1, 1);

    while (1) {
        // flock(fd_lock, LOCK_EX);
        sem_wait(sem);
        printf("all good\n");
        sprintf(buf, "SHARED_MMAP NUM = %d\n", count++);
        memcpy(shm_buf, buf, 256);
        sem_post(sem); 
        sleep(1);
        // flock(fd_lock, LOCK_UN);
    }

    shmdt(shm_buf);
    shmctl(shm_fd, IPC_RMID, NULL);

    return 0;
}
