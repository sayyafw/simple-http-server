#include "Request_Handler.h"

void httpRequest(void* data);
int file_exist_check(char* file_name, FILE* file);

/** Parses the client sent request, reads the data and
    calls the message prep function to prep response for client
    */
void httpRequest(void* data) {

    info args = *((info*)data);
	int sock_fd = args.sock_fd;
    char buffer[256], request[100],tmp[100];
    int a=0,b=0,received=-1, file_exist=1;
	char *file_name,*fl1,*fl2;
	FILE *file;
    //initialises to zeros
    bzero(buffer,255);
    //reads client request
	int n = read(sock_fd,buffer,255);
	if (n < 0)
	{
		perror("ERROR reading from socket");
		exit(1);
	}

    buffer[received - 1]='\0';
    //Parses request line
    while(buffer[a]!= '\n' || a < received - 1) {
		request[a] = buffer[a];
		a++;
    }
	request[a] = '\0';
//Get the "GET" word.
    while(request[b] != ' ') {
        b++;
    }
	strncpy(tmp, request, b);

	//Extract filename
    if (strcmp(tmp,"GET") == 0) {
        fl1=strpbrk(request,"/");
		//Remove succeeding spaces
    	fl2=strtok(fl1," ");
        file_name=strpbrk(fl2,"/");
    }

    //Get the full home directory
    strcpy(file_name,strcat(args.home, file_name));
    //Check if file exists
	file =fopen(file_name, "rb");
	if (file ==NULL){
		file_exist=0;
	}
    else {
        fclose(file);
    }
    //Get file descriptor
    int fd = open(file_name, O_RDONLY);
	message_prep(file_name, file_exist, sock_fd, fd);
	close(sock_fd);           // Close the connection.
	pthread_exit(NULL);
}

/** Does the necessary work to prepare the response to client */
void message_prep(char* file_name, int file_exist, int sock_fd, int file) {
    char *filetype;
    char type[64];
	char response_header[100]="HTTP/1.0 ";
	char mime_type[100]="Content-type: ";
	char content_response[100]="<html>";
    int s='.';
    filetype=strrchr(file_name, s);
	http_type_parser(filetype, type);
	http_response_formatter(file_exist, filetype, type, response_header,
		mime_type, content_response);
	send_message(sock_fd, response_header, mime_type, content_response,
		 file_exist, file, file_name);
}
