/** Multithreaded HTTP Server. Code Adapted by lab code provided
    by comp30023 labs
    Capable of answering get requests for a limited range of file types
    Author: Sayyaf Waseem
    Date: 19/4/2018
    */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h> //for threading , link with lpthread
#include "Request_Handler.h"
#include <limits.h>

struct sockaddr_in build_address(int portno);
int create_thread(int new_sock_fd, char* argv[], pthread_t p_thread[], int i);

int main (int argc, char* argv[]) {

    int sockfd, new_sock_fd, portno;  // listen on sock_fd, new connection on new_sock_fd
    struct sockaddr_in serv_addr, cli_addr;    // my address information
    socklen_t clilen;
    pthread_t p_thread[3000];
    int i=0;
//Create the parent socket.
    if (argc < 3){
            printf("Incorrect Params\n");
            exit(EXIT_FAILURE);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);

    serv_addr = build_address(portno);

//Binding
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("bind");
        exit(1);
    }
//Make this socket ready to accept connection requests.
    if (listen(sockfd, 3) < 0) {
        perror("socket listen error");
        exit(1);
    }

    while(1)
   {  // main accept() loop
        clilen = sizeof(cli_addr);
        if ((new_sock_fd = accept(sockfd, (struct sockaddr *)&cli_addr,
            &clilen)) < 0) {
            perror("accept");
            continue;
        }
        i = create_thread(new_sock_fd, argv, p_thread, i);
   }

    return 0;
}

/*handles thread creation and sends a void struct to provide necessary args
for function */
int create_thread(int new_sock_fd, char* argv[], pthread_t p_thread[], int i) {
    info args;
    args.sock_fd = new_sock_fd;
    strcpy(args.home, argv[2]);
    pthread_create(&p_thread[i++],NULL,(void*)httpRequest,(void*)&args);
    pthread_join(p_thread[i-1], NULL);
    return i;
}

//Build the server's address.
struct sockaddr_in build_address(int portno) {
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    return serv_addr;
}
