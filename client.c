#include  "shared.h"

void com(int,struct sockaddr_in);
void serverMode();
void clientMode(char addr[INET_ADDRSTRLEN]);

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
    char reponse[MAX_BUFF];
    int port;
    char addr[INET_ADDRSTRLEN];
    printf("attente du mode\n");

    while(1){
        read(sd, buffer, sizeof(reponse));
        switch (atoi(buffer)) {
                        case 1 :close(sd);
                                serverMode();
                                break;

                        case 2 :printf("mode client\n");
                                write(sd,OK,sizeof(OK)+1);
                                printf("envoie OK\n");
                                read(sd,buffer,sizeof(buffer)); // lecture de l'addresse
                                strcpy(addr,buffer);
                                printf("reception addr\n");
                                write(sd,OK2,sizeof(OK2)+1);   // le ack est à 2 pour eviter qu'il soit confondu avec le premier
                                printf("envoie OK2\n");
                                read(sd,buffer,sizeof(buffer)); //lecture du port
                               // strcpy(port, buffer);
                                close(sd);
                                clientMode(addr);
                                break;

                        default :   break;
                            }
    }
}

void clientMode(char addr[INET_ADDRSTRLEN]){ // le port est fixé à PORT_SVC
    char reponse[MAX_BUFF];
    int sh;
    struct sockaddr_in svc;
    printf("communication coté client\n");
    CHECK(sh=socket(PF_INET, SOCK_STREAM  , 0), "Can't create");

    //printf("%s\n",addr);
   // printf("%d\n",port);

    //connection avec le serv de jeu
    svc.sin_family = PF_INET;
    svc.sin_port = (htons(PORT_SVC+1));
    inet_pton(AF_INET, addr, &(svc.sin_addr));

    memset(&svc.sin_zero, 0, 8); 
    
    // Demande d’une connexion au service 
    printf("connect\n");
    CHECK(connect(sh, (struct sockaddr *)&svc, sizeof(svc)) , "Can't connect");
    printf("Connection established - starting the game\n");
    
    //debut de la partie
           game(2,sh);
    
}

void serverMode(){
    struct sockaddr_in svc,clt; 
    int se,sd;
    char reponse[MAX_BUFF];

    socklen_t cltLen = sizeof(clt);
    socklen_t svcLen = sizeof(svc);

    CHECK(se=socket(PF_INET, SOCK_STREAM, 0), "Can't create");

    printf("mode serv\n");
    svc.sin_family = PF_INET; 
    svc.sin_port   = htons (PORT_SVC+1);
    svc.sin_addr.s_addr = INADDR_ANY; 
    memset(&svc.sin_zero, 0, 8); 

    CHECK(bind(se, (struct sockaddr *) &svc, svcLen), "Can't bind");

    printf("waiting for player 2\n");
    CHECK(listen(se, 5) , "Can't calibrate");
    printf("listening\n");
    CHECK(sd=accept(se, (struct sockaddr *) &clt, &cltLen) , "Can't connect");

    printf("Connection established - starting the game\n");
    //debut de la partie
            game(2,sd);
    

}

void game(int mode,int sock){
    createBoard();
}

int createBoard(){ 
int i,j;
for (i=0;i<6;i++)
     {
        for (j=0;j<7;j++)
        {
             tab[i][j]=' ';
        }
     }


	for(i=1;i<6;i++)
    {
        printf("\t\t\t");
        printf("+-+-+-+-+-+-+-+");

        printf("\n");
        printf("\t\t\t");
        for (j=0;j<7;j++)

        printf("|%c",tab[5-i][j]);

        printf("|%d \n",i);// affiche les numéros horizontalement

   }
    if (i==6)
        printf("\t\t\t");
    printf("+-+-+-+-+-+-+-+");
    printf("\n");
    printf("\t\t\t");
    for(j=0;j<=6;j++)
    {
        printf(" %d",j);// affiche les numéro verticalement
    }
    printf("\n\n\t\t");
    
    while(1);
}
    
