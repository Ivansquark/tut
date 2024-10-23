#include "http_parser.h"

HttpParser::HttpParser(bool isHTTPS, int sock_num) {
    this->isHTTPS = isHTTPS;
    if (isHTTPS) {
        std::cout << "DEBUG 0" << std::endl;
        ctx = initialize_ctx(KEY_FILE, PEM_FILE);
        ssl = SSL_new(ctx);
        SSL_set_fd(ssl, sock_num);
        char rbuff[8000];
        memset(rbuff, '\0', sizeof(rbuff));
        int connect = SSL_accept(ssl);
        int error = SSL_get_error(ssl, connect);
        if (error < 0) {
            printf("SSL accept error %d\n", error);
            printf("SSL accept error code %d\n", SSL_get_error(ssl, error));
            exit(error);
        } else {
            printf("SSL accept %d\n", error);
        }
    }
}
HttpParser::~HttpParser() {
    if (isHTTPS) {
        SSL_CTX_free(ctx);
    }
}

void HttpParser::parseData(const char *buff, int len) {
    // parse first GET request
    int sockfd = 0;
    std::string str;
    if (buff[0] == 'G' && buff[1] == 'E' && buff[2] == 'T' && buff[3] == ' ' && buff[4] == '/' && buff[5] == ' ') {
        std::string sendStr = "HTTP/1.1 200 OK\n"
                              "Content-Type: text/html; charset=UTF-8\n"
                              "Content-Length: ";
        struct stat sb;
        stat("index.html", &sb);
        int length = sb.st_size; // get file length
        std::cout << "\nlength = " << length;
        sendStr += std::to_string(length) + "\n";
        if (isHTTPS) {
            ssl_write(ssl, (char *)sendStr.data(), sendStr.size());
        } else {
            Tcp::instance()->sendToClient(Tcp::instance()->connectedSockFD, sendStr);
        }
        std::ifstream file;
        file.open("index.html");
        if (!file.is_open()) {
            std::cout << "\n Cant open file index.html";
        } else {
            std::cout << "Html sended\n" << std::endl;
            str.clear();
            sendStr += "\n";
            std::cout << sendStr << "\n";
            while (std::getline(file, str)) {
                sendStr += str + "\n";
            }
            if (isHTTPS) {
                ssl_write(ssl, (char *)sendStr.data(), sendStr.size());
            } else {
                Tcp::instance()->sendToClient(Tcp::instance()->connectedSockFD, sendStr);
            }
            file.close();
        }
    } else if (buff[0] == 'G' && buff[1] == 'E' && buff[2] == 'T' && buff[3] == ' ' && buff[4] == '/' &&
               buff[5] == 's' && buff[6] == 't') {
        // parse GET style.css request
        std::string sendStr = "HTTP/1.1 200 OK\n"
                              "Content-Type: text/css; charset=UTF-8\n"
                              "Content-Length: ";
        struct stat sb;
        stat("style.css", &sb);
        int length = sb.st_size; // get file length
        std::cout << "\nlength = " << length;
        sendStr += std::to_string(length) + "\n";
        if (isHTTPS) {
            ssl_write(ssl, (char *)sendStr.data(), sendStr.size());
        } else {
            Tcp::instance()->sendToClient(Tcp::instance()->connectedSockFD, sendStr);
        }
        std::ifstream file;
        file.open("style.css");
        if (!file.is_open()) {
            std::cout << "\n Cant open file style.css";
        } else {
            std::cout << "Style sended\n" << std::endl;
            str.clear();
            sendStr += "\n";
            while (std::getline(file, str)) {
                sendStr += str + "\n";
            }
            if (isHTTPS) {
                ssl_write(ssl, (char *)sendStr.data(), sendStr.size());
            } else {
                Tcp::instance()->sendToClient(Tcp::instance()->connectedSockFD, sendStr);
            }
            file.close();
        }
    } else if (buff[0] == 'G' && buff[1] == 'E' && buff[2] == 'T' && buff[3] == ' ' && buff[4] == '/' &&
               buff[5] == 's' && buff[6] == 'c') {
        // parse GET script.js request
        std::string sendStr = "HTTP/1.1 200 OK\n"
                              "Content-Type: text/javascript; charset=UTF-8\n"
                              "Content-Length: ";
        struct stat sb;
        stat("script.js", &sb);
        int length = sb.st_size; // get file length
        std::cout << "\nlength = " << length;
        sendStr += std::to_string(length) + "\n";
        if (isHTTPS) {
            ssl_write(ssl, (char *)sendStr.data(), sendStr.size());
        } else {
            Tcp::instance()->sendToClient(Tcp::instance()->connectedSockFD, sendStr);
        }
        std::ifstream file;
        file.open("script.js");
        if (!file.is_open()) {
            std::cout << "\n Cant open file script.js\n";
        } else {
            std::cout << "Script sended\n" << std::endl;
            str.clear();
            sendStr += "\n";
            while (std::getline(file, str)) {
                sendStr += str + "\n";
            }
            if (isHTTPS) {
                ssl_write(ssl, (char *)sendStr.data(), sendStr.size());
            } else {
                Tcp::instance()->sendToClient(Tcp::instance()->connectedSockFD, sendStr);
            }
            file.close();
        }
    } else if (buff[0] == 'G' && buff[1] == 'E' && buff[2] == 'T' && buff[3] == ' ' && buff[4] == '/' &&
               buff[5] == 'f' && buff[6] == 'a') {
        // parse GET favicon.ico request
        std::string sendStr = "HTTP/1.1 200 OK\n"
                              "Content-Type: image/png; charset=UTF-8\n"
                              "Content-Length: ";
        struct stat sb;
        stat("icon.png", &sb);
        int length = sb.st_size; // get file length
        std::cout << "\nlength = " << length;
        sendStr += std::to_string(length) + "\n";
        if (isHTTPS) {
            ssl_write(ssl, (char *)sendStr.data(), sendStr.size());
        } else {
            Tcp::instance()->sendToClient(Tcp::instance()->connectedSockFD, sendStr);
        }
        std::ifstream file;
        file.open("icon.png");
        if (!file.is_open()) {
            std::cout << "\n Cant open file icon.png";
        } else {
            std::cout << "Icon send" << std::endl;
            str.clear();
            sendStr += "\n";
            while (std::getline(file, str)) {
                sendStr += str + "\n";
            }
            if (isHTTPS) {
                ssl_write(ssl, (char *)sendStr.data(), sendStr.size());
            } else {
                Tcp::instance()->sendToClient(Tcp::instance()->connectedSockFD, sendStr);
            }
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
