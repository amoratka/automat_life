#ifndef _matrix
#define _matrix

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int rn;
	int cn;
   	int *e;
} matrix_t;

matrix_t * make_matrix( int rn, int cn );

void free_matrix (matrix_t *m);

matrix_t * read_matrix( FILE *in );

void write_matrix( matrix_t *, FILE *out );

void put_entry_matrix( matrix_t *, int i, int j, int val );

void add_to_entry_matrix( matrix_t *, int i, int j, int val );

int get_entry_matrix( matrix_t *, int i, int j );

matrix_t * copy_matrix( matrix_t *s );


#endif
