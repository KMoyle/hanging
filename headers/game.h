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
	int guesses_used;
	int guesses_allowed;
	char word_one[20];
	char word_two[20];
	int length_word_one;
	int length_word_two;
	char encoded_word_one[20];
	char encoded_word_two;
}Game;	



























 
