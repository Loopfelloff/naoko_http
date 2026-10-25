#include<stdlib.h>
#include<string.h>
#include<stdio.h>

// custome imports 

#include "http/build_static_file_response.h"
#include "util/request_first_line.h"


int main(){

    int status = 200;

    http_request_t *req = malloc(sizeof(http_request_t));

    strcpy(req->content_type , "html");

    const char* body = "<html><body>Welcome to the Jungle</body></html>";

    size_t body_len = strlen(body);

    size_t *out_len = malloc(sizeof(size_t));

    build_response(status , req->content_type , body , body_len , out_len);

    char *final_response_body = malloc(*out_len);

    final_response_body = build_response(status , req->content_type , body , body_len , out_len);

    printf("%s \n" , final_response_body);

    free(final_response_body);

    return 0;
}
