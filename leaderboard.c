#include "leaderboard.h"


leaderboard* leaderboard(){

	Leaderboard* l = malloc(sizeof(Leaderboard));

	l->active_users = 0;

	return l;
}

void update_scores(client_t* client, player* p){

	// checks for a win, compare names and updates 

	
}

char* return_leaderboard(Leaderboard* l){

	//generate the display for the leaderboard including all active users

}
