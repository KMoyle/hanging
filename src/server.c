
//  	     CAB403 Assignment
 
//      By Michael Bell & Kyle Moyle


#include "server.h"

int sfd, nfd, s;
struct addrinfo hints;
struct addrinfo *result, *rp;
char buf_rec[BUF_SIZE];
char buf_snd[BUF_SIZE];
char *port;
char clientPassword[6];
char clientName[6];
bool clientConnection = false;

typedef struct client client_t;
typedef struct client_node client_node_t;

struct client {
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

void client_login(){
	//TODO
}

void input_client_info( struct client* client){
	//TODO
}
	
int main(int argc, char *argv[])
{



	

	// Get port number for server to listen on, if not correct defalut is assigned
	if (argc == 2) {
		port = argv[1];
	}else{
		port = DEFAULT_PORT;
		printf("Incorrect port argument, assigned default %s\n\n",DEFAULT_PORT);
	}

	memset(&hints, 0, sizeof(struct addrinfo));
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

	for (rp = result; rp != NULL; rp = rp->ai_next) {
        	
		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
                if (sfd == -1){
                   continue;
		}
                if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0){
                   break;             
		}
               close(sfd);
         }
	 
	if (rp == NULL) {//No address succeeded
               fprintf(stderr, "Could not bind\n");
               exit(EXIT_FAILURE);
        }

        freeaddrinfo(result);// No longer needed

	//start listnening

	if (listen(sfd, QUE_LENGTH) == -1) {
		perror("listen");
		exit(1);
	}


	printf("server is now listnening ...\n\n");

	/* repeat: accept, send, close the connection */
	/* for every accepted connection, use a sepetate process or thread to serve it */
	
	for(;;){  /* main accept() loop */
		
		//accepts a new connection
		if ((nfd = accept(sfd, rp->ai_addr, &rp->ai_addrlen)) == -1) {
			perror("accept");
			continue;

		}
		printf("Successfull Connection\n");
		clientConnection = true;

		printf("Sending Welcome Message\n\n");
		
		//sending welcome msg to client
		write(nfd, WELCOME_MESSAGE, BUF_SIZE);	

		strcpy(clientPassword, "123456");
		strcpy(clientName, "Tom");

		/*if(clientPassword != "123456" && clientName != "Tom"){
			perror("Incorrect Login Details");
			exit(EXIT_FAILURE);
		}*/
		
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

