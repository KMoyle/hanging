/*
  	   CAB403 Assignment
 
      By Michael Bell & Kyle Moyle
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <sys/wait.h> 
#include <unistd.h>
#include <errno.h>
#include <netdb.h>     

#define DEFAULT_PORT    12345
#define BUF_SIZE        500
#define QUE_LENGTH	10

const char *WELCOME_MESSAGE = "\n"
                              "=============================================\n"
                              "\n"
			      "\n"
                              "Welcome to the Online Hangman Gaming System\n"
                              "\n"
			      "\n"
                              "=============================================\n"
                              "\n";

const char *LOGIN = "You are required to logon with your username and password\n";
const char *USERNAME = "\nPlease enter your username-->";
const char *PASSWORD = "\nPlease enter your password-->";




