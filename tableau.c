#include <stdlib.h>
#include <stdio.h>
#include <string.h>


 #define LIG 16
 #define COL 15
 
int main()
{
int i,j,j1;
int col1=(COL-1)/2;
int lig1=LIG-1;
int board[col1][lig1]; //init du board avec les tokens
char t[COL][LIG];

memset(board,0,sizeof(board));

for(i=0;i<col1;i++) //à modifier pour mettre le tab dans le bon sens 
{
	for(j=0;j<lig1;j++)
	{
		printf("%d",board[i][j]);
	}
	printf("\n");
}

for(j=0;j<COL;j++)
	{
		t[LIG][j]='_';
	}


for(j=0;j<LIG;j=j+2)
{
	for(i=1;i<COL;i++)
	{
		j1=j/2;
		t[i][j]='|';
		t[i][j+1]=' '; //
	}
}



for(i=0;i<LIG-1;i++) //à modifier pour mettre le tab dans le bon sens 
{
	for(j=0;j<COL;j++)
	{
		printf("%c",t[i][j]);
	}
	
	printf("\n");
	
}

}








