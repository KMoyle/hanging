CC = c99 
CFLAGS = -Wall # Show all reasonable warnings
LDFLAGS = 

all: server

server: server.o

server.o: server.c

clean:
	rm -f server *.o 
 
.PHONY: clean
