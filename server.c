/* ------------------------------------------------------------------------ */
/**
 *  \file      server.c
 *  \brief     Server de matchmaking pour Puissance 4
 *
 *  \author     Lucas Dorczysnki & Guilleme Benoit
 *
 *  \date       decembre 2019
 *
 *  \version    1.0
 *
 *  
 */

#include  "shared.h"

/*************************************************************************************************************************************************************
 *                                                              PROTOTYPES DES FONCTIONS
 * */

void com(int,struct sockaddr_in,int,struct sockaddr_in );

//***********************************************************************************************************************************************************



/**
 *  \fn void com(int sd, struct sockaddr_in clt,int sd2, struct sockaddr_in clt2)
 *  \brief    Définie le mode des deux clients, leur envoie les infos de connexion client -> host
 * 
 *  \remark     OK est fixé à "1", Ok2 à "2" et ACK à "-1", voir shared.h
 * 
 *  \remark     Le port de l'host n'est pas libre, il est fixé à PORT_SVC+1
 * 
 *  \version    1.0
 * 
 * 		
 */

void com(int sd, struct sockaddr_in clt,int sd2, struct sockaddr_in clt2) {
        char reponse[MAX_BUFF];
        
        printf("debut communication\n");

        CHECK(write(sd, OK, strlen(OK)+1), "Can't write"); //notifie au joueur 1 qu'il est en mode serveur (1)
        CHECK(write(sd2, OK2, strlen(OK2)+1), "Can't write"); //notifie au joueur 2 qu'il est en mode client (2)

        read(sd2,reponse,sizeof(reponse));
        while(atoi(reponse)!=1){ //attente d'ack (OK) du client
                read(sd2,reponse,sizeof(reponse));
                sleep(1);
        }
        char addr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &clt.sin_addr, addr, INET_ADDRSTRLEN);
        write(sd2,addr,sizeof(addr)+1); //envoie de l'addr du serv au client
        printf("envoie addr\n");

        read(sd2,reponse,sizeof(reponse));
        while(atoi(reponse)!=-1){ //attente d'ack (ACK) du client
                read(sd2,reponse,sizeof(reponse));
                 printf("waiting for ack\n");
                sleep(1);
        }

  //      int port;
  //      port = ntohs(clt.sin_port);
  //      write(sd2,port,sizeof(port)+1); //envoie du port du serv au client
  //      printf("envoie port\n");

         printf("Job done, peut acceuillir d'autres clients\n\n");
}


int main() {
        int se ,sd,sd2;
        pid_t pid;
        struct sockaddr_in svc,clt,clt2;        
 // Création de la socket de réception d’écoute des appels 
        CHECK(se=socket(PF_INET, SOCK_STREAM, 0), "Can't create");

        // Préparation de l’adressage du service (d’appel) 
        svc.sin_family = PF_INET; 
        svc.sin_port   = htons (PORT_SVC);
        svc.sin_addr.s_addr = INADDR_ANY; 
        memset(&svc.sin_zero, 0, 8); 
        printf("Fin initiatlisation \n ");
        // Association de l’adressage préparé avec la socket d’écoute
        CHECK(bind(se, (struct sockaddr *) &svc, sizeof(svc)) , "Can't bind");
        // Mise en écoute de la socket 
        CHECK(listen(se, 5) , "Can't calibrate");
        // Boucle permanente de service 
        while (1) {
                //  Attente d’un appel
                socklen_t cltLen = sizeof(clt);
                socklen_t clt2Len = sizeof(clt2);
                printf("En attente du joueur 1\n");
                CHECK(sd=accept(se, (struct sockaddr *) &clt, &cltLen) , "Can't connect");
 
                printf("En attente du joueur 2\n");
                CHECK(sd2=accept(se, (struct sockaddr *) &clt2, &clt2Len) , "Can't connect");
                com(sd,clt,sd2,clt2);
                close(sd);
                close(sd2);

        }
        shutdown(se,2);
        return 0;
}

