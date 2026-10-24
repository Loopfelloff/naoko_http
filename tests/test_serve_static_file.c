#include<stdio.h>
#include"util/serve_static_file.h"

int main(){
    if(serve_static_file() == -1){
	fprintf(stderr , "The file couldn't be accessed \n");
	return 0;
}
    printf("The file is accessible \n");
    return 0;
}
