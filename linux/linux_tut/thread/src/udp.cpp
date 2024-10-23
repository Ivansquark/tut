#include "udp.h"
#include <iostream>

Udp::Udp() {
    init();
}
Udp::~Udp(){
    delete saddr;
}

void Udp::send(const std::string& str) {
    sendto(sockfd, (const char*)str.data(), str.length(), 0, (sockaddr*)&saddr_in, sizeof(*saddr_in));
}

void Udp::read() {
    recvfrom(sockfd, &buff[0], sizeof(buff), 0, (sockaddr*)&saddr_in, &sock_len);
    for(int i = 0; i<10; i++) {
        std::cout << buff[i] << " ";
    }
}

void Udp::init() {
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    saddr = new struct sockaddr;
    saddr_in = new struct sockaddr_in;
    saddr_in->sin_addr.s_addr = inet_addr("127.0.0.1");
    saddr_in->sin_family = AF_INET;
    saddr_in->sin_port = htons(55555);
    sock_len = sizeof(sockaddr_in);
}
