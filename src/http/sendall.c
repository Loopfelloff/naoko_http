#include<string.h>
#include<stdio.h>
#include<sys/socket.h>
#include "http/sendall.h"

int sendall(int socket_fd , char* buf , int* len){
    
    int total=0;
    int bytes_left = *len;
    int n=0;
    
    while(total < *len){
    
	n = send(socket_fd , buf+total , bytes_left , 0);

	if(n == -1){break;}
	
	bytes_left -= n;
	
	total += n;
	    
	

    }

    *len = total;

    return (n == -1) ? -1 : 0;
}


