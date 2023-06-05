#ifndef TCP_H
#define TCP_H

#include "sys/types.h"
#include "sys/socket.h"
#include "arpa/inet.h"
#include <unistd.h>
#include <string>

class Tcp {
public:
    Tcp();
    ~Tcp();
    int sendToClient(int sock, const std::string &str);
    int sendToServer(const std::string& str);
    int readFromServer();
    int sockfd=0;
    int listenConnections();
    char buff[2000];
    void closeIT();
private:
    void init_server();
    void init_client();
    struct sockaddr* saddr;
    struct sockaddr_in* saddr_in;
    struct sockaddr_in* saddr_connected;
    socklen_t sock_len;
};

#endif //TCP_H
