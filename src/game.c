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
int calculate_num_guesses(Word words){
	int case1 = get_word_lengths(words) + 10;
	int case2 = 26;
	
	if (case1 < case2){
		return case1;
	} else{
		return case2;
	}
}

/* Returns a random set of words from the list */
Word pick_random_words(){
	double min = 0;
	double max = 287;	
	srand((unsigned) time(NULL));
	double scaled = (double)rand()/RAND_MAX;	
	double random_index = (max - min + 1)*scaled + min;
	return words[(int) random_index];
}



/* Initialises all variables for a instance of a game */
void initialise_game(Game game){
	game.completion_flag = 0;
	game.game_words = pick_random_words();
	game.guesses_allowed = calculate_num_guesses(game.game_words);
	game.guesses_remaining = game.guesses_allowed;
	game.guessed_characters[0] = '@'; // Dummy character for testing purposes
	// Not sure how to go about next line with pointer etc.
	//game.encoded_words = produce_encoded_text(game, game.game_words);
}

/* Given an instance of a game and a guessed letter, do required processing for a guess */
void process_guess(Game game, char *letter){

	game.guessed_characters[guesses] = *letter;

	for(int i = 0; i < strlen(game.encoded_words); i++){
	
		if(*letter != game.encoded_words[i]){
	
			game.guesses_remaining--;
		}
	}

	guesses++;
}


/* Given an array of guessed letters and set of Words, return the updated encoded text i.e "_ _ _ _ _  _ _ _" */
char produce_encoded_text(Game game, Word words){

	for(int i = 0; i < strlen(game.encoded_words); i++){
		for(int j = 0; j < strlen(words.word_a); j++){
			
			if(game.guessed_characters[i] == words.word_a[j]){

				game.encoded_words[j] = game.guessed_characters[i];	
			}else{ 
				game.encoded_words[j] = '_';
			}
		}
		for(int k = 0; k < strlen(words.word_b); k++){

			if(game.guessed_characters[i] == words.word_b[k]){
				
				game.encoded_words[k] = game.guessed_characters[i];		
			}else{ 
				game.encoded_words[strlen(words.word_a)+k] = '_';
			}
		}	
	}
		
	return *game.encoded_words;	
}


/* Given the current game object, check if all guesses are used or words are complete, set a flag to say game is finished */
int check_completion(Game game){
	int flag = 0;
	
	// If encoded_text contains no underscores, set flag = 2 to indicate game has finished and player won 
	for(int j = 0; j < strlen(game.encoded_words); j++){
		if(game.encoded_words[j] == '_'){
			counter++;
		}
	}
	//if counter = 0 then correct word has been guessed an client wins
	if(counter == 0){
		flag = 2; //game one
	}

	// If remaining guess = 1 and flag != 2, set flag = 1 to indicate game has finished and player lost
	if (game.guesses_remaining == 1 && flag != 2){
		flag = 1;
	}
	
	game.completion_flag = flag;
	return flag;
}

/*

Steps on server side (I think):

	- call read_hangman_list() somewhere that will only be called once
	- for each time a client selects play hangman, create a new game object by calling Game game
	- after this call initialise_game(game)
	- start a while loop that continues while game.completion_flag == 0
		- Display all the current game data to player (guesses remaining, characters guessed, encoded text) by calling 			game.guesses_remaining etc
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








