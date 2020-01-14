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

void com(int sd,struct sockaddr_in svc){ // differencie le server et le client et entame leur connexion, ferme la connexion avec le server de matchmaking
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
                                read(sd,buffer,sizeof(buffer)); // lecture de l'addresse
                                strcpy(addr,buffer);
                                printf("reception addr\n");
                                write(sd,OK2,sizeof(OK2)+1);   // le ack est à 2 pour eviter qu'il soit confondu avec le premier
                             //   read(sd,buffer,sizeof(buffer)); //lecture du port
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
           game(2,2,sh);
    
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
            game(1,1,sd);
    

}

void game(int joueur,int mode,int sock){ //le mode correspond au joueur à qui c'est le tour de jouer
    int colonne,ligne;
    creationTableau();
    while(1){ //chaque iteration correspond au tour d'un joueur
        switch (mode)
        {
        case 1: // le joueur[x,1] est en train de jouer
            printf("tour de jouer");
            colonne=saisirCoup(joueur);
            ligne=remplissage[colonne];
            tab[colonne][ligne]='0';
            remplissage[colonne]=remplissage[colonne]+1;
            creationTableau();
            write(sock,colonne,sizeof(colonne)); // pour faciliter l'envoie, on ne communique que la colonne et l'autre joueur calcul la ligne
            if(partieGagnante(colonne,ligne)==1){
                while(1);
            }
            mode=2;
            break;
        
        case 2: // le joueur[x,2] attend pour jouer 
            read(sock,buffer,sizeof(buffer));
            colonne=buffer;
            ligne=remplissage[colonne];
            tab[colonne][ligne]='0';
            remplissage[colonne]=remplissage[colonne]+1;
            creationTableau();
            if(partieGagnante(colonne,ligne)==1){
                while(1);
            }
            mode=1;
            break;
        }
    }
}

int creationTableau(){  //crée le tableau de jeu
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
}
    
int saisirCoup(int joueur) //permet au joueur de choisir une colonne (avec verification de la jouabilité)
{

    //ici parametre int qui permet de differencier j1 et j2
	int choixC;
	do{
printf ("Veuillez entrer le numéro de colonne pour le jeton mettez une autre colonne si celle ci est remplie\n");
	scanf("%d",&choixC);
printf("Vous voulez mettre votre jeton  dans  la colonne %d\n",choixC);
	if(jouable(choixC)==1)
	{
		
		return choixC;
	}

	}while(jouable(choixC)!=1);
}

int jouable(int x) //permet de verifier si une colonne est jouable
{
	if(x>0 &&(x<7)&&remplissage[x]>=0 && remplissage[x]<6)
    {
    
    return 1;
    }
	
	else {
       
    return 0;
    }
}

int partieGagnante(int c, int l) // vérifie si un coup fait gagner le joueur
{
    if  ((calculNBJetons(c,l,0,1)+calculNBJetons(c,l,0,-1))>=3 ||
  (calculNBJetons(c,l,1,0)+calculNBJetons(c,l,-1,0))>=3 ||
  (calculNBJetons(c,l,1,1)+calculNBJetons(c,l,-1,-1))>=3 ||
  (calculNBJetons(c,l,1,-1) + calculNBJetons(c,l,-1,1)>=3))
  return 1;
  else return 0;
}

int calculNBJetons(int c,int l, int dirV, int dirH)
{
    int jeton=0;
    if(dirV==0)// si on reste sur la même ligne
    {
        if(dirH==1)
        {
            while((tab[l][c])==(tab[l][c+1])&&(tab[l][c]!=' '))// calcul des jetons en horizontale droite de 0 vers 7
            {
                jeton++;
                c++;
            }
        }
        else if(dirH==-1)
        {
            while((tab[l][c])==(tab[l][c-1])&&(tab[l][c]!=' ')) // calcul des jetons en horizontale gauche de 7 vers 0
            {
                jeton++;
                c--;
            }
        }

    }
    if(dirV==1)// Si on change de ligne (on monte)
    {
        if(dirH==0)// on reste dans la même colonne 
        {
            while((tab[l][c])==(tab[l+1][c])&&(tab[l][c]!=' '))// calcul des jetons en vertical de 0 vers 6
            {
                jeton++;
                l++;
            }
        }
        else if(dirH==1) // on change de colonne
        {
            while((tab[l][c])==(tab[l+1][c+1])&&(tab[l][c]!=' '))//calcul des jetons de manière diagonale (haut -droite) de 0 vers 7
            {
                jeton++;
                c++;
                l++;
            }
        }
        else if(dirH==-1)
        {
            while((tab[l][c])==(tab[l+1][c-1])&&(tab[l][c]!=' ')) //calcul des jetons de manière  diagonale (bas-droit vers haut-gauche)
            {
                jeton++;
                c--;
                l++;
            }
        }
    }
    if(dirV==-1) //si on change de ligne (on descend)
    {
        if(dirH==0) // on reste dans la même colonne
        {
            while((tab[l][c])==(tab[l-1][c])&&(tab[l][c]!=' '))// calcul des jetons verticaux bas (de haut en bas)
            {
                jeton++;
                l--;
            }

        }
        else if(dirH==-1)
        {
            while((tab[l][c])==(tab[l-1][c-1])&&(tab[l][c]!=' '))// calcul des jetons diagnaux haut-droit vers bas-gauche
            {
                jeton++;
                c--;
                l--;
            }
        }
        else if(dirH==1)
        {
            while((tab[l][c])==(tab[l-1][c+1])&&(tab[l][c]!=' '))// calculs des jetons diagonaux (haut-gauche vers bas-droit)
            {
                jeton++;
                c++;
                l--;

            }
        }
    }
    return jeton;
}