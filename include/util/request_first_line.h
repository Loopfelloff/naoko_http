#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#define HTTP_METHOD_MAX   16    /* GET, POST, DELETE, ... */
#define HTTP_PATH_MAX     256   /* /index.html */
#define HTTP_VERSION_MAX  16    /* HTTP/1.1 */
#define HTTP_CTYPE_MAX    64    /* text/html, image/png, ... */

typedef struct {
    char method[HTTP_METHOD_MAX];     /* request type, e.g. "GET"          */
    char path[HTTP_PATH_MAX];         /* requested file, e.g. "/index.html" */
    char version[HTTP_VERSION_MAX];   /* e.g. "HTTP/1.1"                   */
    char content_type[HTTP_CTYPE_MAX];/* filled in later during processing */
} http_request_t;

/*
 * Parses a request line such as "GET /index.html HTTP/1.1"
 * into req. content_type is left empty (set to "").
 * Returns 0 on success, -1 on a malformed line.
 */
int parse_request_line(const char *line, http_request_t *req);

#endif /* HTTP_REQUEST_H */
