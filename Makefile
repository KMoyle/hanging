all:
	gcc -std=gnu99 -pthread src/server.c -I./headers -o bin/server
	gcc -std=gnu99 -pthread src/client.c -I./headers -o bin/client
	gcc -std=gnu99 -pthread src/game.c -I./headers -o bin/game

clean:
	rm bin/server




