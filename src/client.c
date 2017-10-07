#include "client.h"

int main(int argc, char *argv[]){

	check_inputs(argc);

	signal(SIGINT, close_client);

	check_inputs(argc);

	socket_identifier = establish_connection(argv[1], argv[2]);

	pthread_t recieve_thread;
	pthread_t send_thread;


	if (pthread_create(&send_thread, NULL, send_socket, (void *) &socket_identifier) != 0) {
        	perror("Could not create send thread");
        	exit(EXIT_FAILURE);
    	}

	if (pthread_create(&recieve_thread, NULL, recieve_socket, (void *) &socket_identifier) != 0) {
        	perror("Could not recieving send thread");
        	exit(EXIT_FAILURE);
	}

	if (pthread_join(send_thread, NULL) != 0) {
        	perror("Could not join send thread");
        	exit(EXIT_FAILURE);
   	}

    	if (pthread_join(recieve_thread, NULL) != 0) {
        	perror("Could not join recieve thread");
        	exit(EXIT_FAILURE);
    	}



	close(socket_identifier);

	exit(EXIT_SUCCESS);
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
	
	return socket_identifier;

}


int get_user_input(char *message, char *input)
{
    int input_length;
    char *new_line;

    printf("%s", message);
    fgets(input, BUFFER_LENGTH, stdin);

    /* Replace the new line inserted by pressing the enter key with end of line. */
    if ((new_line = strchr(input, '\n')) != NULL) {
        *new_line = '\0';
    } else {
        /* If input is longer than BUF_SIZE, getchar to clear input stream */
        while (getchar() != '\n') { ; }
    }

    input = strlen(input) + 1;

    return input;
}


static void *send_socket(void *data)
{
    int     *socket_identifier;
    char    output_buffer[BUFFER_LENGTH];
    int     input_length;

    socket_identifier = (int *) data;

    while (!quit) {
        input_length = get_user_input("", output_buffer);

        if (write(*socket_identifier, output_buffer, input_length) != input_length) {
            perror("Could not send");
            exit(EXIT_FAILURE);
        }
    }

    pthread_exit(NULL);
}

static void *recieve_socket(void *data)
{
    int     *socket_identifier;
    char    recieve_bufffer[BUFFER_LENGTH];

    socket_identifier = (int *) data;

    for (;;) {
        if (read(*socket_identifier, recieve_bufffer, BUFFER_LENGTH) == -1) {
            perror("Could not read");
            exit(EXIT_FAILURE);
        }

        printf("%s", recieve_bufffer);
        fflush(stdout);
    }
}





void close_client(){
	exit(EXIT_SUCCESS);
}





