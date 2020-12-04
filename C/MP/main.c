#include "estruct.h"

int main()
{
    int i;
    r_elem elems;
    r_player *player;
    r_item *item;
    r_storm *stages;
    r_coord *coord;
    r_config config;

    get_elems(&elems);
    elems.coord=7;
    //Declaracion de vectores
    player = (r_player*) malloc(elems.ply*sizeof(r_player));
    item = (r_item*) malloc(elems.itm*sizeof(r_item));
    stages = (r_storm*) malloc(elems.stg*sizeof(r_storm));
    coord = (r_coord*) malloc(elems.coord*sizeof(r_coord));
   
    for(i = 0; i < elems.ply; i++)
        player[i].bag = (r_bag*) calloc(10, sizeof(r_bag));
    //Cargo los ficheros en las estructuras
    files_struct(player, item, stages, &config, elems);
    for(i = 0; i < elems.ply; i++)
        player[i].bag = (r_bag*) realloc(player[i].bag, config.capac_bag*sizeof(r_bag));
    //Cargo los ficheros en las estructuras
    //Resto del codigo vuestro
    
    
    // Posiciones de tormenta y jugadores se definen automaticamente
    
    coord[0].x=0;
	coord[0].y=0;
	coord[1].x=50;
	coord[1].y=0;
	coord[2].x=100;
	coord[2].y=0;
	coord[3].x=0;
	coord[3].y=100;
	strcpy(coord[0].type,"JUG");
	strcpy(coord[1].type,"JUG");
	strcpy(coord[2].type,"JUG");
	strcpy(coord[3].type,"JUG");

	coord[4].x=0;
	coord[4].y=50;
	coord[5].x=50;
	coord[5].y=0;
	coord[6].x=50;
	coord[6].y=50;
	strcpy(coord[4].type,"OBJ");
	strcpy(coord[5].type,"OBJ");
	strcpy(coord[6].type,"OBJ");
	stages[0].x=0;
	stages[0].y=0;
    
    while(1){
   
	menu_partida(player,player[0].bag,item,stages,coord,config,0,0,elems); 
	}
	
	
	
    //Final
    //Guardo la informacion en ficheros
    struct_files(player, item, stages, config, elems);
    free(player);
    free(item);
    free(stages);
    free(coord);
    return 0;
}


