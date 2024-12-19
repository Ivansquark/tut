#ifndef HTTP_PARSE
#define HTTP_PARSE

#ifndef __USE_GNU
    #define __USE_GNU
    #define _GNU_SOURCE /* See feature_test_macros(7) */
#endif

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

int http_parse(char* arr, char* head, char** data, size_t* data_sz);
int http_prepare_read_file_bufs();
int http_return_file_bus_addr(File_Buf_Addr* addr);

#endif // HTTP_PARSE
