#ifndef MESSAGE_OPS
#define MESSAGE_OPS

#include "Request_Handler.h"
#include "HTTP_Parser.h"
#include <sys/sendfile.h>

#define HTTP_OK "200 OK"
#define HTTP_NOT_FOUND "404 Not Found"
#define NONE "NONE"
#define HTTP_NOT_FOUND_HEADER "<HEAD><TITLE>404 Not Found</TITLE></HEAD>"
#define HTTP_NOT_FOUND_BODY "<BODY>Not Found</BODY></html>"

void send_not_found_message(char* response_header, char* mime_type,
	char* content_response);
void send_found_message(char* filetype, char* type ,char* response_header,
	 char* mime_type, char* content_response);
void send_message(int sock_fd, char* response_header, char* mime_type,
 	char* content_response, int file_found, int file, char* file_name);
int file_exist_check(char* fileName, FILE* file);

#endif
