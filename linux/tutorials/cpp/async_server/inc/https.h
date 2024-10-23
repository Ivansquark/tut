#include <openssl/err.h>
#include <openssl/ssl.h>

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
//#include <sys/socket.h>

#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define PEM_FILE "server.pem"
#define KEY_FILE "server.key"
#define BUFSIZZ 4096

SSL_CTX *initialize_ctx(const char *key_file, const char *pem_file);
int ssl_read(SSL *ssl, char* buf, int size);
int ssl_write(SSL* ssl, const char* buf, int size);
