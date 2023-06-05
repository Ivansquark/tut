#include <sys/types.h>
#include <unistd.h>
#include <cstdio>
#include <stdlib.h>
#include <pwd.h>
#include <stdint.h>

extern char** environ;
int main( int argc, char** argv) {
    while(1);
    uint16_t InitPid = getpid();
    int uid = getuid();
    printf("UID=%d", uid);
    pid_t result = fork();
    if(result == -1) {
        write(2, "Error\n", 7); return 1;
    }
    if(result == 0) {
        printf("I am child process PID=%d, PPID=%d\n", getpid(), getppid());
        char* argv[] = {"ps", "-f", NULL}; 
        execve("/bin/ps", argv, environ);
    }
    else printf("I am parent, result=%d, PID=%d, PPID=%d\n", result, getpid(), getppid());
    sleep(10);
    return 0;
}
