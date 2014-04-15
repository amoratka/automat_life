#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "matrix.h"
#include "draw.h"
#include "block.h"
#include "cellular_automaton.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#define PARENT_DIRECTORY  ".."

char *usage =
  "Usage: %s -d data -f format -n number of generation -r directory name -i frequency";

int main (int argc, char **argv){
	matrix_t *m;
	matrix_t *newm;
	int opt;
	char *progname = argv[0];
	char *inf = NULL;
        char *format = NULL;
	int n = 20;
	char *dirname = NULL;
	int f=1;
 	while ((opt = getopt (argc, argv, "d:f:n:r:i:")) != -1) {
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
			case 'r':
				dirname=optarg;
			break;
			case 'i':
				f=atoi(optarg);
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
	else{
		FILE *in = fopen("pulsar","r");
		m=read_matrix(in);
	}
	
	if (format == NULL)
	format="bmp";
	
	if(dirname==NULL) dirname="pictures";
	
	int i=0;
	int k=1;
	for(i;i<n;i++){
		if(i%f==0){
		char name[100]="";
		char str[10];
		sprintf(str, "%d", k);
		strcpy(name,"picture");
		strcat(name,str);
		strcat(name,".");
		strcat(name,format);	
		draw_matrix(m,name,dirname);
		k++;
		}
		newm = cellular_automaton(m);
		m=newm;
	}


	return 0;
}
