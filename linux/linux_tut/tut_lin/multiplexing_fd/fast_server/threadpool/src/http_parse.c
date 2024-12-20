#include "http_parse.h"

#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

File_Buf_Addr files_addr;

//@ fill global structure of mmaped files addresses and sizes
static int fill_addr_struct(char* name, char** addr, int* size) {
    int fd_index = open(name, O_RDONLY, 0400);
    if (fd_index < 0) {
        perror("read index.html");
        return -1;
    }
    struct stat info;
    if (stat(name, &info) < 0) {
        perror("icon stat");
        return -1;
    }
    int len = info.st_size;
    int len_off = len % 4096;
    len_off = 4096 - len_off;
    printf("%s len = %d; len + off = %d\n", name, len, len + len_off);
    char* buf_ret =
        mmap(NULL, len + len_off, PROT_READ, MAP_PRIVATE, fd_index, 0);
    if (buf_ret == (void*)-1) {
        perror("index mmap");
        return -1;
    }
    *addr = buf_ret;
    *size = len;
    close(fd_index);
    return 0;
}

int http_prepare_read_file_bufs() {
    // TODO mmap r/o files to buffers

    if ((fill_addr_struct((char*)"index.html", &files_addr.index_html,
                          &files_addr.index_size)) < 0) {
        return -1;
    }
    if ((fill_addr_struct((char*)"icon.png", &files_addr.icon_png,
                          &files_addr.icon_size)) < 0) {
        return -1;
    }
    if ((fill_addr_struct((char*)"style.css", &files_addr.style_css,
                          &files_addr.style_size)) < 0) {
        return -1;
    }
    if ((fill_addr_struct((char*)"script.js", &files_addr.script_js,
                          &files_addr.script_size)) < 0) {
        return -1;
    }
    return 0;
}

int http_parse(char* arr, char* head, char** data, size_t* data_sz) {
    // strtok
    char method[1024] = {0};
    char* ptr_method = NULL;
    char* ptr_r1 = NULL;
    ptr_method = strtok_r(arr, " \t\r\n", &ptr_r1);
    int sz = strlen(ptr_method);
    memcpy(method, ptr_method, sz);
    //printf("method = %s\n", method);

    char uri[1024] = {0};
    char* ptr_uri = NULL;
    ptr_uri = strtok_r(NULL, " ?", &ptr_r1);
    memcpy(uri, ptr_uri, strlen(ptr_uri));
    //printf("uri = %s\n", uri);

    if (!strcmp(method, "GET")) {
        if (!strcmp(uri, "/index.html") || !(strcmp(uri, "/"))) {
            const char ret_head[] = "HTTP/1.1 200 OK\n"
                                    "Content-Type: text/html; charset=UTF-8\n"
                                    "Content-Length: ";
            memcpy(head, ret_head, sizeof(ret_head));
            char size[10] = {0};
            sprintf(size, "%d\r\n\r\n", files_addr.index_size);
            strcat(head, size);
            *data = files_addr.index_html;
            *data_sz = files_addr.index_size;
        } else if (!strcmp(uri, "/favicon.ico")) {
            const char ret_head[] = "HTTP/1.1 200 OK\n"
                                    "Content-Type: image/png; charset=UTF-8\n"
                                    "Content-Length: ";
            memcpy(head, ret_head, sizeof(ret_head));
            char size[10] = {0};
            sprintf(size, "%d\r\n\r\n", files_addr.icon_size);
            strcat(head, size);
            *data = files_addr.icon_png;
            *data_sz = files_addr.icon_size;
        } else if (!strcmp(uri, "/style.css")) {
            const char ret_head[] = "HTTP/1.1 200 OK\n"
                                    "Content-Type: text/css; charset=UTF-8\n"
                                    "Content-Length: ";
            memcpy(head, ret_head, sizeof(ret_head));
            char size[10] = {0};
            sprintf(size, "%d\r\n\r\n", files_addr.style_size);
            strcat(head, size);
            *data = files_addr.style_css;
            *data_sz = files_addr.style_size;
        } else if (!strcmp(uri, "/script.js")) {
            const char ret_head[] =
                "HTTP/1.1 200 OK\n"
                "Content-Type: text/javascript; charset=UTF-8\n"
                "Content-Length: ";
            memcpy(head, ret_head, sizeof(ret_head));
            char size[10] = {0};
            sprintf(size, "%d\r\n\r\n", files_addr.script_size);
            strcat(head, size);
            *data = files_addr.script_js;
            *data_sz = files_addr.script_size;
        } else if (!strcmp(uri, "/content.bin")) {
            const char ret_head[] =
                "HTTP/1.1 200 OK\n"
                "Content-Type: application/octet-stream;\n"
                "Content-Length: ";
            memcpy(head, ret_head, sizeof(ret_head));
            char size[10] = {0};
            sprintf(size, "%d\r\n\r\n", 4);
            strcat(head, size);
            static int val = 0;
            //static __thread int val = 0; //thread local
            //int val = 4;
            *data = (char*)&val;
            *data_sz = 4;
            val++;
        } else {
            // 404
            const char ret_head[] = "HTTP/1.0 404 Not Found\r\n"
                                "Date: 12 1212 2020 GMT\r\n"
                                "Server: FastServer\r\n"
                                "Content-Length: 0\r\n"
                                "Connection: close\r\n"
                                "Content-Type: text/html\r\n";
            memcpy(head, ret_head, sizeof(ret_head));
            printf("uri not parsed: \n%s\n", arr);
            data = NULL;
        }
    } else {
        printf("method not parsed: \n%s\n", arr);
        head = NULL;
        data = NULL;
    }
    return 0;
}

int http_return_file_bus_addr([[maybe_unused]] File_Buf_Addr* addr) {
    addr = &files_addr;
    return 0;
}
