#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LIG 16
#define COL 15
int i;
int j;
char tab[COL][LIG];
int main()
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

	for(i=0;i<LIG-1;i++) //à modifier pour mettre le tab dans le bon sens 
	{
		for(j=0;j<COL;j++)
		{
			printf("%c",tab[i][j]);
		}
		
		printf("\n");
		
	}
}
