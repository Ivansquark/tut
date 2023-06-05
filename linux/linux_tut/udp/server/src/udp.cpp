#include "udp.h"
#include <iostream>

Udp::Udp() {
    init();
}
Udp::~Udp(){
    delete saddr;
}

int Udp::send(const std::string& str) {
    //std::cout<<"str= "<<str<<"str lengt = "<<str.length()<<std::endl;
    return sendto(sockfd, (const char*)str.data(), str.length(), 0, (sockaddr*)saddr_in, sizeof(sockaddr));
}

void Udp::read() {
    recvfrom(sockfd, &buff[0], sizeof(buff), 0, (sockaddr*)saddr_in, &sock_len);
    for(int i = 0; i<10; i++) {
        std::cout << buff[i] << " ";
    }
}

void Udp::init() {
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    saddr_in = new struct sockaddr_in;
    std::cout<<" saddr_in "<<saddr_in << " sockfd="<<sockfd<<std::endl;
    saddr_in->sin_addr.s_addr = inet_addr("192.168.0.106");
    //saddr_in->sin_addr.s_addr = inet_addr("192.168.0.106");
    saddr_in->sin_family = AF_INET;
    saddr_in->sin_port = htons(55555);
    sock_len = sizeof(sockaddr_in);
    std::cout<<"socklen="<<sock_len<<std::endl;
    sleep(3);
}
