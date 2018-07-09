#include "Message_Operations.h"

//Prepares response if file not found
void send_not_found_message(char* response_header, char* mime_type,
	char* content_response) {
	strcpy(response_header,strcat(response_header,HTTP_NOT_FOUND));
	 //send a blank line to indicate the end of the header lines
    strcpy(response_header,strcat(response_header,"\r\n"));
    strcpy(mime_type,strcat(mime_type, NONE));
    strcpy(mime_type,strcat(mime_type,"\r\n"));
    //send the entity body
    strcpy(content_response,strcat(content_response, HTTP_NOT_FOUND_HEADER));
    strcpy(content_response,strcat(content_response, HTTP_NOT_FOUND_BODY));
    strcpy(content_response,strcat(content_response,"\r\n"));
}

//Prepares response if file was found
void send_found_message(char* filetype, char* type ,
	char* response_header, char* mime_type, char* content_response) {
		http_type_parser(filetype, type);
        strcpy(response_header,strcat(response_header, HTTP_OK));
        strcpy(response_header,strcat(response_header,"\r\n"));
        strcpy(mime_type,strcat(mime_type,type));
        strcpy(mime_type,strcat(mime_type,"\r\n"));
	}

//Handles sending the message to client
void send_message(int sock_fd, char* response_header, char* mime_type,
 	char* content_response, int file_found, int file, char* file_name) {

		//Makes sure headers have gone through
	if ((write(sock_fd, response_header, strlen(response_header)) < 0) ||
		(write(sock_fd, mime_type, strlen(mime_type)) == -1) ||
        (write(sock_fd,"\r\n", strlen("\r\n")) <0)) {
			perror("Failed to send message headers");
		}
    //send the body of the content through sendfile
    if (file_found) {
		struct stat st;
	    stat(file_name, &st);
	    size_t size = st.st_size;
	    sendfile(sock_fd, file, NULL,size);
		printf("HELLO");
    }
    else {
        if (write(sock_fd, content_response, 100) < 0){
                perror("File could not be found");
		}
	}
}

//Check file exists
int file_exist_check(char* file_name, FILE *file) {

	int file_exist=1;
	file=fopen(file_name, "rb");
	if (file==NULL){
		file_exist=0;
	}
	return file_exist;
}
