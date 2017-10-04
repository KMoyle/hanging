all:
	gcc -std=gnu99 -lpthread src/server.c -I./headers -o bin/server
	gcc -std=gnu99 -lpthread src/client.c -I./headers -o bin/client

clean:
	rm bin/server




