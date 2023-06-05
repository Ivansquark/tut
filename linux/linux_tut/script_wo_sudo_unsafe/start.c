#include <unistd.h>
#include <stdio.h>

int main() {
    setuid(0);
    //system("./script");
    pid_t num = fork();
    if(!num) {
        _exit(0);
    } else if(num != -1){
        execl("./script.sh", NULL);
    } else printf("ERROR");
    return 0;
}
