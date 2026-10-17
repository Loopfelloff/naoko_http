#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "util/split_lines.h"

int main(){
    char *buf = "GET /index.html HTTP/1.1\r\nHost: localhost:3000\r\nConnection: close\r\nUser-Agent: Mozilla/5.0 (X11; Linux x86_64)\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: identity\r\nCache-Control: no-cache\r\nPragma: no-cache\r\nUpgrade-Insecure-Requests: 1\r\nDNT: 1\r\nReferer: http://localhost:3000/\r\nOrigin: http://localhost:3000\r\nX-Requested-With: XMLHttpRequest\r\nX-Custom-Header-1: one\r\nX-Custom-Header-2: two\r\nX-Custom-Header-3: three\r\nX-Custom-Header-4: four\r\n\r\n";
    char **lines;
    size_t out;    

    if(split_into_lines(buf , &lines , &out) != 0){
	fprintf(stderr , "out of memory \n");
	return 1;
    }

    char *to_compare_with_buf[] = {
  "GET /index.html HTTP/1.1",
  "Host: localhost:3000",
  "Connection: close",
  "User-Agent: Mozilla/5.0 (X11; Linux x86_64)",
  "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
  "Accept-Language: en-US,en;q=0.5",
  "Accept-Encoding: identity",
  "Cache-Control: no-cache",
  "Pragma: no-cache",
  "Upgrade-Insecure-Requests: 1",
  "DNT: 1",
  "Referer: http://localhost:3000/",
  "Origin: http://localhost:3000",
  "X-Requested-With: XMLHttpRequest",
  "X-Custom-Header-1: one",
  "X-Custom-Header-2: two",
  "X-Custom-Header-3: three",
  "X-Custom-Header-4: four",
  "",
    };
    if(out != 19){
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
