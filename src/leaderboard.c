#include "leaderboard.h"

const char *LEADERBOARD_DIVIDER = "\n===================================================\n";

// initialises leaderboard structure
Leaderboard* leaderboard(){

	Leaderboard* l = malloc(sizeof(Leaderboard));

	l->active_users = 0;
	l->first = NULL;
	l->last = NULL;

	return l;
}
//this function retrives the players score, used to update the scoreboard, multiple clients
player* get_users_score(char *clientname, Leaderboard *l){

	player *players_score = l->first;

	if(players_score != NULL){
		if(players_score->name == clientname){
			return players_score;
		}
	}
		
	return NULL;

}

//add you player to leaderboard, multiple clients
player* add_to_leaderboard(char *clientname, Leaderboard *l){
	
	//have an instance of player and add them to the leaderboard  

	player *new_player;

	new_player = malloc(sizeof(player));

	strcpy(new_player->name, clientname);

	new_player->games_won = 0;
	new_player->games_played = 0;

	if(l != NULL){
		//new_player->next = l->first;
		l->first = new_player;
	}else{
		new_player->next = NULL;
		l->last = new_player;
		l->first = new_player;	
	}

	l->active_users++;

	return new_player;
}

//will update a users score after an instance of hangman
void update_scores(Leaderboard* l, char *clientname, int games_played, int games_won){

	// checks for a win, compare names and updates 
	// compare names and update accordingly 
	
	
	if(games_played > 1){
		
		//p = get_users_score(clientname, l);
	}else{

		//p = add_to_leaderboard(clientname, l);
	}

	//p->games_played = games_played;
	//p->games_won = games_won;

}



//arrange the players due to scores
void arrange_leaderboard(Leaderboard* l){

	//logic to sort leaderboard

}

char* get_interface(Leaderboard* l, char *clientname, int games_played, int games_won){
	
	char leaderboard_container[BUFFER_SIZE];

	char *leaderboard_interface = (char *) malloc(BUFFER_SIZE);
	
	memset(leaderboard_container, 0, sizeof(leaderboard_container));

	strcat(leaderboard_interface,LEADERBOARD_DIVIDER);
	
	sprintf(leaderboard_container, "\nPlayer  - %s\nNumber of games won  - %d\nNumber of games played  - %d\n",clientname, games_won, games_played);

	strcat(leaderboard_interface, leaderboard_container);  

	strcat(leaderboard_interface,LEADERBOARD_DIVIDER);
	//strcat(leaderboard_interface,leaderboard_container);

	return leaderboard_interface;
	
}
