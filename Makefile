all:
	gcc -std=gnu99 -pthread src/server.c src/leaderboard.c src/game.c -I./headers -o bin/server
	gcc -std=gnu99 -pthread src/client.c -I./headers -o bin/client

clean:
	rm bin/server




