

all:
	gcc -std=c99 -D_POSIX_SOURCE -pthread src/server.c -I./headers -o bin/server
	gcc -std=c99 -D_POSIX_SOURCE -pthread src/client.c -I./headers -o bin/client
	gcc -std=c99 -D_POSIX_SOURCE src/hangman.c -I./headers -o bin/hangman

clientgdb:
	gcc -g -std=c99 -D_POSIX_SOURCE -pthread src/client.c -I./headers -o bin/client

servergbd:
	gcc -g -std=c99 -D_POSIX_SOURCE -pthread src/server.c -I./headers -o bin/server

clean:
	rm bin/server
	rm bin/client
	rm bin/hangman
