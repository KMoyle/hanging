#include "leaderboard.h"


leaderboard* leaderboard(){

	Leaderboard* l = malloc(sizeof(Leaderboard));

	l->active_users = 0;

	return l;
}

void add_leaderboard(player* p){
	
	//have an instance of player and add them to the leaderboard (order logic) 

}
void update_scores(client_t* client, player* p){

	// checks for a win, compare names and updates 
	// compare names and update accordingly 
}

char* return_leaderboard(Leaderboard* l){

	//generate the display for the leaderboard including all active users

}
