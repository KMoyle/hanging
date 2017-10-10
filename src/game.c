#include "game.h"


bool read_hangman_list(){

	char line[287];
	
	FILE *pf = NULL;

	pf = fopen("bin/hangman_text.txt", "r");

	int i = 0;

	while ( ( fgets ( line, sizeof ( line), pf))) {
		sscanf ( line, "%30[^ ,\n\t],%30[^ ,\n\t]", words[i].word_a, words[i].word_b);	
		i++;
   	}

	fclose(pf);

	return 0; 
}

int get_word_lengths(Word words){
	int words_length = strlen(words.word_a) + strlen(words.word_b);
	return words_length;
}

int calculate_num_guesses(int words_length){
	int case1 = words_length + 10;
	int case2 = 26;
	
	if (case1 < case2){
		return case1;
	} else{
		return case2;
	}
}

int pick_random_words(){
	int min = 0;
	int max = 287;	
	srand(time(NULL));
	double scaled = (double)rand()/RAND_MAX;
	int previous_random_index = (max - min +1)*scaled + min;	
	int random_index = (max - min +1)*scaled + min;	
	while (random_index == previous_random_index){
		scaled = (double)rand()/RAND_MAX;
		random_index = (max - min +1)*scaled + min;	
	}
	return random_index;
}



/********************************************************************************************************************/

/**************************************** Below is for testing purposes only ****************************************/

/********************************************************************************************************************/

int main(int argc, char *argv[]){
	read_hangman_list();
	//printf("%s\n", words[0].word_b);
	//Word test = pick_random_words();
	//printf("%s, %s\n", test.word_a, test.word_b);
	int test = pick_random_words();
	printf("%d\n", test);
}

//  Compile using:
//  gcc -std=gnu99 -pthread src/game.c -I./headers -o bin/game
//  ./bin/game








