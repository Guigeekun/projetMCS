#include <stdlib.h>
#include <stdio.h>
#include <string.h>


 #define LIG 16
 #define COL 15
 
int main()
{
int i,j;
int board[8][17] = {0}; //init du board avec les tokens
unsigned t[COL][LIG];

for(j=0;j<COL;j++)
	{
		t[0][j]='_';
	}


for(j=0;j<LIG;j=j+2)
{
	for(i=1;i<COL;i++)
	{
		t[i][j]='|';
		t[i][j+1]=' '; //à remplir avec les tokens
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








