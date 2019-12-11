#include  "shared.h"


int main() {
        int se ,sd;
        pid_t pid;
        struct sockaddr_in svc,clt;
        socklen_t cltLen;
 // Création de la socket de réception d’écoute des appels 
        CHECK(se=socket(PF_INET, SOCK_STREAM, 0), "Can't create");

        // Préparation de l’adressage du service (d’appel) 
        svc.sin_family = PF_INET; 
        svc.sin_port   = htons (PORT_SVC);
        svc.sin_addr.s_addr = INADDR_ANY; 
        memset(&svc.sin_zero, 0, 8); 

        // Association de l’adressage préparé avec la socket d’écoute
        CHECK(bind(se, (struct sockaddr *) &svc, sizeof(svc)) , "Can't bind");

        // Mise en écoute de la socket 
        CHECK(listen(se, 5) , "Can't calibrate");

        // Boucle permanente de service 
        while (1) {
                //  Attente d’un appel
                cltLen = sizeof(clt);
                CHECK(sd=accept(se, (struct sockaddr *)&clt, &cltLen) , "Can't connect");
                pid = fork();
                if(pid==0){
                        // Dialogue avec le client
                        partie (sd , clt);
        }
        close(sd);

    }
    shutdown(se,2);
    return 0;
}
void partie(int sd, struct sockaddr_in clt) {
        char reponse[MAX_BUFF];
}