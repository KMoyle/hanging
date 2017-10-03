/*
  	   CAB403 Assignment
 
      By Michael Bell & Kyle Moyle
*/

#include "server.h"

#define BUF_SIZE 500

int main(int argc, char *argv[])
{
	int sfd, nfd, s;
	struct addrinfo hints;
        struct addrinfo *result, *rp;
        char buf_rec[BUF_SIZE];
	char buf_snd[BUF_SIZE];
	

	// Get port number for server to listen on
	if (argc != 2) {
		fprintf(stderr,"usage: client port_number\n");
		exit(1);
	}

	memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
        hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
        hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
        hints.ai_protocol = 0;          /* Any protocol */
        hints.ai_canonname = NULL;
        hints.ai_addr = NULL;
        hints.ai_next = NULL;

	s = getaddrinfo(NULL, argv[1], &hints, &result);
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
	if (listen(sfd, 10) == -1) {
		perror("listen");
		exit(1);
	}

	printf("server starts listnening ...\n");

	/* repeat: accept, send, close the connection */
	/* for every accepted connection, use a sepetate process or thread to serve it */
	
	while(1) {  /* main accept() loop */
		
		//accepts a new connection
		if ((nfd = accept(sfd, rp->ai_addr, &rp->ai_addrlen)) == -1) {
			perror("accept");
			continue;

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

