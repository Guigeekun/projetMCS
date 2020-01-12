#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LIG 16
#define COL 15
int i;
int j;
char tab[COL][LIG];
int choixL;
int choixC;
void creationTableau();


void demande()
{

	printf("Veuillez entrer le numéro de ligne sur le jeton:\n");
	scanf("%d",&choixL);
while(choixL==0)
{
	printf("Il faut entrer un nombre supérieur à 0!!\n");
	printf("Veuillez entrer le numéro de ligne sur le jeton:\n");
	scanf("%d",&choixL);
}
	printf ("Veuillez entrer le numéro de colonne pour le jeton \n");
	scanf("%d",&choixC);
while(choixC==0)
{
	printf("Il faut entrer un nombre supérieur à 0!!\n");
	printf("Veuillez entrer le numéro de colonne sur le jeton:\n");
	scanf("%d",&choixC);
}	
printf("Vous voulez mettre votre jeton dans la ligne %d et dans  la colonne %d\n",choixL,choixC);

placementJeton(choixL,choixC);

}
void creationTableau()
{

	for(j=0;j<LIG;j=j+2)
	{

		for(i=1;i<COL;i++)
		{
			tab[i][j]='|';
			tab[i][j+1]=' ';
		}		
		tab[COL-1][j+1]='_';	
	}

	for(i=0;i<LIG-1;i++) 
	{
		for(j=0;j<COL;j++)
		{
			printf("%c",tab[i][j]);
		}
		
		printf("\n");
		
	}
}

void placementJeton(choixL,choixC)
{
//printf("Fonction placement");

	for(j=0;j<LIG;j=j+2)
	{

		for(i=1;i<COL;i++)
		{
			tab[i][j]='|';
			tab[choixL][choixC+1]='+';
		}		
		tab[COL-1][j+1]='_';	
	}
	
	for(i=0;i<LIG-1;i++) 
	{
		for(j=0;j<COL;j++)
		{
			printf("%c",tab[i][j]);
		}
		
		printf("\n");
	/// Condition	
	}
	
demande();
}

int main()
{
creationTableau();
demande();
placementJeton(choixL,choixC);
}
