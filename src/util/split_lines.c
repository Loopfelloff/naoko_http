#include<string.h>
#include<stdio.h>
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


	if(end)    
	    lines[n] = malloc(length_of_sentence);
	else 
	    lines[n] = malloc(length_of_sentence+1);
	

	if(!lines[n]) goto fail;	
	
	if(end)
	    { 
	    memcpy(lines[n] , start , length_of_sentence-1);
	    lines[n][length_of_sentence-1] = '\0';
	    start += length_of_sentence;
}
	else {
	    memcpy(lines[n] , start , length_of_sentence);
	    lines[n][length_of_sentence] = '\0';
	    start += (length_of_sentence+1);
	}
	
	n++;

	if(*start == '\n') start++;
	
    }
    
    *out = lines;

    *out_len = n;

    return 0;

    fail:
	for(size_t i =0; i<n; i++) free(lines[i]);
	free(lines);
	return -1;

}
