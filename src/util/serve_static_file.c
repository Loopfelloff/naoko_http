#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "util/serve_static_file.h"

int serve_static_file(char* http_request_method , char* resource_name , char** file_read){
    
    if(strcmp(http_request_method , "GET") != 0) return 0;

    size_t full_name_path_length = strlen("./assets") + strlen(resource_name) + 1;
    
    char *full_name = malloc(full_name_path_length);

    snprintf(full_name, full_name_path_length , "./assets%s", resource_name);


    FILE *static_file = fopen(full_name,  "rb");

    free(full_name);

    if(static_file == NULL){
	printf("The file couldn't be accessed \n");
	return 0; // the reason why this is 0 is because we want the next controller to handle the request properly if the said file doesn't exist.
    }
    
    size_t bytes_read;

    size_t init_read = 4096;

    char file_read_buffer[init_read];

    size_t cap = 4096;

    size_t current_read = 0;

    char *final_full_buffer = malloc(cap);

    *final_full_buffer = '\0'; 

    while((bytes_read = fread(file_read_buffer , 1 , sizeof(file_read_buffer) - 1, static_file))> 0){

	current_read += bytes_read;

	if(current_read > cap){
	    cap *= 2;
	    char *temp_read = realloc(final_full_buffer , cap);
	    if(temp_read == NULL){
		fclose(static_file);		
		free(final_full_buffer);
		return -1;
	    }
	    
	    final_full_buffer = temp_read;
	    
	    }
    
	file_read_buffer[bytes_read] = '\0';

	strcat(final_full_buffer , file_read_buffer);
	
    }
    *file_read = final_full_buffer; // Don't forget to clear this from outside.

    fclose(static_file);
    
    return 0;
}
