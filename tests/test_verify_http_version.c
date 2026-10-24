#include<string.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

// local import 
#include "util/verify_http_version.h"

int main(){
    char* allowed_version = "HTTP/1.1";
    char* not_allowed_version = "HTTP/0.9";
    char* verifiable_list[] = {"HTTP/1.1", "HTTP/2.0", "HTTP/1.0"};
    if(verify_http_version(allowed_version , verifiable_list) == -1){
	fprintf(stderr, "HTTP version not allowed \n");
	return 0;
}
    printf("Version is allowed \n");
    
    if(verify_http_version(not_allowed_version , verifiable_list) == -1){
	fprintf(stderr , "Second version is not allowed \n");
	return 0;
}
    printf("Second version is also allowed");
    return 0;

}
