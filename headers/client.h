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

static bool quit = false;
int error_indentifier; // Returns the error code from getaddrinfo()
int socket_identifier;
struct addrinfo hints;
struct addrinfo *result, *rp;

void check_inputs(int argc);
int establish_connection(char *host, char *portNum);
void close_client();

