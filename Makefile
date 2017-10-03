all:
	gcc -std=c99 -D_POSIX_SOURCE -pthread src/server.c -I./headers -o bin/server

clean:
	rm bin/server




