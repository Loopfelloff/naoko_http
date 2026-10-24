#include<stdio.h>
#include<string.h>
#include "server.h" 

#define ip_addr "127.0.0.1"
#define port 3490
#define backlog 10
#define buf_len 1024

int main(){
    printf("We are running the app!!! \n");
    char *verifiable_list[] = {"HTTP/1.1"}; 
    start_server(ip_addr , port , 10 , (size_t)buf_len , verifiable_list);
    return 0;
}
