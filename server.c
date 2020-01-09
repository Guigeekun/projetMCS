#include  "shared.h"

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
        CHECK(bind(se, (struct sockaddr *) &svc, sizeof(svc)) , "Can't bind")
        // Mise en écoute de la socket 
        CHECK(listen(se, 5) , "Can't calibrate");
        // Boucle permanente de service 
        while (1) {
                //  Attente d’un appel
                socklen_t cltLen = sizeof(clt);
                socklen_t clt2Len = sizeof(clt2);
                printf("En attente player 1\n");
                CHECK(sd=accept(se, (struct sockaddr *) &clt, &cltLen) , "Can't connect");
 
                printf("waiting for player 2\n");
                CHECK(sd2=accept(se, (struct sockaddr *) &clt2, &clt2Len) , "Can't connect");
                printf("players ready\n");
                com(sd,clt,sd2,clt2);
                close(sd);
                close(sd2);

        }
        shutdown(se,2);
        return 0;
}
void com(int sd, struct sockaddr_in clt,int sd2, struct sockaddr_in clt2) {
        char* ack=OK;
        char* ack2=OK2;
        char reponse[MAX_BUFF];
        
        printf("debut communication\n");

        CHECK(write(sd,&ack,sizeof(ack)+1),"can't write"); //notifie au joueur 1 qu'il est en mode serveur (1)
        CHECK(write(sd2,&ack2,sizeof(ack2)+1),"can't write"); //notifie au joueur 2 qu'il est en mode client (2)


        printf("notif done\n");

        printf("%s\n",ack);
        printf("%s\n",ack2);

        read(sd2,reponse,sizeof(reponse));
        while(atoi(reponse)!=ack){ //attente d'ack du client
                read(sd2,reponse,sizeof(reponse));
                sleep(1);
        }

        write(sd2,clt2.sin_addr.s_addr,sizeof(clt2.sin_addr.s_addr)); //envoie de l'addr du serv au client
        read(sd2,reponse,sizeof(reponse));
        while(atoi(reponse)!=ack2){ //ack
                read(sd2,reponse,sizeof(reponse));
                sleep(1);
        }
}