/* ------------------------------------------------------------------------ */
/**
 *  \file       P4.c
 *  \brief     Code du jeu Puissance4
 *
 *  \author     Lucas Dorczysnki
 *
 *  \date       decembre 2019
 *
 *  \version    1.0
 *
 *  
 */

 
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

/*************************************************************************************************************************************************************
 *                                                              PROTOTYPES DES FONCTIONS
 * */

int calculNBJetons(int ,int, int, int);
void creationTableau();
int grillePleine();
int jouable(int);
int partieGagnante(int, int);
int saisirCoup();
//***********************************************************************************************************************************************************


/**
 *  \file       P4.c --> fonction init
 *  \brief    Fonction permettant de calculer les jetons qui se suivent dans toutes les directions  
 *  
 *  \version    1.0
 *  
 * 
 * *			
 */


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

/**
 *  \file       P4.c --> fonction créationTableau
 *  \brief    Fonction permettant de créer la grille de jeu
 *  
 *  \version    1.0
 *  
 * 
 * *			
 */
void creationTableau()
{
	int i, j;
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

/**
 *  \file       P4.c --> fonction grillePleine
 *  \brief    Fonction permettant de vérifier si on peut encore jouer un coup  si la grille est pleine fin de partie
 *  
 *  \version    1.0
 *  
 * 
 * *			
 */

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

/**
 *  \file       P4.c --> fonction jouable
 *  \brief    Fonction permettant de vérifier si on peut jouer un coup pas de superposition de jeton
 *  \version    1.0
 * 
 * 			
 */

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
/**
 *  \file       P4.c --> fonction partieGagnante
 *  \brief    Fonction permettant de vérifier les conditions de victoire
 *  
 *  \version    1.0
 *  
 *  \remark la première condition  vérifie les jetons horizontalement, la seconde verticalement, la troisième diagonalement ( haut-droit vers bas gauche) la 
 * quatrième diagonalement (haut gauche- bas droite)
 * 
 *  
 * *			
 */
int partieGagnante(int c, int l)
{
    if  ((calculNBJetons(c,l,0,1)+calculNBJetons(c,l,0,-1))>=3 ||
  (calculNBJetons(c,l,1,0)+calculNBJetons(c,l,-1,0))>=3 ||
  (calculNBJetons(c,l,1,1)+calculNBJetons(c,l,-1,-1))>=3 ||
  (calculNBJetons(c,l,1,-1) + calculNBJetons(c,l,-1,1)>=3))
  return 1;
  else return 0;
}

 /**
 *  \file       P4.c --> fonction SaisirCoup 
 *  \brief    Fonction permettant de  placer un jeton  
 *  
 *  \version    1.0
 *  
 *  \remark appel la fonction jouable()
 * 
 *  
 * 			
 */
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
		remplissage[j]=0;// remplissage fait référence au remplissage  de la colonne
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
 
 