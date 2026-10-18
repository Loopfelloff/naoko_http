#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>

// We include it's header file now 

#include "http/receiveall.h"

int receiveall(int socket_fd , char** to_return_buf , size_t buf_len){

    char buf[buf_len];

    ssize_t n ;

/*    while((n = recv(socket_fd , buf , buf_len - 1 , 0)) > 0){
	    
	buf[n] = '\0';	
	
	strcat(*to_return_buf , buf);
	
    } */
	
    n = recv(socket_fd , buf , buf_len-1  , 0);

    if(n == -1)	return -1;
	
    buf[n] = '\0';
    
    strcat(*to_return_buf , buf);
    
    return n;
}
