#include "leaderboard.h"

// initialises leaderboard structure
Leaderboard* leaderboard(){

	Leaderboard* l = malloc(sizeof(Leaderboard));

	l->active_users = 0;
	l->first = NULL;
	l->last = NULL;

	return l;
}
//th is function retrives the players score, used to update the scoreboard
player* get_users_score(char *clientname, Leaderboard *l){

	player *players_score = l->first;

	if(players_score != NULL){
		if(players_score->name == clientname){
			return players_score;
		}
	}
		
	return NULL;

}

//add you player to leaderboard
player* add_to_leaderboard(char *clientname, Leaderboard *l){
	
	//have an instance of player and add them to the leaderboard  

	player *new_player;

	new_player = malloc(sizeof(player));

	strcpy(new_player->name, clientname);

	new_player->games_won = 0;
	new_player->games_played = 0;

	if(l != NULL){
		new_player->next = l->first;
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
void update_scores(Leaderboard* l, char *clientname, int new_player ){

	// checks for a win, compare names and updates 
	// compare names and update accordingly 
	
	player *p;

	if(new_player == 1){
		p = get_users_score(clientname, l);
	}else{
		p = add_to_leaderboard(clientname, l);
	}

	p->games_played += 1;
	p->games_won +=1;

}



//arrange the players due to scores
void arrange_leaderboard(Leaderboard* l){

	//logic to sort leaderboard

}
