#include "stdlib.h"
#include "stdio.h"

 
 
int main()
{
int i,j;
char t[10][10];
for(i=0;i<10;i++)
{
	for(j=0;j<10;j++)
	{
		t[i][j]='-';
	}

}

for(i=0;i<10;i++)
{
	for(j=0;j<10;j++)
	{
		printf("%c",t[i][j]);
	}
	printf("\n");

}

}








