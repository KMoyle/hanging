
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

struct client_details {
	int sfd;
	char clientName[6];
	char clientPassword[6];
};
	
struct node {
	struct client_t *client;
	struct client_node_t *next;
	
};

struct client_list{
	struct node *head;
	struct node *tail;
	
}clients;



int read_socket( int sfd, char *buf_rec ){
	
	//Receives a message from sfd
        if (recv(sfd, buf_rec, BUF_SIZE, 0) == -1) {
            	perror("receiving input");
            	exit(EXIT_FAILURE);
        	}
	return 0;
}

void write_socket( int sfd, char *buf_snd )
{
    if (write(sfd, buf_snd, BUF_SIZE) == -1) {
        perror("writing output");
        exit(EXIT_FAILURE);
    }
}

void insert_new_client(client_t* client){

	struct client_node_t* new_client = malloc(sizeof(client_node_t));
	
	//new_client->next = NULL;

    	//memcpy(&new_client->client, client, sizeof(client_t));

   	//clients.tail = new_client;
}
/*
void authentication(char *clientName, char *clientPassword){
	
	
	FILE *fp = fopen("Authentication.txt", "r");
        char buf[BUF_SIZE];

	fgets(fp, buf, BUF_SIZE);

	while(fgets(fp, buf, BUF_SIZE)) {
        
        	//get client name and password
        	if (sscanf(buf, "%s %s", &new_client->clientName, &new_client->clientPassword) != 2)
            		fputs(stderr, "sscanf format error\n");
        
        insert_user(&new_user);
    }

    fclose(fp);

}*/

void client_(){
	//TODO
}

void input_client_info( client_t* client ){
	//TODO
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

	/* repeat: accept, send, close the connection */
	/* for every accepted connection, use a sepetate process or thread to serve it */
	
	for(;;){  /* main accept() loop */
		
		//accepts a new connection
		if ((nfd = accept(pfd, rp.ai_addr, &rp.ai_addrlen)) == -1) {
			perror("accept");
			continue;

		}
		printf("Successfull Connection\n");
		clientConnection = true;

		printf("Sending Welcome Message\n\n");
		
		//sending welcome msg to client
		write(nfd, WELCOME_LOGIN_MSG, BUF_SIZE);	


		
		while(clientConnection){

			//sending menu data
		}
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

//int establish_new_connection(){}

