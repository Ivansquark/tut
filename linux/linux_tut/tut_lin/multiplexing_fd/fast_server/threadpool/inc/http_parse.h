#ifndef HTTP_PARSE
#define HTTP_PARSE

#include <stdlib.h>
#include <string.h>

typedef struct {
    char* index_html;
    int index_size;
    char* icon_png;
    int icon_size;
    char* style_css;
    int style_size;
    char* script_js;
    int script_size;
} File_Buf_Addr;

int http_parse(char* buf, size_t buf_size, char* head, char* data); 
int http_prepare_read_file_bufs(File_Buf_Addr* addr);
int http_return_file_bus_addr(File_Buf_Addr* addr);

#endif // HTTP_PARSE
