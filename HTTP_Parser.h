#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void http_type_parser(char* filetype, char* type);
void http_response_formatter(int file_found, char* filetype, char* type ,
	char* response_header, char* mime_type, char* content_response);

 #endif
