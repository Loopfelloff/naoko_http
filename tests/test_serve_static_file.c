#include<stdio.h>
#include<stdlib.h>
#include "util/serve_static_file.h"
#include "util/request_first_line.h"

int main(){
    
    http_request_t *req = malloc(sizeof(http_request_t));

    char *http_request_method = "GET"; 

    char *resource_name = "/index.html";

    char **file_read = malloc(sizeof(char *));

    printf("We are here before calling the handler for testing \n");
    
    if(serve_static_file(http_request_method , resource_name , file_read , req) == -1){
	fprintf(stderr , "Some error caught while trying to run the serve_static_file function \n");
	return 0;
}
    printf("We are here just before calling the file buffer print function \n");
    printf("%s \n", *file_read);
    printf("%s : is the content type \n", req->content_type);
    free(*file_read);
    free(file_read);
    return 0;
}
