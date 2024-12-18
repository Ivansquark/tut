#include "http_parse.h"

#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int http_prepare_read_file_bufs(File_Buf_Addr* addr) {
    // TODO mmap r/o files to buffers
    int fd_index = open("index.html", O_RDONLY, 0400);
    if (fd_index < 0) {
        perror("read index.html");
        return 1;
    }
    struct stat info;
    if (stat("index.html", &info) < 0) {
        perror("index stat");
        return 1;
    }
    int len = info.st_size;
    int len_off = len % 4096;
    len_off = 4096 - len_off;
    printf("index len = %d; len+off = %d\n", len, len + len_off);
    char* buf_index =
        mmap(NULL, len + len_off, PROT_READ, MAP_PRIVATE, fd_index, 0);
    if (buf_index == (void*)-1) {
        perror("index mmap");
        return 1;
    }
    addr->index_html = buf_index;
    addr->index_size = len;
    close(fd_index);

    fd_index = open("icon.png", O_RDONLY, 0400);
    if (fd_index < 0) {
        perror("read index.html");
        return 1;
    }
    if (stat("icon.png", &info) < 0) {
        perror("icon stat");
        return 1;
    }
    len = info.st_size;
    len_off = len % 4096;
    len_off = 4096 - len_off;
    printf("icon len = %d; len+off = %d\n", len, len + len_off);
    char* buf_icon =
        mmap(NULL, len + len_off, PROT_READ, MAP_PRIVATE, fd_index, 0);
    if (buf_index == (void*)-1) {
        perror("index mmap");
        return 1;
    }
    addr->icon_png = buf_icon;
    addr->icon_size = len;
    close(fd_index);
    return 0;
}

int http_return_file_bus_addr(File_Buf_Addr* addr) { return 0; }

int http_parse(char* buf, size_t buf_size, char* head, char* data) {
    // strtok
    char method[1024] = {0};
    char* ptr_method = NULL;
    ptr_method = strtok(buf, " ");
    printf("buf = %s \nptr_method = %x\n", buf, ptr_method - buf);
    memcpy(method, buf, ptr_method - buf);
    printf("method = %s\n", method);

    char uri[1024] = {0};
    char* ptr_uri = NULL;
    ptr_uri = strtok(NULL, " ");
    memcpy(method, ptr_method, ptr_uri - ptr_method);
    printf("uri = %s\n", uri);

    if (!strcmp(method, "GET")) {
        if (!strcmp(uri, "/index_html")) {
            const char ret_head[] = "HTTP/1.1 200 OK\n"
                                    "Content-Type: text/html; charset=UTF-8\n"
                                    "Content-Length: 0";
            memcpy(head, ret_head, sizeof(ret_head));
        } else {
            printf("uri not parsed: \n%s\n", buf);
            head = NULL;
            data = NULL;
        }
    } else {
        printf("method not parsed: \n%s\n", buf);
        head = NULL;
        data = NULL;
    }
    return 0;
}
