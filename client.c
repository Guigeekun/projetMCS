#include  "shared.h"

int main(int c,char* v[] ) {
    int sa; 
    struct sockaddr_in svc; 
    // Création de la socket pour envoi de la requête
    CHECK(sa=socket(PF_INET, SOCK_STREAM  , 0), "Can't create");

    // Préparation de l’adressage du service à contacter 
    svc.sin_family = PF_INET;
    svc.sin_port   = htons(atoi(v[2])); 
    svc.sin_addr.s_addr = inet_addr(v[1]); 
    memset(&svc.sin_zero, 0, 8); 
    // Demande d’une connexion au service 
    CHECK(connect(sa, (struct sockaddr *)&svc, sizeof(svc)) , "Can't connect");
    // Dialogue avec le serveur
    com(sa,svc);
}

void com(int sd,struct sockaddr_in svc){
    char addr[15];
    int port;
    char reponse[MAX_BUFF];
    printf("attente du mode\n");
    while(1){
        if(read(sd,reponse,sizeof(reponse))=='1'){ //le serveur a notifier (1) donc mode serveur
        printf("mode serv\n");
         serverMode(sd,svc);
     }
        if(read(sd,reponse,sizeof(reponse))=='2'){ //le serveur a notifier (2) donc mode serveur
        printf("mode client\n");
             write(sd,1,sizeof(1));
             read(sd,reponse,sizeof(reponse)); //reception de l'adresse
             strcpy(addr,reponse);
             write(sd,2,sizeof(2));           // le ack est à 2 pour eviter qu'il soit confondu avec le premier
             close(sd);
             clientMode(addr);
     }
    }
}

void clientMode(char addr){ // le port est fixé à PORT_SVC
    char reponse[MAX_BUFF];
    int sh;
    struct sockaddr_in svc;
    printf("communication coté client\n");
    CHECK(sh=socket(PF_INET, SOCK_STREAM  , 0), "Can't create");

    //connection avec le serv de jeu
    svc.sin_family = PF_INET;
    svc.sin_port   = htons(PORT_SVC);  // le port est fixé à PORT_SVC
    svc.sin_addr.s_addr = inet_addr(addr); 
    memset(&svc.sin_zero, 0, 8); 
    // Demande d’une connexion au service 
    CHECK(connect(sh, (struct sockaddr *)&svc, sizeof(svc)) , "Can't connect");
    printf("conection réussi\n");
    write(sh,1,sizeof(1));

}

void serverMode(int sd,struct sockaddr_in svc){
    char reponse[MAX_BUFF];
    while(read(sd, reponse, sizeof(reponse))!=1){ //attente du client
        printf("waiting for player 2\n");
    }
    printf("Connection established - starting the game\n");
    //debut de la partie

}

int printBoard(){ // fonction en cours de construction dans tableau.c
    //   7 colonne et on bloque la limite du jeu à 100 ligne (à gérer plus tard)
    //la variable board contient uniquement les jetons alors que boardAff contient aussi les element graphique du plateau
    //ici on doit creer le plateau à afficher à partir du tableau board ne contenant que les jetons
    
    }
