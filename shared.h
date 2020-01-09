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

#define OK 1 
#define OK2 2
#define LIG 16
#define COL 15
#define MAX_BUFF 2048
char buffer[MAX_BUFF];
