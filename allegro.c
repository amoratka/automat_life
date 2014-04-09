#include<allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

char *usage =
  "Usage: %s -d spline-file [-p points-file] [ -g gnuplot-file [-f from_x -t to_x -n n_points ] ]\n"
  "            if points-file is given then\n"
  "               reads discrete 2D points from points-file\n"
  "               writes spline approximation to spline-file\n"
  "               - number of points should be >= 4\n"
  "            else (points-file not given)\n"
  "               reads spline from spline-file\n"
  "            endfi\n"
  "            if gnuplot-file is given then\n"
  "               makes table of n_points within <from_x,to_x> range\n"
  "               - from_x defaults to x-coordinate of the first point in points-file,\n"
  "               - to_x defaults to x-coordinate of the last point\n"
  "               - n_points defaults to 100\n"
  "               - n_points must be > 1\n"
  "            endif\n";

typedef struct {
	int rn;
    int cn;
    int *e;
} matrix_t;

matrix_t *
make_matrix (int rn, int cn)
{
  matrix_t *new_mat = malloc (sizeof *new_mat);
  if (new_mat == NULL)
    return NULL;
  if ((new_mat->e =
       malloc ((size_t) rn * (size_t) cn * sizeof *new_mat->e)) == NULL) {
    free (new_mat);
    return NULL;
  }
  new_mat->rn = rn;
  new_mat->cn = cn;
  memset (new_mat->e, 0, (size_t) (rn * (size_t) cn * sizeof *new_mat->e));
  return new_mat;
}

void
free_matrix (matrix_t * m)
{
  free (m->e);
  free (m);
}

void
put_entry_matrix (matrix_t * m, int i, int j,  int val)
{
  if (i >= 0 && i < m->rn && j >= 0 && j <= m->cn)
    m->e[i * m->cn + j] = val;
}

void
add_to_entry_matrix (matrix_t * m, int i, int j, int val)
{
  if (i >= 0 && i < m->rn && j >= 0 && j <= m->cn)
    m->e[i * m->cn + j] += val;
}

double
get_entry_matrix (matrix_t * m, int i, int j )
{
  if (i >= 0 && i < m->rn && j >= 0 && j <= m->cn)
    return m->e[i * m->cn + j];
	else
		return -999;
}

matrix_t *
read_matrix (FILE * in)
{
  int rn, cn;
  int i, j;
  matrix_t *new_mat;
  if (fscanf (in, "%d %d", &rn, &cn) != 2)
    return NULL;

  if ((new_mat = make_matrix (rn, cn)) == NULL)
    return NULL;
  for (i = 0; i < rn; i++)
    for (j = 0; j < cn; j++)
      if (fscanf (in, "%d", &new_mat->e[i * cn + j]) != 1) {
        free_matrix (new_mat);
        return NULL;
      }

  return new_mat;
}

void
write_matrix (matrix_t * m, FILE * out)
{
  int i, j;
  if (m == NULL) {
    fprintf (out, "Matrix is NULL\n");
    return;
  }

  fprintf (out, "%d %d\n", m->rn, m->cn);
  for (i = 0; i < m->rn; i++) {
    for (j = 0; j < m->cn - 1; j++)
      fprintf (out,  " %d ",m->e[i * m->cn + j]);
    fprintf (out, " %d\n", m->e[i * m->cn + j]);
  }
}

void draw_matrix(matrix_t *m, char *format)
{
    	allegro_init();
    	install_keyboard();
    	set_color_depth( 16 );
    	set_gfx_mode( GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0 );
   	clear_to_color( screen, makecol( 255, 0,255 ) );

	BITMAP * obrazek1 = NULL;
	obrazek1 = create_bitmap( m->cn*100, m->rn*100 );
	if( !obrazek1 )
	{
	    set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
	    allegro_message( "nie mogę załadować obrazka 1 !" );
	    allegro_exit();
	}

	clear_to_color( obrazek1, makecol( 255, 255, 255 ) );
	int i,j;
	for (i = 0; i < m->rn; i++) 
    		for (j = 0; j < m->cn ; j++)
				if(m->e[i*m->cn+j]==1)
					rectfill( obrazek1, j*100, i*100,  (j*100)+100,(i*100)+100,makecol( 0, 0, 0 ) );
		
	blit( obrazek1, screen, 0, 0, 100, 100, obrazek1->w, obrazek1->h );
	masked_blit;
	save_bitmap("dump.bmp", obrazek1, default_palette);
	
	destroy_bitmap( obrazek1 );
	readkey();
	allegro_exit();
}
/*numeracja c r od 1 w put od 0 */
int* block(int r, int c, matrix_t *m){
	size_t size = 9;/*sąsiedztwo MOORE`a* pierwsze to rozmiar*/
	int *tab = malloc(size*sizeof(int));
	tab[0]=size;
	int x = 0;
	int y = 0; 
	int k,l;
	
	int tmp=1;
		for(k=-1;k<2;k++)
			for(l=-1;l<2;l++)
			{
				x=(r+k)%m->rn;
				y=(c+l)%m->cn;
				if (x==0)	x=m->rn;
				if (y==0)	y=m->cn;
				/*printf("nr = %d nc = %d \n",x, y);*/
				if(x!=r&&y!=c)		tab[tmp]==m->e[(r-1)*m->cn+c-1];
				tmp++;	
			}		
		
return tab;			
}
int cellular( int tab[], int status){
	int nl=0;
	int nd=0;
	int i;
	int newstatus;
	for(i=1;i<tab[0];i++)
		if(tab[i]==1)	nl++;
		else		nd ++;
	for(i=1;i<tab[0];i++)
		if(tab[i]=1&&(nl=!2&&nl!=3))	newstatus=0;	
		else if(tab[i]==0&&nl==3) 	newstatus=1;	
return newstatus;
}		
			

matrix_t *
cellular_automaton(matrix_t *m)
{	int i;
	int c, r;
	int n;
	int status=0;
	int newstatus=status;
	int *tab;
	matrix_t * newm;
	newm=make_matrix ( m->rn, m->cn);
	n=m->rn*m->cn;
	for(i=0;i<n-1;i++)
	{
		c=i%m->cn+1;
		r=i/m->cn+1;
		tab=block(r,c,m);
		status=m->e[(r-1)*m->cn+c-1];
		newstatus = cellular(tab,status);	
		put_entry_matrix (newm, r-1,  c-1,  newstatus);
	free(tab);
	}
return newm;
}

				
				
int main (int argc, char **argv){
	matrix_t *m;
	int opt;
	char *inf = NULL;
        char *format = NULL;
	char *progname = argv[0];
 	while ((opt = getopt (argc, argv, "d:f:")) != -1) {
    		switch (opt) {
    			case 'd':
    				inf = optarg;
      			break;
			case 'f':
				format = optarg;
			break;
			default:    
				fprintf(stderr, usage, progname);               
      				exit (EXIT_FAILURE);
		}
	}
	if( optind < argc ) {
		fprintf( stderr, "\nBad parameters!\n" );
		for( ; optind < argc; optind++ )
			fprintf( stderr, "\t\"%s\"\n", argv[optind] );
		fprintf( stderr, "\n" );
		fprintf( stderr, usage, progname );
		exit( EXIT_FAILURE );
	}
	if (inf != NULL) {
   		FILE *in = fopen (inf, "r");
   			if (in == NULL) {
   	   			fprintf (stderr, "%s: can not read points file: %s\n\n", argv[0], inf);
      				exit (EXIT_FAILURE);
    			}
		else 
			m=read_matrix(in);
	}
	else {};
	write_matrix(m, stdout);
	draw_matrix(m,format);
	cellular_automaton(m);
	return 0;
}
