#define CHECK(sts,msg) if ((sts) == -1) {perror(msg);exit(-1);}
#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <signal.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <sys/wait.h>

#define PORT_SVC 7000
#define INADDR_SVC "127.0.0.1"

#define MAX_BUFF 1024
char buffer[MAX_BUFF]; 