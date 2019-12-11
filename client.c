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
    connected(sd,svc);
}
void connected(int sd,struct sockaddr_in svc){
    char reponse[MAX_BUFF];

}