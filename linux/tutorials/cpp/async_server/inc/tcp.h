#ifndef TCP_H
#define TCP_H

#include "http_parser.h"
#include "https.h"
#include "pool.h"

#include "arpa/inet.h"
#include "sys/socket.h"
#include "sys/types.h"
#include <fstream>
#include <iostream>
#include <string.h>
#include <string>
#include <thread>
#include <unistd.h>
#include <vector>
class Tcp {
  public:
    ~Tcp();
    static Tcp *pThis;
    static Tcp *instance();
    int sendToClient(int sock, const std::string &str);
    void read();
    int sockfd = 0;
    int listenConnections();
    int connectedSockFD = 0;
    void init_server(bool isHTTPS);

  private:
    Tcp();
    Tcp(const Tcp &) = delete;
    Tcp &operator=(Tcp &) = delete;
    static void handleConnection(bool arg);
    static int clientSock;
    struct sockaddr *saddr;
    struct sockaddr_in *saddr_in;
    struct sockaddr_in *saddr_connected;

    char buff[256];
    socklen_t sock_len;
    const char *IP = "127.0.0.1";

    SSL_CTX *ctx;
    SSL *ssl;
    Pool pool;
};

#endif // TCP_H
