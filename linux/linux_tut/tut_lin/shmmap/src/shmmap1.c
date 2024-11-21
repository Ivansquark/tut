#include "shmmap1.h"

#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/file.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <unistd.h>
#include <wait.h>

#define LOCK_FILE "/lock"
#define SNAME "/mysem"

char arr[1024] = {0};

int main() {
    // char semaphoreName[] = "/sem";
    // sem_t* sem = sem_open(SEM_NAME, 0); /* Open a preexisting semaphore. */

    sleep(1);
    int shm_fd;
    char* shm_buf;

    shm_fd = shm_open("/myshm", O_RDWR, 0666);
    ftruncate(shm_fd, 65536);

    shm_buf = mmap(NULL, 65536, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    int count = 0;
    char buf[256] = {0};

    // int fd_lock = open(LOCK_FILE, O_RDWR);
    close(shm_fd);
    int fd = shm_open(SNAME, O_RDWR, 0666);
    if (!fd) {
        perror("NO SEM\n");
        return 1;
    }
    ftruncate(fd, sizeof(sem_t));
    sem_t* sem =
        mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    sem_init(sem, 1, 1);
    while (1) {
        sem_wait(sem);
        // flock(fd_lock, LOCK_EX);
        memcpy(buf, shm_buf, 256);
        printf("recv \n %s\n", buf);
        sem_post(sem);
        // flock(fd_lock, LOCK_UN);
        usleep(500000);
    }

    shmdt(shm_buf);
    shmctl(shm_fd, IPC_RMID, NULL);

    return 0;
}
