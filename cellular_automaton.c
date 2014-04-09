#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cellular_automaton.h"
#include "block.h"

matrix_t *
cellular_automaton(matrix_t *m)
{	int i;
	int c, r;
	int n;
	int status=0;
	int newstatus=status;
	matrix_t * newm;
	newm=make_matrix ( m->rn, m->cn);
	n=m->rn*m->cn;
	int *tab;
	int size=9;
	tab=(int*)malloc(size*sizeof(int));
	tab[0]=9;
	for(i=0;i<n;i++)
	{
		c=i%m->cn+1;
		r=i/m->cn+1;
		block(r,c,m,tab);
		status=m->e[(r-1)*m->cn+c-1];
		newstatus = cellular(tab,status);	
		put_entry_matrix (newm, r-1,  c-1,  newstatus);
	}
return newm;
}

