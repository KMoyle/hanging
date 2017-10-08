#include "client.h"

int main(int argc, char *argv[]){

	check_inputs(argc);

	signal(SIGINT, shutdown_client);

	check_inputs(argc);

	socket_identifier = establish_connection(argv[1], argv[2]);

	pthread_t recieve_thread, send_thread;


	if (pthread_create(&send_thread, NULL, send_data, (void *) &socket_identifier) != 0) {
        	perror("pthread_create");
        	close(EXIT_FAILURE);
   	}

	if (pthread_create(&recieve_thread, NULL, recieve_data, (void *) &socket_identifier) != 0) {
        	perror("pthread_create");
        	close(EXIT_FAILURE);
    	}

   	if (pthread_join(send_thread, NULL) != 0) {
        	perror("pthread_join");
        	close(EXIT_FAILURE);
	}

	if (pthread_join(recieve_thread, NULL) != 0) {
        	perror("pthread_join");
        	close(EXIT_FAILURE);
	}



	close(socket_identifier);

	close(EXIT_SUCCESS);
}


void check_inputs(int argc){
	if (argc != 3) {
        	printf("Usage: ./client <hostname> <port>\n");
        	close(EXIT_FAILURE);
	}
}


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


int obtain_input(char *msg, char *input_str)
{
    int input_len;
    char *new_line;

    printf("%s", msg);
    fgets(input_str, BUFFER_LENGTH, stdin);


    if ((new_line = strchr(input_str, '\n')) != NULL) {
        *new_line = '\0';
    } else {

        while (getchar() != '\n') { ; }
    }

    input_len = strlen(input_str) + 1;

    return input_len;
}


static void *send_data(void *data)
{
    int     *socket_identifier;
    char    send_buffer[BUFFER_LENGTH];
    int     input_len;

    socket_identifier = (int *) data;

    while (!close_client) {
        input_len = obtain_input("", send_buffer);

        if (write(*socket_identifier, send_buffer, input_len) != input_len) {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    pthread_exit(NULL);
}

static void *recieve_data(void *data)
{
    int     *socket_identifier;
    char    recieved_buffer[BUFFER_LENGTH];

    socket_identifier = (int *) data;

    for (;;) {
        if (read(*socket_identifier, recieved_buffer, BUFFER_LENGTH) == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        if (strcmp(recieved_buffer, DISCONNECT_FLAG) == 0) {
            printf("\nServer has disconnected\n");
            close_client = true;
            pthread_exit(NULL);
        }

        printf("%s", recieved_buffer);
        fflush(stdout);
    }
}





void shutdown_client(){
	exit(EXIT_SUCCESS);
}





