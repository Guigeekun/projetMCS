#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LIG 6
#define COL 7
int i;
int j;
char tab[COL][LIG];
int remplissage[7];
int choixC;
void creationTableau();

int calcul(int c,int l, int dirV, int dirH)
{
    int jeton=0;
    if(dirV==0)
    {
        if(dirH==1)
        {
            while((tab[l][c])==(tab[l][c+1])&&(tab[l][c]!=' '))
            {
                jeton++;
                c++;
            }
        }
        else if(dirH==-1)
        {
            while((tab[l][c])==(tab[l][c-1])&&(tab[l][c]!=' '))
            {
                jeton++;
                c--;
            }
        }

    }
    if(dirV==1)
    {
        if(dirH==0)
        {
            while((tab[l][c])==(tab[l+1][c])&&(tab[l][c]!=' '))
            {
                jeton++;
                l++;
            }
        }
        else if(dirH==1)
        {
            while((tab[l][c])==(tab[l+1][c+1])&&(tab[l][c]!=' '))
            {
                jeton++;
                c++;
                l++;
            }
        }
        else if(dirH==-1)
        {
            while((tab[l][c])==(tab[l+1][c-1])&&(tab[l][c]!=' '))
            {
                jeton++;
                c--;
                l++;
            }
        }
    }
    if(dirV==-1)
    {
        if(dirH==0)
        {
            while((tab[l][c])==(tab[l-1][c])&&(tab[l][c]!=' '))
            {
                jeton++;
                l--;
            }

        }
        else if(dirH==-1)
        {
            while((tab[l][c])==(tab[l-1][c-1])&&(tab[l][c]!=' '))
            {
                jeton++;
                c--;
                l--;
            }
        }
        else if(dirH==1)
        {
            while((tab[l][c])==(tab[l-1][c+1])&&(tab[l][c]!=' '))
            {
                jeton++;
                c++;
                l--;

            }
        }
    }
    return jeton;
}


void creationTableau()
{
	int i, j;
	for(i=1;i<6;i++){
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

int grillePleine()
{
    int i,compteur=0;
    for(i=0;i<LIG;i++)
    {
    if(jouable(i))
        compteur=compteur++;
    }
    if(compteur==0)
    return 1; // grille pleine ---> fin du jeu
    else return 0;
    
}

int jouable(int x)
{
	if(x>0 &&(x<7)&&remplissage[x]>=0 && remplissage[x]<6)
    {
    
    return 1;
    }
	
	else {
       
    return 0;
    }
    

}

int partieGagnante(int c, int l)
{
    if  ((calcul(c,l,0,1)+calcul(c,l,0,-1))>=3 ||
  (calcul(c,l,1,0)+calcul(c,l,-1,0))>=3 ||
  (calcul(c,l,1,1)+calcul(c,l,-1,-1))>=3 ||
  (calcul(c,l,1,-1) + calcul(c,l,-1,1)>=3))
  return 1;
  else return 0;
}

int saisirCoup()
{
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

int main()
{
	int i,j,ligne,colonne;
    
 
 for (i=0;i<6;i++)
     {
        for (j=0;j<7;j++)
        {
             tab[i][j]=' ';
        }
     }


	for(j=0;j<7;j++)
	{
		remplissage[j]=0;
	}

    do
    {
        creationTableau();
        colonne=saisirCoup();
        ligne=remplissage[colonne];
        tab[ligne][colonne]='0';
        remplissage[colonne]=remplissage[colonne]+1;
        creationTableau();
        
    }while((!grillePleine() && !partieGagnante(colonne,ligne)));
    
	printf("Fin du game!");
}
 
 