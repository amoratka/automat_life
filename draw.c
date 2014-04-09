#include <allegro.h>
#include <stdlib.h>
#include <stdio.h>
#include "draw.h"
#include <string.h>
#include "matrix.h"
void draw_matrix(matrix_t *m, char *name){
    	//char name[100];
	//strcat(name,"picture3.bmp");
	//printf("%d\n",nr);
	
	allegro_init();
    	install_keyboard();
    	set_color_depth( 16 );
    	set_gfx_mode( GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0 );
   	clear_to_color( screen, makecol( 255, 0,255 ) );
	BITMAP * obrazek1 = NULL;
	obrazek1 = create_bitmap( m->cn*10, m->rn*10 );
	if( !obrazek1 )
	{
	    set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
	    allegro_message( "nie mogę załadować obrazka 1 !" );
	    allegro_exit();
	}
	printf("cosiek\n");
	clear_to_color( obrazek1, makecol( 255, 255, 255 ) );
	int i,j;
	for (i = 0; i < m->rn; i++) 
    		for (j = 0; j < m->cn ; j++)
				if(m->e[i*m->cn+j]==1)
					rectfill( obrazek1, j*10, i*10,  (j*10)+10,(i*10)+10,makecol( 0, 0, 0 ) );
	blit(obrazek1,screen,0, 0 , 100, 100 , obrazek1->w, obrazek1->h);

	
 	printf("cosiek2\n");
//	char *b;
//	sprintf(b,"%d",4);
//	strcat(name,b);
	printf("cosiek3\n");
//	char *cosiek = ".bmp";
//	strcat(name,cosiek);
	//strcat(name,format);
//	printf("%s\n",name);
	save_bitmap("name.bmp", obrazek1, default_palette);		
	destroy_bitmap( obrazek1 );
	readkey();
	allegro_exit();
}

