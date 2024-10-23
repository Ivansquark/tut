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
    void send(const std::string &str);
    uint16_t read();
    int sockfd=0;
    char buff[256];
private:
    void init();
    struct sockaddr* saddr;
    struct sockaddr_in* saddr_in;
    socklen_t sock_len;
};

#endif //UDP_H
