#include "udp.h"
#include <iostream>

Udp::Udp() {
    init();
}
Udp::~Udp(){
    delete saddr;
}

void Udp::send(const std::string& str) {
    sendto(sockfd, (const char*)str.data(), str.length(), 0, (sockaddr*)saddr_in, sizeof(*saddr_in));
}

uint16_t Udp::read() {
    //return recvfrom(sockfd, buff, sizeof(buff), 0, (sockaddr*)saddr_in, &sock_len);
    return recvfrom(sockfd, buff, sizeof(buff), 0, NULL, NULL);
}

void Udp::init() {
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    saddr = new struct sockaddr;
    saddr_in = new struct sockaddr_in;
    //saddr_in->sin_addr.s_addr = inet_addr("192.168.0.106");
    saddr_in->sin_addr.s_addr = inet_addr("127.0.0.1");
    saddr_in->sin_family = AF_INET;
    saddr_in->sin_port = htons(55555);
    sock_len = sizeof(sockaddr_in);
    if(bind(sockfd, (struct sockaddr *)saddr_in, sizeof(*saddr_in)) < 0) {
        perror("bind");
        exit(2);
    }
    //bind(sockfd,saadr_in,sock_len);
}
