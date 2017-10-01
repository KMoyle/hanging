all:
	gcc -std=gnu99 -D_POSIX_SOURCE -D_XOPEN_SOURCE=700 -lpthread src/server.c -I./headers -o bin/server

clean:
	rm bin/server




