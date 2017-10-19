
//  	      CAB403 Assignment
 
//      By Michael Bell & Kyle Moyle


#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <sys/wait.h> 
#include <unistd.h>
#include <errno.h>
#include <netdb.h>     

#include "game.h"
#include "leaderboard.h"

#define DEFAULT_PORT    "12345"
#define BUF_SIZE        256
#define QUE_LENGTH	10
#define PORT_LENGTH	5


typedef struct addrinfo addrinfo;
typedef struct client_details client_t;

struct client_details {

	int sfd;
	char clientName[6];
	char clientPassword[6];
	int games_played;
	int games_won;

};
	

const char *WELCOME_LOGIN_MSG = "\n"
                              "=============================================\n"
                              "\n"
			      "\n"
                              "Welcome to the Online Hangman Gaming System\n"
                              "\n"
			      "\n"
                              "=============================================\n"
                              "\n"
			      "You are required to logon with your register Username and Password\n";
const char *USERNAME = "\nPlease enter your username-->";
const char *PASSWORD = "\nPlease enter your password-->";
const char *UNAUTH = "\n"
		      "Unautherised to play"
		      "\n";
const char *MAIN_MENU = "\n"
			"=======MAIN MENU=======\n"
			"\n"
			"\n"
			"Please enter a selection\n"
			"<1> Play Hangman\n"
			"<2> Leaderboard\n"
			"<3> Quit Hangman\n"
			"\n"
			"\n"
			"Selection option 1-3 ->";
int passive_connection( addrinfo *rp, char *port);
void read_socket( int sfd, char *buf_rec );
void write_socket( int sfd, const char *buf_snd );
void get_client_name( client_t* client );
void get_client_password( client_t* client );
int get_menu_selection( client_t* client );
char* get_guess( Game *game, client_t* client);
//void input_client_info( client_t* client );
bool authenticate_client( char *clientName, char *clientPassword );
void client_( int sfd, client_t* client );
void return_leaderboard(Leaderboard* l, client_t* client);
int play_hangman( client_t* client);
