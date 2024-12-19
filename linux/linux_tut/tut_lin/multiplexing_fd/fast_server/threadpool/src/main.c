#include "http_parse.h"
#include "server.h"
#include "threadpool.h"

#include <sys/signal.h>

void sig_handler(int sig) {
    printf("Get signal SIGPIPE %d\n", sig);
}

int main(int argc, char** argv) {
    signal(SIGPIPE, SIG_IGN);
    //struct sigaction act;
    //sigset_t wait_set;
    //int sig;
    //sigemptyset(&wait_set);
    //act.sa_handler = &sig_handler;
    //act.sa_flags = SA_RESTART;
    ////sigaddset(&wait_set, SIGPIPE);
    ////sigprocmask(SIG_BLOCK, &wait_set, NULL);
    //if (sigaction(SIGPIPE, &act, NULL) == -1) {
    //    perror("sig failure");
    //    exit(EXIT_FAILURE);
    //}

    http_prepare_read_file_bufs();
    threadpool_create();
    // fptr f = {threat_sock, 5};
    // threadpool_add_task(&f);

    if (argc < 2) {
        fprintf(stderr, "USAGE %s SERVICE\n", argv[0]);
        return 1;
    }

    int sock = server_create_listner(argv[1]);
    if (sock < 0) {
        return 1;
    }
    while (1) {
#ifdef SERVERNONBLOCK
        int connection = accept4(sock, NULL, NULL, SOCK_NONBLOCK);
#else
        int connection = accept(sock, NULL, NULL);
#endif
        // extern pthread_mutex_t mutex;
        // pthread_mutex_lock(&mutex);
        // printf("Connection %d\n", connection);
        if (connection < 0) {
            perror("accept error");
            return 2;
        }
        fptr f = {server_threat_sock, connection};
        // pthread_mutex_unlock(&mutex);
        //  static int count = 0;
        //  fptr f = {server_threat_sock, count++};
        //  usleep(1);

        threadpool_add_task(&f);
    }

    return 0;
}
