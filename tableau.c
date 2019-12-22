#include "stdlib.h"
#include "stdio.h"

 #define COL 16
 #define LIG 16
 
int main()
{
int i,j;
char t[LIG][COL];
for(j=0;j<COL-1;j++)
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








