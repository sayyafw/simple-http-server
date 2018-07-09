objects = HTTP_Parser.o Server.o Request_Handler.o Message_Operations.o

server: $(objects)
	gcc -pthread -Wall -o server  $(objects)

Server.o: Server.c Request_Handler.h
	gcc -pthread -c -Wall Server.c -g

Request_Handler.o: Request_Handler.c Request_Handler.h HTTP_Parser.h
	gcc -pthread -c -Wall Request_Handler.c -g

HTTP_Parser.o: HTTP_Parser.c HTTP_Parser.h Message_Operations.h
	gcc -pthread -c -Wall HTTP_Parser.c -g

Message_Operations.o: Message_Operations.c Message_Operations.h HTTP_Parser.h \
	Request_Handler.h
	gcc -pthread -c -Wall Message_Operations.c -g
clean :
	rm Server $(objects)
