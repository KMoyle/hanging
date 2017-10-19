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

char* get_interface(Leaderboard* l, char *clientname){
	
	char leaderboard_container[BUFFER_SIZE];
	char *leaderboard_interface = (char *) malloc(BUFFER_SIZE);
	
	player *current_player;

	current_player = malloc(sizeof(player));

	memset(leaderboard_container, 0, sizeof(leaderboard_container));
	//while(1){}
	//current_player = l->first;
	
	leaderboard_container[0] = '\n'; 
	
	for(int i = 1; i < 50; i++){
	
		leaderboard_container[i] = '=';
	}

	leaderboard_container[51] = '\0'; 
	
	strcat(leaderboard_interface, leaderboard_container);
	
	
	sprintf(leaderboard_container, "\n\nPlayer  - %s\nNumber of games won  - %d\nNumber of games played  - %d\n\0",current_player->name, current_player->games_won, current_player->games_played);
	
	strcat(leaderboard_interface, leaderboard_container);	

	for(int i = 1; i < 50; i++){
	
		leaderboard_container[i] = '=';
	}

	leaderboard_container[51] = '\0'; 
	
	strcat(leaderboard_interface, leaderboard_container);

	
}
