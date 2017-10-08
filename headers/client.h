/*
  	   CAB403 Assignment
 
      By Michael Bell & Kyle Moyle
*/

#include <errno.h>  
#include <signal.h>       
#include <stdbool.h>
#include <stdio.h>    
#include <netdb.h>          
#include <netinet/in.h>  
#include <pthread.h>
#include <sys/socket.h>  
#include <sys/types.h>   
#include <unistd.h>        
#include <stdlib.h>
#include <string.h>

#define BUFFER_LENGTH            256
#define DISCONNECT_FLAG   "QUIT"

static bool close_client = false;
int error_indentifier;
int socket_identifier;
struct addrinfo hints;
struct addrinfo *result, *rp;

static void *send_data(void *socket_identifier);

static void *recieve_data(void *data);
int obtain_input(char *msg, char *input_str);

void check_inputs(int argc);
int establish_connection(char *host, char *portNum);
void shutdown_client();

