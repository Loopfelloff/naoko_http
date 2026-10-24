void start_server(char* ip_addr , int port, int backlog , size_t buf_len , char** verifiable_list);
int sendall(int socket_fd , char* buf , int* len);

