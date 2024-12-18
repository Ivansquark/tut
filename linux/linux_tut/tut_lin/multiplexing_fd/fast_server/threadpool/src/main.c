#include "server.h"
#include "threadpool.h"


int main(int argc, char** argv) {
    threadpool_create();
    // fptr f = {threat_sock, 5};
    // threadpool_add_task(&f);

    //if (argc < 2) {
    //    fprintf(stderr, "USAGE %s SERVICE\n", argv[0]);
    //    return 1;
    //}

    //int sock = create_listner(argv[1]);
    //if (sock < 0) {
    //    return 1;
    //}
    while (1) {

        //int connection = accept(sock, NULL, NULL);
        //printf("Connection %d\n", connection);
        //if (connection < 0) {
        //    perror("accept error");
        //    return 2;
        //}
        //fptr f = {server_threat_sock, connection};
        
        static int count = 0;
        fptr f = {server_threat_sock, count++};
        usleep(1);

        threadpool_add_task(&f);
    }

    return 0;
}
