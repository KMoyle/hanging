#include "game.h"

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
	game.game_words = pick_random_words();
	game.guesses_allowed = calculate_num_guesses(game.game_words);
	game.guesses_remaining = game.guesses_allowed;
	game.guessed_characters[0] = '@'; // Dummy character for testing purposes
	//game.encoded_words = produce_encoded_text(game.guessed_characters, game.game_words);
}

/* Given an instance of a game and a guessed letter, do required processing for a guess */
void process_guess(Game game, char letter){
	// Decrement guesses remaining
	// Update array of guessed letters
	// Update array of decoded text
	// Call function to check if the game is finished
}


/* Given an array of guessed letters and set of Words, return the updated encoded text "_ _ _  _ _ _ _" */
char *produce_encoded_text(char *letters, Word words){
	char *encoded_text = malloc(sizeof(char) * get_word_lengths(words));
	// Implement:
	// - Convert words to single char array
	// - For each element in char array (besides space), if element is not in array of guessed letter turn it into an underscore
	return encoded_text;
}


/* Given the current game object, check if all guesses are used or words are complete, set a flag to say game is finished */
int check_completion(Game game){
	int flag = 0;
	
	// If encoded_text contains no underscores, set flag to 2 to indicate game has finished and player won (important this is 		done before checking guess count)

	// If remaining guess = 1 and flag != 2, set flag to 1 to indicate game has finished and player lost
	
	return flag;
}




/********************************************************************************************************************/

/**************************************** Below is for testing purposes only ****************************************/

/********************************************************************************************************************/

int main(int argc, char *argv[]){
	read_hangman_list();
	//printf("%s\n", words[0].word_b);
	//Word test = pick_random_words();
	//printf("%s, %s\n", test.word_a, test.word_b);
	//int test = pick_random_words();
	//printf("%d\n", test);
}

//  Compile using:
//  gcc -std=gnu99 -pthread src/game.c -I./headers -o bin/game
//  ./bin/game








