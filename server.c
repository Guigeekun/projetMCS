#include  "shared.h"

int main() {
        int se ,sd,sd2;
        pid_t pid;
        struct sockaddr_in svc,clt,clt2;
        socklen_t cltLen,clt2Len;
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
                cltLen = sizeof(clt);
                clt2Len = sizeof(clt2);
                printf("En attente player 1\n");
                CHECK(sd=accept(se, (struct sockaddr *)&clt, &cltLen) , "Can't connect");
 
                printf("waiting for player 2\n");
                CHECK(sd2=accept(se, (struct sockaddr *)&clt2, &clt2Len) , "Can't connect");
                printf("players ready");
                close(sd);
                close(sd2);

        }
        shutdown(se,2);
        return 0;
}
void com(int sd, struct sockaddr_in clt,int sd2, struct sockaddr_in clt2) {
        char reponse[MAX_BUFF];
        printf("c'est parti!!!\n");
        CHECK(write(sd,1,1),"can't write"); //notifie au joueur 1 qu'il est en mode serveur
        CHECK(write(sd2,2,15),"can't write");
        while(read(sd2,reponse,sizeof(reponse))!=1){ //ack
                sleep(1);
        }
        write(sd2,clt2.sin_addr.s_addr,10);
        while(read(sd2,reponse,sizeof(reponse))!=1){ //ack
                sleep(1);
        }
        write(sd2,clt2.sin_addr.s_addr,10);
}