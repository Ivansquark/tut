#include "shamem1.h"

#include <stdio.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/file.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <unistd.h>
#include <wait.h>

char arr[1024] = {0};

int main() {
#if (READ_METHOD == PIPE)
    char* cmd = "ipcs -m";
    int ch;
    FILE* fd;
    fd = popen(cmd, "r");
    // read from the process and print.
    int count = 0;
    while ((ch = fgetc(fd)) != EOF) {
        arr[count++] = ch;
    }
    arr[count] = 0;
    pclose(fd);
    printf("%s\n", arr);
#else if (READ_METHOD == MMAP)
    pid_t id = 0;
    pid_t childpid = 0;
    int fd = open("file.txt", O_RDWR | O_CREAT, 0644);
    id = fork();
    char* data = "opa";
    if (id == -1) {
        fprintf(stderr, "error: fork()");
        return 1;
    }
    if (!id) {
        childpid = getpid();
        fprintf(stdout, "-------------- Child ---------------\n");
        fflush(stdout);
        dup2(fd, 1); // make stdout go to file
        execlp("ipcs", "ipcs", "-m", NULL);
        // fflush(stdout);
        fprintf(stderr, "child_end\n");
    }
    waitpid(childpid, NULL, 0);

    data = mmap(NULL, 1024, PROT_READ, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED) {
        perror("mmap failed");
        return 2;
    }
    close(fd);
    unlink("file.txt");

    fprintf(stdout, "------------- Parent ------------------\n");
    fflush(stdout);
    printf("%s\n", data);
    memcpy(arr, data, 1024);
    munmap(data, 1024);
#endif

    //---------------- parse key ----------------------------------------------
    // find key
    char* start = 0;
    start = strtok(arr, "\n");
    printf("%s\n", start);
    start = strtok(NULL, "\n");
    printf("%s\n", start);
    start = strtok(NULL, " ");
    printf("%s\n", start);
    // parse key
    unsigned key = strtol(start, NULL, 16);
    printf("Key = %d\n", key);
    start = strtok(NULL, " ");
    start = strtok(NULL, " ");
    start = strtok(NULL, " ");
    start = strtok(NULL, " ");
    // parse size
    printf("%s\n", start);
    unsigned size = (int)strtol(start, NULL, 10);
    printf("Size = %d\n", size);

    int shm_id;
    char* shm_buf;
    shm_id = shmget(key, size, 0);
    shm_buf = (char*)shmat(shm_id, 0, 0);

    if (shm_buf == (char*)-1) {
        fprintf(stderr, "shmat() error\n");
        return 1;
    }
    shm_buf[0] = 'F';
    shm_buf[4096] = 'F';
    printf("Message: %s\n", shm_buf);
    shmdt(shm_buf);

    return 0;
}
