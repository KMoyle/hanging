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

	return words; 
}




/********************************************************************************************************************/

/**************************************** Below is for testing purposes only ****************************************/

/********************************************************************************************************************/

int main(int argc, char *argv[]){
	read_hangman_list();
	printf("%s\n", words[287].word_b);
	
}

// Compile using:
// gcc -std=gnu99 -pthread src/game.c -I./headers -o bin/game








