#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>


//custome header file includes are mentioned in here.
#include "server.h"
#include "http/sendall.h"
#include "util/split_lines.h"
#include "http/receiveall.h"
#include "util/split_lines.h"

void sigchld_handler(int s) // This is what the structure of the function should look like always btw.
{
    while(wait(NULL) > 0);
}
void start_server(char* ip_addr , int port , int backlog , size_t buf_len){
    int sockfd, new_fd; // listen on sock_fd, new connection on new_fd
    struct sockaddr_in my_addr; // my address information
    struct sockaddr_in their_addr; // connector’s address information
    int sin_size;
    struct sigaction sa;
    int yes=1;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
	perror("socket");
	exit(1);
    }
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
    sizeof(int)) == -1) {
	perror("setsockopt");
	exit(1);
    }
    my_addr.sin_family = AF_INET; // host byte order
    my_addr.sin_port = htons(port); // short, network byte order
    my_addr.sin_addr.s_addr = inet_addr(ip_addr); // automatically fill with my IP
    memset(&(my_addr.sin_zero), 0, 8); // zero the rest of the struct
    if (bind(sockfd, (struct sockaddr *)&my_addr,
	sizeof(struct sockaddr)) == -1) {
	perror("bind");
	exit(1);
    }
    

    if (listen(sockfd, backlog) == -1) {
	perror("listen");
	exit(1);
    }

    // basically with these signals what are we doing is trying to associate that SIGCHLD signal whicch is an async signal the OS sends to a process when one of it's child is terminated , or finisehd with execution (which is what we need to reap the zombie process).

    sa.sa_handler = sigchld_handler;  // associating the signal with the task to perform.
    sigemptyset(&sa.sa_mask); // filled with garbage at first so clean it .
    sa.sa_flags = SA_RESTART; // any task interrupted by the signal are continued later on.
    if (sigaction(SIGCHLD, &sa, NULL) == -1) { // this is where we associate the sa with the signal
// This signaction function specifies that if SIGCHLD signal where to be thrown at the the l
// However if you are having problem with remembering this piece of code just look up the man page for sigaction there is a very similar example code to this snippet so that could work pretty fine
	perror("sigaction");
	exit(1);

    }

    while(1) { // main accept() loop
	sin_size = sizeof(struct sockaddr_in);
	if ((new_fd = accept(sockfd,
	(struct sockaddr *)&their_addr, &sin_size)) == -1) {
	    perror("accept");
	    continue;
	}

	printf("server: got connection from %s\n",
	inet_ntoa(their_addr.sin_addr));

	if (!fork()) { // this is the child process
	    close(sockfd); // child doesn’t need the listener
	    char *receive_buf = malloc(buf_len);
	    int receive_stat = receiveall(new_fd , &receive_buf , buf_len);
	    if(receive_stat == -1){
		fprintf(stderr, "receive: error occured while receiving \n");
		close(new_fd);
		free(receive_buf);
		exit(-1);		
	    }
	    char **request_into_lines; 
	    size_t length_of_request_array;

	    if(split_into_lines(receive_buf , &request_into_lines , &length_of_request_array ) == -1) 			
	    {
		fprintf(stderr , "split : memory allocation error while splittling \n");
		free(receive_buf);
		exit(-1);
	    }

	    char* to_send_buf = "Hello, world!\n";
	    int length_of_sending = strlen(to_send_buf);
	    if (sendall(new_fd, to_send_buf, &length_of_sending) == -1)
		perror("send");
	    close(new_fd);
	    free(receive_buf);
	    exit(0);
	}
	close(new_fd); // parent doesn’t need this
    }
    return;
}

