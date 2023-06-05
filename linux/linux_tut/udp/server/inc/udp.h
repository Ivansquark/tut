#ifndef UDP_H
#define UDP_H

#include "sys/types.h"
#include "sys/socket.h"
#include "arpa/inet.h"
#include <unistd.h>
#include <string>

class Udp {
public:
    Udp();
    ~Udp();
    int send(const std::string &str);
    void read();
    int sockfd=0;

private:
    void init();
    struct sockaddr* saddr;
    struct sockaddr_in* saddr_in;
    char buff[256];
    socklen_t sock_len;
};

#endif //UDP_H
