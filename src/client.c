#include "client.h"

int main(int argc, char *argv[]){
	
    int error_indentifier; // Returns the error code from getaddrinfo()
    int socket_identifier;
    struct addrinfo hints;
    struct addrinfo *result, *rp;

    // Print an error if the user has not provided the correct number of arguments
    if (argc != 3) {
        printf("Usage: ./client <hostname> <port>\n");
        exit(EXIT_FAILURE);
    }

    // Comparable values for getaddrinfo()
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;
    hints.ai_flags = 0;

    // Test address information from the server
    if ((error_indentifier = getaddrinfo(argv[1], argv[2], &hints, &result)) != 0) {
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

    // While connection remains open
        // send & receive data using send & recv OR write & read

    // Close connection using close() system call
	while(!quit){
		printf("Connection Successful\n");

	}


    return EXIT_SUCCESS;
}
