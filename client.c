#include  "shared.h"

int main(int c,char* v[] ) {
    int sa,sd; 
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
    com(sd,svc);
}

void com(int sd,struct sockaddr_in svc){
    struct sockaddr add;
    int port;
    char reponse[MAX_BUFF];
    while(1){
        if(read(sd,reponse,sizeof(reponse))==1){
         serverMode(sd,svc);
     }
        if(read(sd,reponse,sizeof(reponse))==1){
             write(sd,3,1);
             add = read(sd,reponse,sizeof(reponse));
             write(sd,4,1);
             port = read(sd,reponse,sizeof(reponse));
             clientMode(sd,svc,add);
     }
    }
}

void clientMode(int sd,struct sockaddr_in svc,struct sockaddr_in addr,int port){
    char reponse[MAX_BUFF];
    //debut de la partie

}

void serverMode(int sd,struct sockaddr_in svc){
    char reponse[MAX_BUFF];
    while(read(sd, reponse, sizeof(reponse))!=1){
        printf("waiting for player 2");
    }
    //debut de la partie

}

int printBoard(char board[99][6]){ // 7 colonne et on bloque la limite du jeu à 100 ligne (à gérer plus tard)
    //la variable board contient uniquement les jetons alors que boardAff contient aussi les element graphique du plateau
    //ici on doit creer le plateau à afficher à partir du tableau board ne contenant que les jetons
    char boardAff[100][14];
    char boardAff[0]={"-","-","-","-","-","-","-","-","-","-","-","-","-","-","-"};
    for (size_t i = 0; i < 99; i++)
    {
        if(board[i]==NULL){

        }
    }
    


}
