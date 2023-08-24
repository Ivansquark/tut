#include "https.h"

extern BIO *bio_err;
BIO *bio_err = 0;

/* Функция для обработки сигнала SIGPIPE который нам может послать ОС при попытки записи в закрытое соединение*/
static void sigpipe_handle(int x) {}

SSL_CTX *initialize_ctx(const char *key_file, const char *pem_file) {
    if (!bio_err) {
        /* Глобальная инициализация алгоритмов OpenSSL, без неё не обходится не один пример по OpenSSL */
        SSL_library_init();
        SSL_load_error_strings();
        OpenSSL_add_ssl_algorithms();
        /* An error write context */
        bio_err = BIO_new_fp(stderr, BIO_NOCLOSE);
    }
    /* Set up a SIGPIPE handler */
    /* Назначаем обработчик сигнала SIGPIPE который нам может послать ОС при попытки записи в закрытое соединение*/
    signal(SIGPIPE, sigpipe_handle);
    /* Create our context*/
    SSL_CTX *ctx = SSL_CTX_new(SSLv23_server_method());
    /* Load our keys and certificates*/
    if (!(SSL_CTX_use_certificate_file(ctx, pem_file, SSL_FILETYPE_PEM))) {
        printf("Не удалось загрузить файл сертификата\n");
    }
    if (!(SSL_CTX_use_PrivateKey_file(ctx, key_file, SSL_FILETYPE_PEM))) {
        printf("Не удалось загрузить файл ключей\n");
    }
    return ctx;
}

int ssl_read(SSL *ssl, char* buf, int size) {
    int r = 0; int e = 0;
    r = SSL_read(ssl, buf, size);
    if (r < 0) {
        e = SSL_get_error(ssl, r);
    }
    return e;
}
int ssl_write(SSL* ssl, const char* buf, int size) {
    int r = 0; int e = 0;
    r = SSL_write(ssl, buf, size);
    if (r < 0) {
        e = SSL_get_error(ssl, r);
    }
    return e;
}

//static int http_serve(SSL *ssl, int s) {
//    char buf[BUFSIZZ];
//    int r = 0;
//    int e;
//
//    bzero(buf, BUFSIZZ - 1);             // Очистка буфера
//    r = SSL_read(ssl, buf, BUFSIZZ - 1); // Чтение данных
//    if (r < 0)                           // Если r < 0 то произошла ошибка
//    {
//        e = SSL_get_error(ssl, r);
//    }
//    printf("[Длина принятого текста %d, Error:%d]%s\n", r, e, buf);
//
//    /* Запись ответа */
//    r = SSL_write(ssl, "HTTP/1.0 200 OK\r\nServer: EKRServer\r\n\r\nServer test page\r\n",
//                  strlen("HTTP/1.0 200 OK\r\nServer: EKRServer\r\n\r\nServer test page\r\n"));
//    if (r <= 0) // Если r < 0 то произошла ошибка
//    {
//        printf("Write error %d\n", r);
//    } else {
//        printf("Write ok %d\n", r);
//    }
//
//    /* Закрытие соединения */
//    shutdown(s, 1);
//    SSL_shutdown(ssl);
//
//    SSL_free(ssl);
//    close(s);
//
//    return (0);
//}
