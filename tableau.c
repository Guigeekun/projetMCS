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

<<<<<<< Updated upstream
for(j=0;j<COL;j++)
	{
		t[0][j]='_';
=======
		for(i=1;i<COL;i++)
		{
			tab[i][j]='|';
			tab[i][j+1]=' ';
		}		
		tab[COL-1][j+1]='_';	
>>>>>>> Stashed changes
	}

	for(i=0;i<LIG-1;i++) //à modifier pour mettre le tab dans le bon sens 
	{
<<<<<<< Updated upstream
		j1=j/2;
		t[i][j]='|';
		t[i][j+1]=(char*) board[j1,i]; //need to fix that asap
	}
}



for(i=0;i<COL;i++) //à modifier pour mettre le tab dans le bon sens 
{
	for(j=0;j<LIG;j++)
	{
		printf("%c",t[i][j]);
	}
	printf("\n");
}

}








=======
		for(j=0;j<COL;j++)
		{
			printf("%c",tab[i][j]);
		}
		
		printf("\n");
		
	}
}
>>>>>>> Stashed changes
