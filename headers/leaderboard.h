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
	
	char name[USER_MAX];
	int games_played;
	int games_won;
	struct player *next;

}player;

typedef struct {
	
	int active_users;

}Leaderboard;


leaderboard* leaderboard();
void add_leaderboard(player* p);
void update_leaderboard(Leaderboard* l, player* p);
void update_scores(Leaderboard* l, player* p)
char* return_leaderboard(Leaderboard* l);

