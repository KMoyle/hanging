
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

#define DEFAULT_PORT    "12345"
#define BUF_SIZE        500
#define QUE_LENGTH	10
#define PORT_LENGTH	5

typedef struct addrinfo addrinfo;
typedef struct client_details client_t;
typedef struct node client_node_t;

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
		      "Unaurtherised to play"
		      "\n";
const char *MAIN_MENU = "\n"
			"=======MAIN MENU=======";

int passive_connection( addrinfo *rp, char *port);
int read_socket( int sfd, char *buf_rec );
void write_socket( int sfd, const char *buf_snd );
void insert_new_client( client_t* client);
int get_client_name(client_t* client);
int get_client_password(client_t* client);
void input_client_info( client_t* client );
bool authenticate_client(char *clientName, char *clientPassword);
bool client_( );
