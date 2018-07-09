#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "HTTP_Parser.h"
#include "Message_Operations.h"

//Parse mime type
void http_type_parser(char* filetype, char* type){

	if((strcmp(filetype,".htm"))==0 || (strcmp(filetype,".html"))==0) {
        strcpy(type,"text/html");
	}
    else if(strcmp(filetype,".jpg")==0) {
        strcpy(type,"image/jpeg");
	}
    else if(strcmp(filetype,".css")==0) {
        strcpy(type,"text/css");
	}
    else if(strcmp(filetype,".js")==0) {
        strcpy(type,"text/javascript");
	}
}

//format response messafe for client
void http_response_formatter(int file_found, char* filetype, char* type, \
	char* response_header, char* mime_type, char* content_response) {

	if(file_found==1) {
    	send_found_message(filetype, type, response_header, mime_type,
			content_response);
    }

    else
    {
        send_not_found_message(response_header, mime_type, content_response);
    }
}
