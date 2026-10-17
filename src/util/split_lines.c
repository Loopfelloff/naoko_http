#include<string.h>
#include<stdlib.h>
#include "util/split_lines.h"

int split_into_lines(char* buf , char*** out , size_t* out_len){
    
    char** lines = NULL;
    
    size_t n = 0; 
	
    size_t cap = 8;

    const char* start = buf;

    lines = malloc(cap * sizeof(char *));
    
    if(!lines) goto fail; 


    while(*start){
	
	const char* end = strchr(start, '\n');
	
	size_t length_of_sentence = (!end) ? strlen(start) : (size_t)(end-start);  

	if(n == cap){
	    cap *=2;
	    char** temp = realloc(lines,cap*sizeof(char *));
	    if(!temp) goto fail;
	    lines = temp;

	}
    
	lines[n] = malloc(length_of_sentence);

	if(!lines[n]) goto fail;	
	
	memcpy(lines[n] , start , length_of_sentence-1);
	
	lines[n][length_of_sentence] = '\0';
	
	n++;

	start += length_of_sentence;

	if(*start == '\n') start++;
	
    }
    
    *out = lines;

    *out_len = n;

    return 0;

    fail:
	for(size_t i =0; i<n; i++) free(lines[n]);
	free(lines);
	return -1;

}
