#ifndef HTTP_PARSE
#define HTTP_PARSE

#include <stdlib.h>
#include <string.h>

typedef struct {
    char* index_html;
    char* ico_bmp;
    char* style_css;
    char* script_js;
} File_Buf_Addr;

int http_parse(char* buf, size_t buf_size, char* method); 
int http_prepare_read_file_bufs();
int http_return_file_bus_addr(File_Buf_Addr* addr);

#endif // HTTP_PARSE
