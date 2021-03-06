#include "client.h"

int main(int argc, char *argv[]){
	
	check_inputs(argc);

	socket_identifier = establish_connection(argv[1], argv[2]);

	// Create threads for recieving and sending data
	pthread_t recieve_thread, send_thread;
	pthread_create(&send_thread, NULL, send_data, (void *) &socket_identifier);
	pthread_create(&recieve_thread, NULL, recieve_data, (void *) &socket_identifier);
	pthread_join(send_thread, NULL);
	pthread_join(recieve_thread, NULL);

	close(socket_identifier);

	close(EXIT_SUCCESS);
}

// Ensure arguments are correctly entered
void check_inputs(int argc){
	if (argc != 3) {
        	printf("Please enter: ./client <hostname> <port>\n");
        	close(EXIT_FAILURE);
	}
}

// Establish connection to client using socket programming
int establish_connection(char *host, char *portNum){


	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;
	hints.ai_flags = 0;


	if ((error_indentifier = getaddrinfo(host, portNum, &hints, &result)) != 0) {
		printf("Address info could not be found: %s\n", gai_strerror(error_indentifier));
	}


	for (rp = result; rp != NULL; rp = rp->ai_next) {

		if ((socket_identifier = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol)) == -1) {
			continue;
		}

		if (connect(socket_identifier, rp->ai_addr, rp->ai_addrlen) == 0) {
			break; 
		}

		close(socket_identifier);
	}

	if (rp == NULL) {
		printf("Failed to make connection.\n");
		close(EXIT_FAILURE);
	}
	
	return socket_identifier;

}

// Get input from user
int obtain_input(char *msg, char *input_str)
{
    int input_len;
    char *new_line;

    printf("%s", msg);
    fgets(input_str, BUFFER_LENGTH, stdin);


    if ((new_line = strchr(input_str, '\n')) != NULL) {
        *new_line = '\0';
    } else {

        while (getchar() != '\n') {}
    }

    input_len = strlen(input_str) + 1;

    return input_len;
}

// Send data to server
static void *send_data(void *data)
{
    int     *socket_identifier;
    char    send_buffer[BUFFER_LENGTH];
    int     input_len;

    socket_identifier = (int *) data;

    while (!close_client) {
        input_len = obtain_input("", send_buffer);
	write(*socket_identifier, send_buffer, input_len); 
    }

    pthread_exit(NULL);

}

// Recieve data from server
static void *recieve_data(void *data)
{
    int     *socket_identifier;
    char    recieved_buffer[BUFFER_LENGTH];

    socket_identifier = (int *) data;

    while (!close_client) {
	read(*socket_identifier, recieved_buffer, BUFFER_LENGTH);
	printf("%s", recieved_buffer);
        fflush(stdout);
    }

}


