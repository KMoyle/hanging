all:
	gcc -std=c99 -D_POSIX_SOURCE src/server.c -I./headers -o bin/server
	gcc -std=c99 -D_POSIX_SOURCE src/client.c -I./headers -o bin/client

clean:
	rm bin/server
	rm bin/client
