all:
	gcc -std=gnu99 -lpthread src/server.c -I./headers -o bin/server

clean:
	rm bin/server




