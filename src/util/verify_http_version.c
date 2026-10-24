#include<string.h>

int verify_http_version(char* version_to_verify , char** verifiable_list){
    size_t list_len = sizeof(verifiable_list)/ sizeof(char*);
    for(size_t i = 0; i < list_len; i++){
	if(strcmp(version_to_verify , *(verifiable_list+i)) == 0){
	    return 0;
}
}
    return -1;
}
