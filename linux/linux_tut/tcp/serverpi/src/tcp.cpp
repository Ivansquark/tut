#include "tcp.h"
Tcp *Tcp::pThis = nullptr;
Tcp *Tcp::instance() {
    if (Tcp::pThis == nullptr) {
        Tcp::pThis = new Tcp();
    }
    return Tcp::pThis;
}

int Tcp::clientSock = 0;
Tcp::Tcp() {}
Tcp::~Tcp() {
    delete saddr_in;
    delete saddr_connected;
}

int Tcp::sendToClient(int sock, const std::string &str) {
    return send(sock, (const char *)str.data(), str.length(), 0);
}

void Tcp::read() {
    recvfrom(sockfd, &buff[0], sizeof(buff), 0, (sockaddr *)saddr_in, &sock_len);
    for (int i = 0; i < 10; i++) {
        std::cout << buff[i] << " ";
    }
}
int Tcp::listenConnections() { return listen(sockfd, 1); }
void Tcp::init_server() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    std::cout << "init_server " << std::endl;
    saddr_in = new struct sockaddr_in;
    saddr_connected = new struct sockaddr_in;
    std::cout << " saddr_in " << saddr_in << " sockfd=" << sockfd << std::endl;
    // saddr_in->sin_addr.s_addr = inet_addr("192.168.0.103");
    saddr_in->sin_addr.s_addr = inet_addr(IP);
    saddr_in->sin_family = AF_INET;
    saddr_in->sin_port = htons(80);
    sock_len = sizeof(sockaddr_in);
    std::cout << "socklen=" << sock_len << std::endl;
    int b = bind(sockfd, (const sockaddr *)saddr_in, sock_len);
    if (b == -1) {
        std::cout << "Error bind" << std::endl;
        perror("Eror In bind");
        _exit(0);
    }
    listenConnections();
    socklen_t saddr_connected_len = sizeof(saddr_connected);
    std::cout << "connectedSockFD = " << connectedSockFD << std::endl;
    std::cout << "Connected IP:" << saddr_connected->sin_addr.s_addr << "\n";
    std::vector<std::unique_ptr<std::thread>> threads;
    while (1) {
        if ((connectedSockFD = accept(sockfd, (sockaddr *)saddr_connected, &saddr_connected_len)) < 0) {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        if (connectedSockFD > 0) {
            // std::thread newConnection(Tcp::handleConnection, nullptr);
            // newConnection.join();
            threads.emplace_back(new std::thread(Tcp::handleConnection, nullptr));
            // TODO: check for memory leakage
        }
    }
}

void Tcp::handleConnection(void *arg) {
    system("clear");
    std::cout << "new c++ thread ID: " << std::this_thread::get_id() << std::endl;
    std::cout << "connectedSockFDnew = " << Tcp::instance()->connectedSockFD << std::endl;
    char buff[1540];
    memset(buff, 0, 1540);
    int sockfd = 0;
    std::string str;
    // int connectedSockFD = 0;
    while (1) {
        // int client_sock = *(int *)arg;
        int size = recv(Tcp::instance()->connectedSockFD, buff, sizeof(buff), 0);
        if (size > 0) {
            std::cout << "size=" << size << std::endl;
            for (int i = 0; i < size; i++) {
                std::cout << buff[i];
            }
            std::cout << std::endl;
            // parse first GET request
            if (buff[0] == 'G' && buff[1] == 'E' && buff[2] == 'T' && buff[3] == ' ' && buff[4] == '/' &&
                buff[5] == ' ') {
                std::string sendStr;
                std::ifstream file;
                file.open("head.c");
                if (!file.is_open()) {
                    std::cout << "\n Cant open file";
                } else {
                    str.clear();
                    while (std::getline(file, str)) {
                        sendStr += str + "\n";
                    }
                    file.close();
                }
                file.open("index.html");
                if (!file.is_open()) {
                    std::cout << "\n Cant open file";
                } else {
                    std::cout << "Reply html" << std::endl;
                    str.clear();
                    sendStr += "\n";
                    while (std::getline(file, str)) {
                        sendStr += str + "\n";
                    }
                    Tcp::instance()->sendToClient(Tcp::instance()->connectedSockFD, sendStr);
                    file.close();
                }
            } else if (buff[0] == 'G' && buff[1] == 'E' && buff[2] == 'T' && buff[3] == ' ' && buff[4] == '/' &&
                       buff[5] == 's' && buff[6] == 't') {
                // parse GET style.css request
                // TODO: send head of style request
                std::string sendStr;
                std::ifstream file;
                file.open("style.css");
                if (!file.is_open()) {
                    std::cout << "\n Cant open file";
                } else {
                    std::cout << "Style send" << std::endl;
                    str.clear();
                    sendStr += "\n";
                    while (std::getline(file, str)) {
                        sendStr += str + "\n";
                    }
                    Tcp::instance()->sendToClient(Tcp::instance()->connectedSockFD, sendStr);
                    file.close();
                }
            } else if (buff[0] == 'G' && buff[1] == 'E' && buff[2] == 'T' && buff[3] == ' ' && buff[4] == '/' &&
                       buff[5] == 's' && buff[6] == 'c') {
                // parse GET script.js request
                std::string sendStr;
                std::ifstream file;
                file.open("sript.js");
                if (!file.is_open()) {
                    std::cout << "\n Cant open file";
                } else {
                    std::cout << "Style send" << std::endl;
                    str.clear();
                    sendStr += "\n";
                    while (std::getline(file, str)) {
                        sendStr += str + "\n";
                    }
                    Tcp::instance()->sendToClient(Tcp::instance()->connectedSockFD, sendStr);
                    file.close();
                }
            }
            if (buff[0] == 's' && buff[1] == 't' && buff[2] == 'a' && buff[3] == 'r' && buff[4] == 't') {
                str = "start";
                Tcp::instance()->sendToClient(Tcp::instance()->connectedSockFD, str);
            }
            if (buff[0] == 'e' && buff[1] == 'x' && buff[2] == 'i' && buff[3] == 't') {
                str = "exit";
                Tcp::instance()->sendToClient(Tcp::instance()->connectedSockFD, str);
                close(sockfd);
                close(Tcp::instance()->connectedSockFD);
                _exit(0);
            }
        }
    }
}
