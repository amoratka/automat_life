#include <stdio.h>
#include <stdlib.h>
#include "block.h"
void block(int r, int c, matrix_t *m, int tab[] ){
	int z=1;
	for(z;z<tab[0];z++)
		tab[z]=0;
	int x = 0;
	int y = 0; 
	int k,l;
	printf("aktualnie sprawdzana komórka %d %d \n",r,c);
	int tmp=1;
		for(k=-1;k<2;k++)
			for(l=-1;l<2;l++)
			{
				x=(r+k)%m->rn;
				y=(c+l)%m->cn;
				if (x==0)	x=m->rn;
				if (y==0)	y=m->cn;
				printf("nr = %d nc = %d tmp = %d n\n",x, y,tmp);
				if(x!=r||y!=c){
					tab[tmp]=m->e[(x-1)*m->cn+y-1];
					printf("wartosc e %d\n",m->e[(x-1)*m->cn+y-1]);
					tmp++;
				}	
			}		
	int i=0;
	for(i;i<tab[0];i++)
	printf("%d",tab[i]);
	printf("\n");

}
int cellular( int tab[], int status){
	int nl=0;
	int nd=0;
	int i;
	int newstatus=status;
	for(i=1;i<tab[0];i++)
		if(tab[i]==1)	nl++;
		else		nd ++;
	for(i=1;i<tab[0];i++)
		if(status==1&&(nl!=2&&nl!=3))	newstatus=0;	
		else if(status==0&&nl==3) 	newstatus=1;	
return newstatus;
}		
			

