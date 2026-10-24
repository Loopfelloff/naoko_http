#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#define HTTP_METHOD_MAX   16    
#define HTTP_PATH_MAX     256   
#define HTTP_VERSION_MAX  16   
#define HTTP_CTYPE_MAX    64  

typedef struct {
    char method[HTTP_METHOD_MAX];   
    char path[HTTP_PATH_MAX];       
    char version[HTTP_VERSION_MAX]; 
    char content_type[HTTP_CTYPE_MAX];
} http_request_t;

int parse_request_line(const char *line, http_request_t *req);

#endif 
