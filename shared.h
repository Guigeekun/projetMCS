/* ------------------------------------------------------------------------ */
/**
 *  \file      shared.c
 *  \brief     Variables global pour Puissance 4
 *
 *  \author     Lucas Dorczysnki & Guilleme Benoit
 *
 *  \date       decembre 2019
 *
 *  \version    1.0
 *
 *  
 */

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

#define OK "1" 
#define OK2 "2"
#define ACK "-1"
#define Col0 "0"
#define Col1 "1"
#define Col2 "2"
#define Col3 "3"
#define Col4 "4"
#define Col5 "5"
#define Col6 "6"
#define LIG 6
#define COL 7
#define MAX_BUFF 2048
char buffer[MAX_BUFF];
char tab[COL][LIG];
int remplissage[7];
int choixC;
