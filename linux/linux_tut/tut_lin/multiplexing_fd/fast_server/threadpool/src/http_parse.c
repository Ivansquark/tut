#include "http_parse.h"

int http_prepare_read_file_bufs() {
    //TODO mmap r/o files to buffers
    return 0;
}

int http_return_file_bus_addr(File_Buf_Addr* addr) {
    return 0;
}

int http_parse(char* buf, size_t buf_size, char* head, char* data) {
    // strtok
    char method[256] = {0};
    if (strcmp(buf, "GET") == 0) {
        const char ret_head[] = "HTTP/1.1 200 OK\n"
                                "Content-Type: text/html; charset=UTF-8\n"
                                "Content-Length: ";
        memcpy(head, ret_head, sizeof(ret_head));
        //TODO parse file to return and fil data
        //file mmap!!! memcpy, munmap;
    }
    return 0;
}
