#ifndef _BLOCK_H
#define _BLOCK_H_

#include<stdio.h>
#include<stdlib.h>
#include"matrix.h"

void block(int r,int c, matrix_t *m, int tab[]);
int cellular (int tab[], int status);

#endif

