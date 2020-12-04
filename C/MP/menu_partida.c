#include <stdio.h>
#include "estruct.h"
#include <math.h>
#include <string.h>
// incluir comienzo_partida.h
double dist(int x1, int y1, int x2, int y2)
{
    int x, y;
    double d;
    x=x1-x2;
    y=y1-y2;
    d=sqrt((pow(x,2))+(pow(y,2)));
    return d;
}
// VIVA ESPAÑA

void mostrar_mochila(r_bag* bag);
void mover_posicion(r_coord coord, int distancia, r_storm tormenta, int radio_mapa);
void interaccion_partida(r_player* player, r_bag* bag, r_item* item, r_coord* coord, r_config config, int numero_jugador, r_elem elem, int rango_arma);
// posible sustitucion
void pos_actual(r_coord coord);
//
// posible sustitucion
void pos_tormenta(r_storm stages);
//
void acabar_turno();
void volver_menu();

void menu_partida(r_player** player,r_item* item,r_storm* stages,r_coord** coord, r_config config,int numero_jugador, int fase_tormenta, r_elem elem){

int op;

do{
   
    printf("1.Mostrar mochila.\n2.Moverse.\n3.Mostrar enemigos cercanos/disparar.\n4.Mostrar posicion actual.\n5.Mostrar posicion de la tormenta.\n6.Acabar turno.\n7.Volver al menu principal.\n");
    scanf("%d",&op);
    
    system("cls");

    switch(op){

        	case 1: mostrar_mochila(bag);
			       	break;
			       
        	case 2: mover_posicion(coord[numero_jugador],config.step_dist,stages[fase_tormenta],config.radius_map);
        			break;
        			
 			case 3: interaccion_partida(player,bag,item,coord,config,numero_jugador,elem,80);
					break;

 			case 4: pos_actual(coord[numero_jugador]);
					break;

 			case 5: pos_tormenta(stages[fase_tormenta]);
					break;

 			case 6: acabar_turno(/*funcion juanjo*/);
					break;

 			case 7: volver_menu(/*funcion juanjo*/);
					break;
    }

     }while(op<1 || op>7);
}


//cabecera: void mostrar_mochila(r_bag *bag);
//precondicion: Componentes de la mochila inicializados.
//postcondicion: muestra el contenido de la mochila del jugador que esta en partida.

void mostrar_mochila(r_bag* bag){

	     printf("%c/%c/%d/%d\n",bag -> id_item,bag -> quant, bag -> equipped);

}

//cabecera: void mover_posicion();
//precondicion: 
//postcondicion: habilita el movimiento del jugador 

void mover_posicion(r_coord coord, int distancia, r_storm tormenta, int radio_mapa){
	
int x,s,sale_mapa_arriba,sale_mapa_abajo,sale_mapa_izq,sale_mapa_derecha,sale_tormenta_arriba,sale_tormenta_derecha,sale_tormenta_abajo,sale_tormenta_izq;

// Calculo del desplazamiento hacia arriba (devuelve 1 si al realizar el movimiento, el jugador queda fuera del mapa)

if(dist(coord.x,coord.y+distancia,0,0)>radio_mapa){
 	sale_mapa_arriba=1;
    }else{
		sale_mapa_arriba=0;
}
if(dist(coord.x,coord.y+distancia,tormenta.x,tormenta.y)>tormenta.radius){
 	sale_tormenta_arriba=1;
	}else{
 		sale_tormenta_arriba=0;
}

// Calculo del desplazamiento hacia la derecha (devuelve 1 si al realizar el movimiento, el jugador queda fuera del mapa)

if(dist(coord.x+distancia,coord.y,0,0)>radio_mapa){
 	sale_mapa_derecha=1;
	}else{
 		sale_mapa_derecha=0;
}
if(dist(coord.x+distancia,coord.y,tormenta.x,tormenta.y)>tormenta.radius){
 	sale_tormenta_derecha=1;
	}else{
 		sale_tormenta_derecha=0;
}

// Calculo del desplazamiento hacia abajo (devuelve 1 si al realizar el movimiento, el jugador queda fuera del mapa)

if(dist(coord.x,coord.y-distancia,0,0)>radio_mapa){
 	sale_mapa_abajo=1;
	}else{
 		sale_mapa_abajo=0;
}
if(dist(coord.x,coord.y-distancia,tormenta.x,tormenta.y)>tormenta.radius){
 	sale_tormenta_abajo=1;
	}else{
 		sale_tormenta_abajo=0;
}

// Calculo del desplazamiento hacia la izquierda (devuelve 1 si al realizar el movimiento, el jugador queda fuera del mapa)

if(dist(coord.x-distancia,coord.y,0,0)>radio_mapa){
 	sale_mapa_izq=1;
	}else{
 		sale_mapa_izq=0;
}
if(dist(coord.x-distancia,coord.y,tormenta.x,tormenta.y)>tormenta.radius){
 	sale_tormenta_izq=1;
	}else{
 		sale_tormenta_izq=0;
}



do{

   printf("Posibles movimientos:\n");
		 if(sale_mapa_arriba==0){
    		printf("1- Moverse hacia arriba.");
       	 if(sale_tormenta_arriba==1){
    		printf("(Sale a la tormenta)");
}
    printf("\n");
}

       	if(sale_mapa_abajo==0){
    		printf("2- Moverse hacia abajo.");
       	if(sale_tormenta_abajo==1){
    		printf("(Sale a la tormenta)");
}
    printf("\n");
}

	   	if(sale_mapa_derecha==0){
    		printf("3- Moverse hacia la derecha.");
       	if(sale_tormenta_derecha==1){
    		printf("(Sale a la tormenta)");
}
    printf("\n");
}

		if(sale_mapa_izq==0){
    		printf("4- Moverse hacia la izquierda.");
       	if(sale_tormenta_izq==1){
    		printf("(Sale a la tormenta)");
}
    printf("\n");
}
   
scanf("%d",&x);

       switch(x){
       	
       	case 1: if(sale_mapa_arriba==0){
       	  coord.y += distancia;
       	    s=0;
           }else{
           	printf("No puedes salir del mapa.\n");
           s=1; 
		   }
		   break;
		   
       	case 2: if(sale_mapa_abajo==0){
       	 coord.y -= distancia;
       	    s=0;
		   }else{
		   	printf("No puedes salir del mapa.\n");
		   	s=1;
		   }
		   break;
		   
       	case 3: if(sale_mapa_derecha==0){
       	 coord.x -= distancia;	
       	   s=0;
           }else{
       	   	printf("No puedes salir del mapa.\n");
       	   	s=1;
       	   }
		   break;
		   
       	case 4: if(sale_mapa_izq==0){
       	 coord.x += distancia;
		   s=0; 	
		   } 
		   else{
		   	printf("No puedes salir del mapa.\n");
		   	s=1;
		   }
		   break;
		   
       	default: puts("Error"); 
		   s=1;
       	
       }
   } while(s==1);   
}




//cabecera: interaccion_partida();
//precondicion: 
//postcondicion: muestra enemigos y objetos cercanos, y atacar(si esta a rango del arma equipada)

void interaccion_partida(r_player* player, r_bag* bag, r_item* item, r_coord* coord, r_config config, int numero_jugador, r_elem elem, int rango_arma ){
int i,x,condicion;
float distancia;
do{

for(i=0;i<elem.coord;i++){
	if(i != numero_jugador && strcmp(coord[i].type,"JUG") == 0 ){
	distancia = dist(coord[numero_jugador].x,coord[numero_jugador].y,coord[i].x,coord[i].y);
	if(distancia <= config.vis_range){
		printf("%d-Jugador(%d,%d) a %.2f distancia ",i+1,coord[i].x,coord[i].y,distancia);
		if(distancia <= rango_arma){
			printf("(Se puede atacar)");
		}
		printf("\n");
	  }
    }
    else{
    	if (strcmp(coord[i].type,"OBJ") == 0){
    	 distancia = dist(coord[numero_jugador].x,coord[numero_jugador].y,coord[i].x,coord[i].y);
	if(distancia <= config.vis_range){
		printf("%d-Objeto(%d,%d) a %.2f distancia ",i+1,coord[i].x,coord[i].y,distancia);
		if(distancia <= config.pick_range){
			printf("(Se puede recoger)");
		      }
		        printf("\n");
	  
           }	
    	}
    }
  }
  
  scanf("%d",&x);
  system("cls");
  
  			if(x <= elem.coord && x > 0 && x-1 != numero_jugador){
  			  	if(strcmp(coord[x-1].type,"JUG") == 0){
  			  		if(dist(coord[numero_jugador].x,coord[numero_jugador].y,coord[x-1].x,coord[x-1].y) <= rango_arma){
  			  			// comparar la id de coord[x-1] con los jugadores y la id del arma con la de los items y restar a jugador[x-1] el daño del arma.
  			  			printf("Jugador %d vida - daño_arma\n",x);
  			  			condicion = 0;
  			  		}else{
  			  			printf("Error\n");
  			  			
  			  			condicion = 1;
  			  		}
  			  	}else{
  			  		if(strcmp(coord[x-1].type,"OBJ") == 0){
  			  		if(dist(coord[numero_jugador].x,coord[numero_jugador].y,coord[x-1].x,coord[x-1].y) <= config.pick_range){
  			  			// comparar la id de coord[x-1] con la de los objetos y ver si el inventario esta lleno, ademas de borrarlo de elementos coord.
  			  			printf("Objeto %d recogido\n",x);
  			  			condicion = 0;
  			  		}else{
  			  			printf("Error\n");
  			  			
  			  			condicion = 1;
  			  		}	
  			  		}
  			  	}
  			}else{
  				printf("Error\n");
  				condicion = 1;
  			}
  		system("pause");
  		system("cls");
} while(condicion == 1); 	
  	

  
}					

//cabecera: void pos_actual(r_coord* coord);
//precondicion: 
//postcondicion: 

void pos_actual(r_coord coord){

		printf("%d/%d\n",coord.x,coord.y);
		
		system("pause");
		system("cls");
}

//cabecera: void pos_tormenta();
//precondicion: posición de la tormenta inicializadas.
//postcondicion: Devuelve la posicion actual de la tormenta.

void pos_tormenta(r_storm storm){

		printf("%d/%d\n", storm.x, storm.y);
		
		system("pause");
		system("cls");
}

//cabecera: void acabar_turno();
//precondicion: 
//postcondicion: Permite al jugador acabar el turno.

void acabar_turno(){
/*
Necesario implementar otro modulo.
*/
}

//cabecera:void return_menu();
//precondicion:
//postcondicion: Permite al jugador volver al menu principal.

void volver_menu(){
/*
necesario implementar otro modulo.
*/

}
