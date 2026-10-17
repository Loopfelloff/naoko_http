#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "util/split_lines.h"

int main(){
    char *buf = "POST /index.html HTTP/1.1\r\nHost: localhost:3000\r\nConnection: close\r\nUser-Agent: Mozilla/5.0 (X11; Linux x86_64)\r\nAccept: application/json\r\nContent-Type: application/json\r\nContent-Length: 24\r\n\r\n{\"name\":\"test\",\"age\":25}";
    char **lines;
    size_t out;    

    if(split_into_lines(buf , &lines , &out) != 0){
	fprintf(stderr , "out of memory \n");
	return 1;
    }

    char *to_compare_with_buf[] = {
"POST /index.html HTTP/1.1",
        "Host: localhost:3000",
        "Connection: close",
        "User-Agent: Mozilla/5.0 (X11; Linux x86_64)",
        "Accept: application/json",
        "Content-Type: application/json",
        "Content-Length: 24",
        "",
        "{\"name\":\"test\",\"age\":25}"
    };
    if(out != 9){
	fprintf(stderr, "the size of the test case isn't passed \n");
	return 1;
    }
    for(size_t i=0; i<out; i++){
	printf("from buffer: %s \n" , lines[i]);
	printf("for comparison: %s \n" , to_compare_with_buf[i]);
	if(strcmp(lines[i], to_compare_with_buf[i]) != 0){
	    fprintf(stderr , "comparison error \n");
	    return 1;
        }
    }

    return 0;
}
