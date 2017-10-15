
//  	     CAB403 Assignment
 
//      By Michael Bell & Kyle Moyle


#include "server.h"

char buf_rec[BUF_SIZE];
char buf_snd[BUF_SIZE];
char buf[BUF_SIZE];

char *port;
char clientPassword[6];
char clientName[6];
bool clientConnection = false;

int pfd; //passive socket
int sfd;

int read_socket( int sfd, char *buf_rec ){
	
	//Receives a message from sfd
        if (recv(sfd, buf_rec, BUF_SIZE, 0) == -1) {
            	perror("receiving input");
            	exit(1);
        	}
	return 0;
}

void write_socket( int sfd, const char *buf_snd )
{

    if (send(sfd, buf_snd, BUF_SIZE, 0) == -1) {
        perror("writing output");
	exit(1);
    }
}
/*
void insert_new_client(client_t* client ){

	client_node_t *new_client = (client_node_t*) malloc(sizeof(client_node_t));
	
	memcpy(&new_client->client, client, sizeof(client_t));
	
	clients.tail = new_client;
}*/

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

int get_client_name(client_t* client){
	
	write_socket(client->sfd, USERNAME);

	if(read_socket(client->sfd, client->clientName) == -1){
		perror("cant read socket");
		return -1;
	}
	
	return 0;
}
int get_client_password(client_t* client){
	
	write_socket(client->sfd, PASSWORD);

	if(read_socket(client->sfd,client->clientPassword) == -1){
		perror("cant read socket");
		return -1;
	}
	
	return 0;
}

int get_menu_selection( client_t* client ){
	
	char menu_selection[BUF_SIZE];

	memset(menu_selection, 0, sizeof(menu_selection));
	
	write_socket(client->sfd, MAIN_MENU);
	
	if(read_socket(client->sfd, menu_selection) == -1){
		perror("cant read socket");
		return -1;
	}
	
	return atoi(menu_selection);	
	
}

char* get_guess( Game *game, client_t* client){


	if(read_socket(client->sfd, game->guessed_character) == -1){
		perror("cant read socket");		
	}
	
	printf("selected letter = %s\n", game->guessed_character);

	//process guess and change guess count
	process_guess(game, game->guessed_character);

	return game->guessed_character;	
	
}


bool client_( int sfd ){
	client_t* client = malloc(sizeof(client_t));
	client_node_t *client_list;
	bool win = false;
	int counter;

	client->sfd = sfd;

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
		
			return false;
		}
		counter = 1;
		//insert_new_client(client);
	}//end client info and authentication

	int menu_selection = get_menu_selection(client);
	printf("menu_selection %d\n",menu_selection);

	switch(menu_selection){

		case 1:
			win = play_hangman(client);
		break;

		case 2:
			//SHOW LEADERBOARD
		break;
		case 3:	
			//QUIT GAME	
		break;
	}
	
	return true;	 
	
}
bool play_hangman(client_t* client){

	Game* game = malloc(sizeof(Game));
	
	char container[100];
	static char *new_interface[BUF_SIZE];
	char *letter = NULL; //char to retrive guess
	game->completion_flag = 0;

	//memset(letter, 0, sizeof(letter));
	initialise_game(game);
		
	printf("--TESTS--\n");
	printf("Clients Words: %s %s\n", game->game_words.word_a, game->game_words.word_b);
	printf("Clients Encoded Words: %s\n", game->encoded_words);
	printf("Clients Guesses Allowed: %d\n", game->guesses_allowed);
	printf("Clients Guesses Remaining: %d\n", game->guesses_remaining);
	printf("Clients Guessed Characters: %s\n", game->guessed_characters);
	printf("Clients Completion Flag: %d\n", game->completion_flag);
	printf("--TESTS--");
	//while(1){}//Pause

	//Game loop
	while(game->completion_flag == 0){

		game->completion_flag = check_completion(game);
		
		*new_interface = hangman_interface(game);
		
		//send HM interface
		write_socket(client->sfd, *new_interface);
		
		letter = get_guess(game, client);
		printf("selected letter = %s\n", letter);
		
		produce_encoded_text(game);
		
	}
	if(game->completion_flag == 2){
		
		sprintf(container, "\nGame over\n\n\nWell done %s! You won this round of Hangman!\n", client->clientName);	
		write_socket(client->sfd, container);
		
		return true;
	}else if(game->completion_flag == 1){
				sprintf(container, "\nGame over\n\n\nBad Luck %s! You have run out of guesses. The Hangman got you!\n", client->clientName);	
		write_socket(client->sfd, container);
		return false;
	}

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


	
int main(int argc, char *argv[])
{
	int sfd, nfd;
	addrinfo rp;

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

	for(;;){  /* main accept() loop */
		
		//accepts a new connection
		if ((nfd = accept(pfd, rp.ai_addr, &rp.ai_addrlen)) == -1) {
			perror("accept");
			continue;

		}
		printf("Successfull Connection\n");
		clientConnection = true;

		printf("Sending Welcome Message\n\n");
		
		do{

			client_(nfd);
		

			
		}while(clientConnection);

		 //Receives a message from the new socket
        	if (recv(nfd, buf_rec, BUF_SIZE, 0) == -1) {
            		perror("receiving");
            		exit(EXIT_FAILURE);
        	}
		
		printf("%s\n", buf_rec);
		
		
		close(nfd); 

		while(waitpid(-1,NULL,WNOHANG) > 0); /* clean up child processes */
	}

}


