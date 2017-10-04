#include "client.h"

int main(int argc, char *argv[]){

	check_inputs(argc);

	signal(SIGINT, close_client);

	check_inputs(argc);

	establish_connection(argv[1], argv[2]);

	write(socket_identifier, "Client Connected\n", 30);

	while(1){ // Change to something better


	}


	write(socket_identifier, "Client Connected\n", 30);

	return EXIT_SUCCESS;
}


void check_inputs(int argc){
	// Print an error if the user has not provided the correct number of arguments
	if (argc != 3) {
        	printf("Usage: ./client <hostname> <port>\n");
        	exit(EXIT_FAILURE);
	}
}


int establish_connection(char *host, char *portNum){

	// Comparable values for getaddrinfo()
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;
	hints.ai_flags = 0;

	// Test address information from the server
	if ((error_indentifier = getaddrinfo(host, portNum, &hints, &result)) != 0) {
		printf("Address info could not be found: %s\n", gai_strerror(error_indentifier));
	}

	// Attempt to conenct to each address from the list
	for (rp = result; rp != NULL; rp = rp->ai_next) {

		// Attempt to create socket
		if ((socket_identifier = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol)) == -1) {
			continue; // Socket creation failed
		}

		// Establish connection using opened socket
		if (connect(socket_identifier, rp->ai_addr, rp->ai_addrlen) == 0) {
			break; // Connection established
		}

		close(socket_identifier); // Connection failed
	}

	if (rp == NULL) { // No connections
		printf("Failed to make connection.\n");
		exit(EXIT_FAILURE);
	}


}

void close_client(){
	exit(EXIT_SUCCESS);
}





