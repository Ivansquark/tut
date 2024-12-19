#ifndef SERVER_H
#define SERVER_H

#include "http_parse.h"

#ifndef __USE_GNU
    #define __USE_GNU
    #define _GNU_SOURCE /* See feature_test_macros(7) */
#endif

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <threadpool.h>
#include <unistd.h>

//#define SERVERNONBLOCK

int server_create_listner(char* service);
int server_threat_sock(int num);

#endif //SERVER_H
