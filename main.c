#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "matrix.h"
#include "draw.h"
#include "block.h"
#include "cellular_automaton.h"
/*char *usage =
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
  "            endif\n";*/
				
int main (int argc, char **argv){
	matrix_t *m;
	matrix_t *newm;
	int opt;
	char *inf = NULL;
        char *format = NULL;
	char *progname = argv[0];
	int n = 20;
	printf("w main");
 	while ((opt = getopt (argc, argv, "d:f:n:")) != -1) {
    		switch (opt) {
    			case 'd':
    				inf = optarg;
      			break;
			case 'f':
				format = optarg;
			break;
			case 'n':
				n=atoi(optarg);
			break;
			default:    
		/*		fprintf(stderr, usage, progname);*/               
      				exit (EXIT_FAILURE);
		}
	}
	if( optind < argc ) {
		fprintf( stderr, "\nBad parameters!\n" );
		for( ; optind < argc; optind++ )
			fprintf( stderr, "\t\"%s\"\n", argv[optind] );
		fprintf( stderr, "\n" );
	/*	fprintf( stderr, usage, progname );*/
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
//	if (format==NULL)
//		strcat(format," bmp");
	/*else {};*/
	
	write_matrix(m, stdout);
	int i=0;

	for(i;i<n;i++){
	char name[100]="";

char str[10];
printf("przed sprintf\n");
sprintf(str, "%d", i+1);
printf("po sprintf\n");
		strcpy(name,"picture");
		printf("po strcpy\n");
		strcat(name,str);		
				strcat(name,".bmp");
		write_matrix(m,stdout);	
		draw_matrix(m,name);
		
	        newm = cellular_automaton(m);
		m=newm;
	}


	return 0;
}
