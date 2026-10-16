#include<stdio.h>
#include "server.h" 

#define ip_addr "127.0.0.1"
#define port 3490
#define backlog 10

int main(){
    printf("We are running the app!!! \n");
    start_server(ip_addr , port , 10);
    return 0;
}
