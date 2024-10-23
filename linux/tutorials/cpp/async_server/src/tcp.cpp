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
int Tcp::listenConnections() { return listen(sockfd, 3); }
void Tcp::init_server(bool isHTTPS) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    std::cout << "init_server " << std::endl;
    saddr_in = new struct sockaddr_in;
    saddr_connected = new struct sockaddr_in;
    std::cout << " saddr_in " << saddr_in << " sockfd=" << sockfd << std::endl;
    // saddr_in->sin_addr.s_addr = inet_addr("192.168.0.103");
    saddr_in->sin_addr.s_addr = inet_addr(IP);
    saddr_in->sin_family = AF_INET;
    if (isHTTPS) {
        saddr_in->sin_port = htons(443);
    } else {
        saddr_in->sin_port = htons(80);
    }
    sock_len = sizeof(sockaddr_in);
    std::cout << "socklen=" << sock_len << std::endl;
    int b = bind(sockfd, (const sockaddr *)saddr_in, sock_len);
    if (b == -1) {
        std::cout << "Error bind" << std::endl;
        perror("Eror In bind");
        _exit(0);
    }
    if (isHTTPS) {
        ctx = initialize_ctx(KEY_FILE, PEM_FILE);
        if (!SSL_CTX_check_private_key(ctx)) {
            abort();
        }
    }
    int listenErr = listenConnections();
    if (listenErr < 0) {
        std::cout << "listenErr = " << listenErr << std::endl;
    }
    socklen_t saddr_connected_len = sizeof(saddr_connected);
    std::cout << "connectedSockFD = " << connectedSockFD << std::endl;
    std::cout << "Connected IP:" << saddr_connected->sin_addr.s_addr << "\n";
    std::vector<std::unique_ptr<std::thread>> threads;
    while (1) {
        if (isHTTPS) {
            if ((connectedSockFD = accept(sockfd, 0, 0)) < 0) {
                printf("Problem accepting\n");
            }
            if (connectedSockFD > 0) {
                // threads.emplace_back(new std::thread(Tcp::handleConnection, isHTTPS));
                pool.addTask(handleConnection, isHTTPS);
            }
        } else {
            if ((connectedSockFD = accept(sockfd, (sockaddr *)saddr_connected, &saddr_connected_len)) < 0) {
                perror("In accept");
                exit(EXIT_FAILURE);
            }
            if (connectedSockFD > 0) {
                // threads.emplace_back(new std::thread(Tcp::handleConnection, isHTTPS));
                pool.addTask(handleConnection, isHTTPS);
            }
        }
    }
}

void Tcp::handleConnection(bool arg) {
    system("clear");
    std::cout << "new c++ thread ID: " << std::this_thread::get_id() << std::endl;
    std::cout << "connectedSockFDnew = " << Tcp::instance()->connectedSockFD << std::endl;
    char buff[8000];
    memset(buff, 0, 8000);
    bool isHTTPS = arg;
    HttpParser httpParser(isHTTPS, Tcp::instance()->connectedSockFD);
    std::cout << "HttpParser" << std::endl;
    // int connectedSockFD = 0;
    while (1) {
        // int client_sock = *(int *)arg;
        if (!isHTTPS) {
            int size = recv(Tcp::instance()->connectedSockFD, buff, sizeof(buff), 0);
            if (size > 0) {
                std::cout << "size=" << size << std::endl;
                for (int i = 0; i < size; i++) {
                    std::cout << buff[i];
                }
                std::cout << std::endl;
                httpParser.parseData(buff, size);
            }
        } else {
            // https encryption
            int size = SSL_read(httpParser.ssl, buff, sizeof(buff));
            if (size > 0) {
                for (int i = 0; i < size; i++) {
                    std::cout << buff[i];
                }
                httpParser.parseData(buff, size);
            }
            // int error = SSL_get_error(httpParser.ssl, n);
            // if (error == SSL_ERROR_WANT_READ) {
            //    continue;
            //} else if (error == 5) {
            //    break;
            //}
            // buff[offset] = '\0';
            // if (size <= 0) {
            //    return;
            //}
        }
    }
}
