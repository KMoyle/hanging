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
	player *first;
	player *last;

}Leaderboard;



Leaderboard* leaderboard(void);
player* get_users_score(char *clientname, Leaderboard *l);
player* add_to_leaderboard(char *clientname, Leaderboard *l);
void update_scores(Leaderboard* l, char *clientname, int games_played, int games_won );
void arrange_leaderboard(Leaderboard* l);
char* get_interface(Leaderboard* l, char *clientname, int games_played, int games_won);
