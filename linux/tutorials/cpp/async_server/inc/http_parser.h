#ifndef HTTP_PARSER_H
#define HTTP_PARSER_H

#include "tcp.h"
#include "https.h"
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
class HttpParser {
  public:
    HttpParser(bool isHTTPS, int sock_num);
    ~HttpParser();
    void parseData(const char *buff, int len);
    SSL *ssl;
  private:
    bool isHTTPS = false;
    SSL_CTX *ctx;
};

#endif // HTTP_PARSER_H
