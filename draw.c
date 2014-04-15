#include <allegro.h>
#include <stdlib.h>
#include <stdio.h>
#include "draw.h"
#include <string.h>
#include "matrix.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#define PARENT_DIRECTORY  ".."

void draw_matrix(matrix_t *m, char *name, char *dirname){
    	
	allegro_init();
    	set_color_depth( 16 );
	BITMAP * obrazek1 = NULL;
	obrazek1 = create_bitmap( m->cn*10, m->rn*10 );
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
					rectfill( obrazek1, j*10, i*10,  (j*10)+10,(i*10)+10,makecol( 0, 0, 0 ) );
	
	chdir(dirname);
	save_bitmap(name, obrazek1, default_palette);	
	chdir(PARENT_DIRECTORY);	
	
	destroy_bitmap( obrazek1 );
	allegro_exit();

}

