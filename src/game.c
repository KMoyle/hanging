#include "game.h"

	int guesses = 0;
	int counter = 0;

/* Reads the hangman text file of words and stores all the words in a global array */
void read_hangman_list(){

	char line[287];
	
	FILE *pf = NULL;

	pf = fopen("bin/hangman_text.txt", "r");

	int i = 0;

	while ( ( fgets ( line, sizeof ( line), pf))) {
		sscanf ( line, "%30[^ ,\n\t],%30[^ ,\n\t]", words[i].word_a, words[i].word_b);	
		i++;
   	}

	fclose(pf);
}

/* Given a set of words, returns the total length of those two words combines */
int get_word_lengths(Word words){
	int words_length = strlen(words.word_a) + strlen(words.word_b);
	return words_length;
}

/* Given a set of words, returns the number of guesses given to that set */
int calculate_num_guesses(Word words_set){
	int case1 = get_word_lengths(words_set) + 10;
	int case2 = 26;
	
	if (case1 < case2){
		return case1;
	} else{
		return case2;
	}
}

/* Returns a random set of words from the list */
void pick_random_words(Game *game){
	Word result;
	double min = 0;
	double max = 287;	
	srand((unsigned) time(NULL));
	double scaled = (double)rand()/RAND_MAX;	
	double random_index = (max - min + 1)*scaled + min;
	game->game_words = words[(int) random_index];
}


/* Initialises all variables for a instance of a game */
void initialise_game(Game *game){
	//game.completion_flag = 0;
	pick_random_words(game);
	game->guesses_allowed = calculate_num_guesses(game->game_words);
	game->guesses_remaining = game->guesses_allowed;
	produce_encoded_text(game);
}

/* Given an instance of a game and a guessed letter, do required processing for a guess */
void process_guess(Game *game, char *letter){
	printf("Char is: %s\n", letter);
	strcat(game->guessed_characters, letter);
	game->guesses_remaining--;
}


/* Given an array of guessed letters and set of Words, return the updated encoded text i.e "_ _ _ _ _  _ _ _" */
void produce_encoded_text(Game *game){

	memset(game->encoded_words, 0, sizeof (game->encoded_words));

	int i = 0;
	for (;i < strlen(game->game_words.word_a); i++){	
		game->encoded_words[i] = '_';
	}
	game->encoded_words[i] = ' '; 
	i = strlen(game->game_words.word_a)+1;
	for (;i < strlen(game->game_words.word_b) + strlen(game->game_words.word_a)+1; i++){	
		game->encoded_words[i] = '_';
	}

	//printf("Game Words: %s %s\n", game->game_words.word_a, game->game_words.word_b);
	//printf("Encoded Words: %s\n", game->encoded_words);

	// Fill in guessed letters
	
	
	for(int i=0;i<strlen(game->game_words.word_a);i++){
		for (int j = 0; j<strlen(game->guessed_characters); j++){
			if(game->game_words.word_a[i] == game->guessed_characters[j]){	
				game->encoded_words[i] = game->guessed_characters[j];
			} 
		}
	}


	for(int i=0;i<strlen(game->game_words.word_b);i++){
		for (int j = 0; j<strlen(game->guessed_characters); j++){
			if(game->game_words.word_b[i] == game->guessed_characters[j]){	
				game->encoded_words[i + strlen(game->game_words.word_a) + 1] = game->guessed_characters[j];
			} 
		}
	}

	game->encoded_words[strlen(game->game_words.word_a) + strlen(game->game_words.word_b) + 1] = '\0';
	
	//printf("Encoded Words: %s\n", game->encoded_words);

}


/* Given the current game object, check if all guesses are used or words are complete, set a flag to say game is finished */
int check_completion(Game *game){
	char container[100];
	int flag = 0;
	sprintf(container, "%s %s", game->game_words.word_a,game->game_words.word_b);
	printf("container = %s\n", container);
	printf("enocoded words = %s\n", game->encoded_words);
	if (strcmp(container, game->encoded_words) == 0){
		flag = 2;

	}

	// If remaining guess = 1 and flag != 2, set flag = 1 to indicate game has finished and player lost
	if (game->guesses_remaining == 1 && flag != 2){
		flag = 1;
	}
	
	game->completion_flag = flag;
	return flag;
}

char* hangman_interface(Game *game){

	int divider = 31;
	char container[100]; 
	static char *interface;
	

	interface = (char *) malloc(BUF_SIZE);
	container[0] = '\n'; 

	for(int i = 1; i < divider-1; i++){
	
		container[i] = '-';
	}
	puts("--we here--");
	container[divider] = '\n'; 
	
	strcat(interface, container);
	puts("--we here--");
	sprintf(container, "\n\nGuessed letters: %s\n", game->guessed_characters);
	
	strcat(interface, container);
	
	sprintf(container, "\nNumber of guesses remaining: %d\n", game->guesses_remaining);

	strcat(interface, container);
	
	sprintf(container, "\nWord: %s\n", game->encoded_words);
	
	strcat(interface, container);

	sprintf(container, "\nEnter your guess -  ");

	strcat(interface, container);
	
	return interface;

	//printf("%s\n", interface);

}

/*

Steps on server side (I think):

		- Read the players guess
		- call process_guess(game, letter)
		- call check_completion(game)
	- Check what game.completion_flag equals and display relevent message
	- Update leaderboard
	- Deallocate memory used by that game object ??
	- Display main menu

*/


/********************************************************************************************************************/

/*  Below is a main function and compile instruction to test parts of code without integrating it with the server   */

/********************************************************************************************************************/
/*
int main(int argc, char *argv[]){
	read_hangman_list();
	Game game;
	initialise_game(game);

}*/

//  Compile using:
//  gcc -std=gnu99 -pthread src/game.c -I./headers -o bin/game
//  ./bin/game








