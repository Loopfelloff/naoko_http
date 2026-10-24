#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "util/request_first_line.h"

int parse_request_line(const char *line, http_request_t *req) {
    memset(req, 0, sizeof(*req));
    /* the width limits are one less than each buffer size, leaving room for '\0' */
    if (sscanf(line, "%15s %255s %15s", req->method, req->path, req->version) != 3)
        return -1;
    return 0;
}
