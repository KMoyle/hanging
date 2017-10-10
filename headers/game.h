#include <errno.h>  
#include <signal.h>       
#include <stdbool.h>
#include <stdio.h>    
#include <netdb.h>          
#include <netinet/in.h>  
#include <pthread.h>
#include <sys/socket.h>  
#include <sys/types.h>   
#include <unistd.h>        
#include <stdlib.h>
#include <string.h>

typedef struct{
	char word_a[20];
	char word_b[20];
}Word;

Word words[288];

typedef struct{	
	int guesses_allowed;
	int guesses_remaining;
	Word game_words;
	char encoded_words[40];
	char guessed_characters[26];
	int completion_flag;
}Game;	

void read_hangman_list();
int get_word_lengths(Word words);
int calculate_num_guesses(Word words);
Word pick_random_words();
void initialise_game(Game game);
void process_guess(Game game, char *letter);
char produce_encoded_text(Game game, Word words);
int check_completion(Game game);



































 
