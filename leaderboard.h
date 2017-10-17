#include <errno.h>  
#include <signal.h>       
#include <stdbool.h>
#include <stdio.h>    
#include <netdb.h>          
#include <netinet/in.h>  
#include <pthread.h>
#include <sys/socket.h>  
#include <sys/types.h>   
#include <unistd.h>        
#include <stdlib.h>
#include <string.h>


#define BUFFER_SIZE 256
#define USER_MAX 10

typedef struct {

	int games_played;
	int games_won;
	char name[USER_MAX];

}player;

typedef struct {

	int active_users;

}Leaderboard;


leaderboard* leaderboard();
void update_leaderboard(Leaderboard* leaderboard, client_t* username);
char* return_leaderboard(Leaderboard* leaderboard);

