#include "tcp.h"
#include <iostream>

Tcp::Tcp() {
    //init_server();
    init_client();
}
Tcp::~Tcp(){
    delete saddr_in;
}

int Tcp::sendToClient(int sock,const std::string& str) {
    return send(sock, (const char*)str.data(), str.length(), 0);
}

int Tcp::sendToServer(const std::string& str) {
    return send(sockfd, (const char*)str.data(), str.length(), 0);
}
int Tcp::readFromServer() {
    return recv(sockfd, buff, sizeof(buff), 0);
}
int Tcp::listenConnections() {
    return listen(sockfd, 1);
}
void Tcp::closeIT(){
    close(sockfd);
}
void Tcp::init_client() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    saddr_in = new struct sockaddr_in;
    std::cout << " saddr_in "<< saddr_in << " sockfd="<< sockfd << std::endl;
    saddr_in->sin_addr.s_addr = inet_addr("192.168.0.103");
    //saddr_in->sin_addr.s_addr = inet_addr("127.0.0.1");
    saddr_in->sin_family = AF_INET;
    saddr_in->sin_port = htons(80);
    sock_len = sizeof(sockaddr_in);
    std::cout<<"socklen="<<sock_len<<std::endl;
    int b = connect(sockfd, (const sockaddr*)saddr_in, sock_len);
    if(b == -1) {
        std::cout<< "Error connect" << std::endl;
    }
}

void Tcp::init_server() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    saddr_in = new struct sockaddr_in;
    std::cout << " saddr_in "<< saddr_in << " sockfd="<< sockfd << std::endl;
    saddr_in->sin_addr.s_addr = inet_addr("192.168.0.103");
    //saddr_in->sin_addr.s_addr = inet_addr("192.168.0.106");
    saddr_in->sin_family = AF_INET;
    saddr_in->sin_port = htons(55555);
    sock_len = sizeof(sockaddr_in);
    std::cout<<"socklen="<<sock_len<<std::endl;
    int b = bind(sockfd, (const sockaddr*)saddr_in, sock_len);
    if(b == -1) {
        std::cout<< "Error bind" << std::endl;
    }
    listenConnections();
    int connectedSockFD = 0;
    while(1) {
        connectedSockFD = accept(sockfd, (sockaddr*)saddr_connected, &sock_len);
        if(connectedSockFD !=0 && connectedSockFD != -1) break;
    }
    std::cout << "Connected IP:" << saddr_connected->sin_addr.s_addr << "\n";
    char buff[1540] = {0};
    while(1) {
        int size = recv(connectedSockFD, buff, sizeof(buff), 0);
        if(size) {
            for(auto& i : buff) {
                std::cout << i;
            }
            if(buff[0] == 'G') {
                sendToClient(connectedSockFD, "GET reply");
            }
            if(buff[0] == 'e' && buff[1] == 'x' && buff[2] == 'i' && buff[3] == 't') {
                close(connectedSockFD);
                _exit(0);
            }
        }        
    }
}
