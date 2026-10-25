#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Here i include my custom header files

#include "http/build_static_file_response.h"
#include "util/request_first_line.h"

const char *content_type(char* mime_type){

    if(strcpy(mime_type , "html")) return "text/html";
    else if(strcpy(mime_type , "css")) return "text/css";
    else if(strcpy(mime_type , "js")) return "text/javascript";
    else return "unknown";
}

const char *status_text(int code) {
    switch (code) {
        case 200: return "OK";
        case 404: return "Not Found";
        case 500: return "Internal Server Error";
        default:  return "Unknown";
    }
}

// Returns a malloc'd buffer holding the full response. Caller frees it.
// *out_len receives the total size in bytes.
char *build_response(int status, const char *mime,
                     const char *body, size_t body_len,
                     size_t *out_len )
{

    const char *fmt =
        "HTTP/1.1 %d %s\r\n"
        "Content-Type: %s; charset=utf-8\r\n"
        "Content-Length: %zu\r\n"
        "\r\n";

//First i am taking just the length
    int header_len = snprintf(NULL, 0, fmt, status, status_text(status), content_type(mime), body_len);
    if (header_len < 0) return NULL;

    char *buf = malloc((size_t)header_len + body_len + 1);
    if (!buf) return NULL;

    // actually copying the header to the buffer 
    snprintf(buf, (size_t)header_len + 1, fmt, status, status_text(status), content_type(mime), body_len);
    // appending the body right after the header
    memcpy(buf + header_len, body, body_len);
    buf[header_len + body_len] = '\0';  // only for convenience when printing text

    *out_len = (size_t)header_len + body_len;
    return buf;
}

