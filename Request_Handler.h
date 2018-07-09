#ifndef REQUEST_HANDLER
#define REQUEST_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <time.h>
#include <pthread.h>
#include "HTTP_Parser.h"

#define MAXDATASIZE 1000

typedef struct information {
	int sock_fd;
	char home[PATH_MAX + 1];
} info;

void httpRequest(void* data);
void message_prep(char* file_name, int file_exist, int sock_fd, int file);

#endif
