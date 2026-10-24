#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "util/request_first_line.h"


int main(){

    http_request_t *req = malloc(sizeof(http_request_t )) ;

    char *request_first = "GET /index.html HTTP/1.1";


    if(parse_request_line(request_first , req) == -1){
	fprintf(stderr , "Failed to parse \n");
	free(req);
	return 1;
	}

    printf("%s \n" , req->method);	    
    printf("%s \n" , req->path);	    
    printf("%s \n" , req->version);	    
    free(req);
    return 0;
}
