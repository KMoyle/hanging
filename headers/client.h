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
