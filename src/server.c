
//  	     CAB403 Assignment
 
//      By Michael Bell & Kyle Moyle


#include "server.h"

char buf_rec[BUFFER_SIZE];
char buf_snd[BUFFER_SIZE];
char buf[BUFFER_SIZE];
bool server_running = true; 
Leaderboard *leaderboard_obj;
char *port;
char clientPassword[6];
char clientName[6];
bool clientConnection = false;
int new_player;	

int pfd; //passive socket
int sfd;

void read_socket( int sfd, char *buf_rec ){
	//Receives a message from sfd
        if (recv(sfd, buf_rec, BUF_SIZE, 0) == -1) {
            	perror("receiving input");
        }
}

void write_socket( int sfd, const char *buf_snd ){

	if (send(sfd, buf_snd, BUF_SIZE, 0) == -1) {
        	perror("writing output");
	}
}

/*Given the clients name and passowrd, checks the Authentication.txt for equivilent*/
bool authenticate_client(char *clientName, char *clientPassword){
	
	FILE *fp;
	char auth_username[6];
	char auth_password[6];

	if((fp = fopen("bin/Authentication.txt", "r")) == NULL) {
		perror("fopen");
		return false;
	}

	while(fgetc(fp) != '\n');

	while(fscanf(fp, "%s %s\n", auth_username, auth_password) > 0) {

		if(strcmp(auth_username, clientName) == 0 && strcmp(auth_password, clientPassword) == 0) {
		return true;
		}
	}

	fclose(fp);
	return false; 

}

void get_client_name(client_t* client){
	
	write_socket(client->sfd, USERNAME);

	read_socket(client->sfd, client->clientName);

}
void get_client_password(client_t* client){
	
	write_socket(client->sfd, PASSWORD);

	read_socket(client->sfd, client->clientPassword);
	
}

int get_menu_selection( client_t* client ){
	
	char menu_selection[BUFFER_SIZE];

	memset(menu_selection, 0, sizeof(menu_selection));
	
	write_socket(client->sfd, MAIN_MENU);
	
	read_socket(client->sfd, menu_selection);

	return atoi(menu_selection);	
	
}

char* get_guess( Game *game, client_t* client){

	read_socket(client->sfd, game->guessed_character);

	printf("selected letter = %s\n", game->guessed_character);

	//process guess and change guess count
	process_guess(game, game->guessed_character);

	return game->guessed_character;	
	
}

//function to handle a client and their requests and game play
void client_( int sfd, client_t* client ){
	
	bool win = false;
	int counter;
	client->sfd = sfd;
	char* leaderboard_interface[BUFFER_SIZE];
	
	//to check if the client is new and needs to be authenticated
	if (counter != 1){

		memset(buf_rec, 0, sizeof(buf_rec));
		memset(buf_snd, 0, sizeof(buf_snd));

		//sending welcome msg to client
		write_socket(client->sfd, WELCOME_LOGIN_MSG);

		//get client name and password
		get_client_name(client);
		get_client_password(client);

		if(!authenticate_client(client->clientName, client->clientPassword)){
		
			printf("AUTH FAILED");
			write_socket(client->sfd, UNAUTH);
		
		}
		counter = 1;

	}//end client info and authentication

	int menu_selection = get_menu_selection(client);
	printf("menu_selection %d\n",menu_selection);

	if(menu_selection == 1){
		client->games_played++;
	
		win = play_hangman(client);
		
		if(win == 1){
			client->games_won++;
			//update_scores(leaderboard_obj, client->clientName, client->games_played, client->games_won);
		}

	}else if(menu_selection == 2){
			
		return_leaderboard(leaderboard_obj, client);
		
	}else if(menu_selection == 3){

		//needs to quit
	}else{
		//incorrect selection try again
	}	 
	
}
int play_hangman(client_t* client){

	Game* game = malloc(sizeof(Game));

	leaderboard_obj = leaderboard();
	
	char hangman_container[100];
	static char *new_interface[BUF_SIZE];
	char *letter = NULL; //char to retrive guess
	game->completion_flag = 0;
	strcpy(game->guessed_characters, "");

	memset(hangman_container, 0, sizeof(hangman_container));
	initialise_game(game);
		
	printf("Clients Words: %s %s\n\0", game->game_words.word_a, game->game_words.word_b);

	//Game loop
	while(game->completion_flag == 0){

		//build new hangman interface
		*new_interface = hangman_interface(game);
		
		//send HM interface
		write_socket(client->sfd, *new_interface);
		
		letter = get_guess(game, client);
		
		produce_encoded_text(game);
	
		game->completion_flag = check_completion(game);
		
	}

	if(game->completion_flag == 2){
		sprintf(hangman_container, "\nGame over\n\n\nWell done %s! You won this round of Hangman!\n", client->clientName);	
		write_socket(client->sfd, hangman_container);

		return 1;

	}else if(game->completion_flag == 1){
		sprintf(hangman_container, "\nGame over\n\n\nBad Luck %s! You have run out of guesses. The Hangman got you!\n", client->clientName);	

		write_socket(client->sfd, hangman_container);
		return 0;
	}

}

// this function packages up the leaderboard and returns for writing
void return_leaderboard(Leaderboard *l, client_t* client){

	static char *leaderboard_interface[BUFFER_SIZE];

	*leaderboard_interface = get_interface(l, client->clientName, client->games_played, client->games_won);

	write_socket(client->sfd, *leaderboard_interface);
}


int passive_connection(addrinfo *rp, char *port){
	
	int s;
	addrinfo hints, *result, *addr;


	memset(&hints, 0, sizeof(addrinfo));
        hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
        hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
        hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
        hints.ai_protocol = 0;          /* Any protocol */
        hints.ai_canonname = NULL;
        hints.ai_addr = NULL;
        hints.ai_next = NULL;

	s = getaddrinfo(NULL, port, &hints, &result);
        if (s != 0) {
        	fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
                exit(EXIT_FAILURE);
        }

	for (addr = result; addr != NULL; addr = addr->ai_next) {
        	
		sfd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
                if (sfd == -1){
                   continue;
		}
                if (bind(sfd, addr->ai_addr, addr->ai_addrlen) == 0){
                   break;             
		}
               close(sfd);
         }
	 
	if (addr == NULL) {//No address succeeded
               fprintf(stderr, "Could not bind\n");
               exit(EXIT_FAILURE);
        }

	//start listnening
	if (listen(sfd, QUE_LENGTH) == -1) {
		perror("listen");
		exit(1);
	}

        freeaddrinfo(result);// No longer needed

	*rp = *addr;

	return sfd;
}


void sigintHandler(int sig_num) {
	// Exit Gracefully
	server_running = false;
	close(pfd);
	exit(EXIT_SUCCESS);
}

	
int main(int argc, char *argv[])
{
	int sfd, nfd;
	addrinfo rp;
	client_t* client = malloc(sizeof(client_t));
	client->games_played = 0;
	client->games_won = 0;

	signal(SIGINT, sigintHandler);

	// Get port number for server to listen on, if not correct defalut is assigned
	if (argc == 2) {
		port = argv[1];
	}else{
		port = DEFAULT_PORT;
		printf("Incorrect port argument, assigned default %s\n\n",DEFAULT_PORT);
	}

	pfd = passive_connection(&rp, port);

	printf("server is now listnening ...\n\n");

	read_hangman_list();

	while(server_running){  /* main accept() loop */
		
		//accepts a new connection
		if ((nfd = accept(pfd, rp.ai_addr, &rp.ai_addrlen)) == -1) {
			perror("accept");
			continue;

		}
		printf("Successfull Connection\n");
		clientConnection = true;

		printf("Sending Welcome Message\n\n");
		
		do{
			client_(nfd, client);
		
		}while(clientConnection && server_running);
		
		
		close(nfd); 

	}

}


