//Menu principal y login/register
#include "estruct.h"
#include "menu.h"

void login(r_player **, r_elem *, int *, r_config);
void registrarse(r_player**, r_elem *, r_config, int);
void mostrar_menu_princ(r_player *, int);
void jugar(r_player **, int, r_config, r_elem);
void comienzo_forzoso(r_player **, r_elem);
void ver_perfil(r_player **, int);
void ajustes(r_config *, r_elem,r_item **, r_storm **);
int cuenta_objetos(r_player, r_config);
void tienda(r_player **, r_config, r_elem, r_item *, int);

//Cabecera: void login(r_player *player)
//Precondición: player inicializada
//Postcondición: Permite iniciar sesión al usuario
void login(r_player **player,r_elem *elems, int *auxi,r_config config)
{

    char op, nick[20],pass[20];
    int i;

    printf(" ---------\n | LOGIN | \n ---------\n\n");
    do
    {
        op = 'x';
        fflush(stdin);
        i = 0;
        printf("Por favor, introduzca su nombre de usuario: ");
        fgets(nick,20,stdin);
        nick[strlen(nick) - 1] = '\0';

        while(strcmp((*player)[i].nick, nick) != 0 && i < elems->ply)
            i++;

        *auxi = i;
        if (strcmp((*player)[i].nick, nick) != 0)
        {
            printf("El usuario no coincide, %cdesea registrarlo?\n s/n(volver a introducir otro usuario) \n",168);
            do
            {
                fflush(stdin);
                scanf("%c",&op);
            }
            while(op != 's' && op != 's' && op != 'N' && op != 'n');
        }

        else
        {
            do
            {
                op = 'x';
                printf("Por favor, introduzca su contrase%ca: ",164);
                fflush(stdin);
                fgets(pass,20,stdin);
                pass[strlen(pass) - 1] = '\0';

                if(strcmp((*player)[i].pass,pass) == 0)
                {
                    printf("Bienvenido/a!\n");
                    if(strcmp((*player)[i].status,"OFF") == 0)
                        strcpy((*player)[i].status,"ON");
                }
                else
                {
                    printf("Contrase%ca incorrecta, %cqu%c desea hacer?\n a.Volver a introducir la contrase%ca\n b.Introducir otro nombre de usuario\n",164,168,130,164);
                    do
                    {
                        fflush(stdin);
                        scanf("%c",&op);
                    }
                    while(op != 'a' && op != 'A' && op != 'b' && op != 'B');
                }


            }
            while(op == 'a' || op == 'A');
        }

        if(op == 's')
        {
            system("cls");
            registrarse(player,elems,config,*auxi);
        }
    }
    while(op == 'b' || op == 'B' || op == 'n' || op == 'N');
}


//Cabecera: void registrarse (r_player *player)
//Precondición: player inicializada
//Postcondición: Permite registrar un nuevo usuario
void registrarse(r_player** player, r_elem *elems, r_config config,int auxi)
{

    int i;

    char nick[15], pass[15], nombre[25], op;

    printf(" ---------------\n | REGISTRARSE | \n ---------------\n\n");

    printf("Introduce tu nick: ");
    fflush(stdin);
    fgets(nick, 15, stdin);
    nick[strlen(nick) - 1] = '\0';
    op = 'x';

    //Compruebo si existe
    i = 0;
    while(strcmp(nick, (*player)[i].nick) != 0 && i < elems->ply)
        i++;

    if(strcmp(nick, (*player)[i].nick) == 0)
    {

        do
        {

            printf("\nERROR, nick registrado, %cqu%c desea hacer?\n    a.Introducir otro nombre de usuario\n    b.Volver al men%c anterior\n",168,130,163);
            fflush(stdin);
            scanf("%c", &op);
            if(op != 'A' && op != 'B' && op != 'a' && op != 'b')
                puts("ERROR");

        }
        while (op != 'A' && op != 'B' && op != 'a' && op != 'b');

        if(op == 'a' || op == 'A')
            registrarse(player, elems, config,auxi);

        else
            op = 'b';
    }
    else
    {

        //Aumento el vector
        elems->ply++;
        *player = (r_player *) realloc(*player, (elems->ply)*sizeof(r_player));

        //Nick
        strcpy((*player)[(elems->ply) - 1].nick,nick);

        //Nombre
        printf("\nNick disponible, introduzca su nombre: ");
        fgets(nombre, 25, stdin);
        nombre[strlen(nombre) - 1] = '\0';
        strcpy((*player)[(elems->ply) - 1].name,nombre);

        //Contraseña
        printf("Introduzca su contrase%ca: ",164);
        fgets(pass,15,stdin);
        pass[strlen(pass) - 1] = '\0';
        strcpy((*player)[(elems->ply) - 1].pass, pass);

        //Mochila
        for(i = 0; i < elems->ply; i++)
            (*player)[i].bag = (r_bag*) calloc(config.capac_bag, sizeof(r_bag));

        //Tipo, ganadas, jugadas, monedas, nivel
        strcpy((*player)[(elems->ply) - 1].type, "JGD");
        (*player)[(elems->ply) - 1].wins = 0;
        (*player)[(elems->ply) - 1].games = 0;
        (*player)[(elems->ply) - 1].gold = config.def_gold;
        (*player)[(elems->ply) - 1].lvl = 1;

        system("cls");

        //Llamo a login justo despues de registrar un usuario
        login(player,elems,&auxi,config);
    }
}

//Cabecera: void mostrar_menu_princ(r_player *player,int auxi)
//Precondición: player y auxi inicializados
//Postcondición: Muestra el menú principal
void mostrar_menu_princ(r_player *player,int auxi)
{

    printf(" -----------\n | ESINAIT |\n -----------\n\n");

    if (strcmp(player[auxi].type,"JGD") == 0)
        printf("1. Jugar/Continuar partida\n2. Ver perfil\n3. Tienda\n4. Cambiar de usuario\n5. Salir del sistema\n");

    else
        printf("1. Jugar/Continuar partida\n2. Comenzar partida\n3. Ver perfil\n4. Tienda\n5. Ajustes\n6. Cambiar de usuario\n7. Salir del sistema\n");

}

//Cabecera: void jugar(r_player *player, int auxi)
//Precondición: player y auxi inicializados
//Postcondición: Cambia el estado de un jugador a "EE" y comprueba si se puede empezar la partida automaticamente
void jugar(r_player **player, int auxi, r_config config, r_elem elems)     //JGD
{

    int cont = 0, i = 0;

    strcpy((*player)[auxi].status,"EE");

    while (strcmp((*player)[i].status,"EE") == 0 && cont <= config.min_player && i < elems.ply)
    {
        i++;
        cont++;
    }

    if(cont == config.min_player)
        for(i = 0; i < elems.ply; i++)

            if(strcmp((*player)[i].status,"EE") == 0)
                strcpy((*player)[i].status,"EJ");

}

//Cabecera: void comienzo_forzoso(r_player *player)
//Precondición: player inicializada
//Postcondición: Comienza la partida
void comienzo_forzoso(r_player **player,r_elem elems)    //admin
{
    printf("Bienvenidos a la grita del hinbocador\n");
}


//Cabecera: void ver_perfil(r_player *player, int auxi
//Precondición: player y auxi inicializados
//Postcondición: Muestra la información de un usuario
void ver_perfil(r_player **player,int auxi)   //Auxi debe ser el numero de jugador. Para saberlo, utilizar la funcion posicion
{

    char op,aux[25];

    int selec;

    puts(" ------------\n| Ver perfil |\n ------------\n");

    do
    {

        printf("Nick: %s\n",(*player)[auxi].nick);
        printf("Nombre: %s\n",(*player)[auxi].name);
        printf("Nivel: %d\n",(*player)[auxi].lvl);
        printf("Monedas: %d\n",(*player)[auxi].gold);
        printf("Partidas jugadas: %d\n",(*player)[auxi].games);
        printf("Partidas ganadas: %d\n",(*player)[auxi].wins);

        printf("\n%cQuieres editar perfil? s/n (volver al men%c): ",168,163);

        do
        {

            fflush(stdin);
            scanf("%c",&op);

        }
        while (op != 's' && op != 'S' && op != 'n' && op != 'N');

        if(op == 's' || op == 'S')
        {

            system("cls");

            printf("%cQu%c deseas editar?",168,130);
            printf("\n1.Nick: %s",(*player)[auxi].nick);
            printf("\n2.Nombre: %s",(*player)[auxi].name);
            printf("\n3.Contrase%ca: %s\n",164,(*player)[auxi].pass);

            printf("\nIntroduce cualquier otro n%cmero para volver al men%c principal\n",163,163);

            fflush(stdin);
            scanf("%d",&selec);

            switch(selec)
            {

            case 1:
                printf("Introduce tu nuevo nick: ");

                fflush(stdin);
                fgets(aux,15,stdin);

                aux[strlen(aux) - 1] = '\0';
                strcpy((*player)[auxi].nick,aux);

                break;

            case 2:
                printf("Introduce tu nuevo nombre: ");

                fflush(stdin);
                fgets(aux,25,stdin);

                aux[strlen(aux) - 1] = '\0';
                strcpy((*player)[auxi].name,aux);

                break;

            case 3:
                printf("Introduce tu nueva contrase%ca",164);

                fflush(stdin);
                fgets(aux,15,stdin);

                aux[strlen(aux) - 1] = '\0';
                strcpy((*player)[auxi].pass,aux);

                break;
            }
        }

        system("cls");

    }
    while(op != 'n' && op != 'N');
}



//Cabecera: void ajustes(r_config *config,r_item **obj,r_elem elems)
//Precondición: config, obj y elems inicializados
//Postcondición: permite cambiar los ajustes
void ajustes(r_config *config,r_elem elems,r_item **obj, r_storm **storm)
{

    char op;

    int selec,cambio,i;

    printf(" ------------\n | Ajustes |\n ------------");

    printf("Qu%c deseas modificar?\na.Configuraci%cn\nb.Objetos\nc.Tormenta\n",130,162);

    fflush(stdin);

    scanf("%c",&op);

    system("cls");

    printf(" ------------\n | Ajustes |\n ------------");

    switch(op)
    {

    case 'a':


        printf("1.Radio del mapa: %d\n",config->radius_map);
        printf("2.Alcance para recoger objetos: %d\n",config->pick_range);
        printf("3.Rango de visi%cn: %d\n",162,config->vis_range);
        printf("4.Monedas por defecto: %d\n",config->def_gold);
        printf("5.Da%co del arma por defecto: %d\n",164,config->def_dmg);
        printf("6.Rango del arma por defecto: %d\n",config->def_range);
        printf("7.Monedas por victoria: %d\n",config->win_gold);
        printf("8.M%cximo de jugadores para comenzar la partida: %d\n",160,config->min_player);
        printf("9.Distancia de movimiento del jugador: %d\n",config->step_dist);
        printf("10.Capacidad de la mochila: %d\n",config->capac_bag);
        printf("11.Victorias para subir de nivel: %d\n",config->win_lvl);
        printf("12.N%cmero m%cximo de acciones por turno: %d\n",163,160,config->max_act);

        fflush(stdin);

        printf("\nIntroduce cualquier otro n%cmero para volver al men%c principal\n",163,163);

        scanf("%d",&selec);

        if(selec <= 12)
            printf("\n\nIntroduce el nuevo valor: ");

        switch(selec)
        {

        case 1:

            fflush(stdin);
            scanf("%d",&cambio);

            config->radius_map = cambio;

            break;

        case 2:

            fflush(stdin);
            scanf("%d",&cambio);

            config->pick_range = cambio;

            break;

        case 3:

            fflush(stdin);
            scanf("%d",&cambio);

            config->vis_range = cambio;

            break;

        case 4:

            fflush(stdin);
            scanf("%d",&cambio);

            config->def_gold = cambio;

            break;

        case 5:

            fflush(stdin);
            scanf("%d",&cambio);

            config->def_dmg = cambio;

            break;

        case 6:

            fflush(stdin);
            scanf("%d",&cambio);

            config->def_range = cambio;

            break;

        case 7:

            fflush(stdin);
            scanf("%d",&cambio);

            config->win_gold = cambio;

            break;

        case 8:

            fflush(stdin);
            scanf("%d",&cambio);

            config->min_player = cambio;

            break;

        case 9:

            fflush(stdin);
            scanf("%d",&cambio);

            config->step_dist = cambio;

            break;

        case 10:

            fflush(stdin);
            scanf("%d",&cambio);

            config->capac_bag = cambio;

            break;

        case 11:

            fflush(stdin);
            scanf("%d",&cambio);

            config->win_lvl = cambio;

            break;

        case 12:

            fflush(stdin);
            scanf("%d",&cambio);

            config->max_act = cambio;

            break;

        }

        break;

    case 'b':

        system("cls");

        puts("Elige lo que desees modificar");

        for(i = 0; i < elems.itm; i++)
            printf("%d.%s\n", i+1, (*obj)[i].descrip);

        scanf("%d", &i);
        i--;

        system("cls");

        if(i < elems.itm && i >= 0)
        {

            if(strcmp((*obj)[i].type,"Arma") == 0)
            {


                printf("1.Precio: %d\n",(*obj)[i].cost);
                printf("2.Alcance: %d\n",(*obj)[i].range);
                printf("3.Da%co: %d\n",164,(*obj)[i].effect);
                printf("4.Munici%cn por defecto: %d\n",162,(*obj)[i].def_ammo);
                printf("5.M%cximo de disparos por turno: %d\n",160,(*obj)[i].max_shot);

                printf("\nIntroduce cualquier otro n%cmero positivo para volver al men%c principal\n",163,163);

                fflush(stdin);
                scanf("%d",&selec);

                if(selec <= 5 && selec > 0)
                    printf("\n\nIntroduce el nuevo valor: ");

                switch(selec)
                {

                case 1:

                    scanf("%d",&cambio);
                    (*obj)[i].cost = cambio;

                    break;

                case 2:

                    scanf("%d",&cambio);
                    (*obj)[i].range = cambio;

                    break;

                case 3:

                    scanf("%d",&cambio);
                    (*obj)[i].effect = cambio;

                    break;

                case 4:

                    scanf("%d",&cambio);
                    (*obj)[i].def_ammo = cambio;

                    break;

                case 5:

                    scanf("%d",&cambio);
                    (*obj)[i].max_shot = cambio;

                    break;
                }
            }
            else
            {

                printf("1.Precio: %d\n",(*obj)[i].cost);
                printf("2.Curaci%cn: %d\n",162,(*obj)[i].effect);
                printf("3.Unidades por defecto: %d\n",(*obj)[i].def_ammo);

                printf("\nIntroduce cualquier otro n%cmero positivo para volver al men%c principal\n",163,163);

                fflush(stdin);
                scanf("%d",&selec);

                if(selec <= 3 && selec > 0)
                    printf("\n\nIntroduce el nuevo valor: ");

                switch(selec)
                {

                case 1:

                    scanf("%d",&cambio);
                    (*obj)[i].cost = cambio;

                    break;

                case 2:

                    scanf("%d",&cambio);
                    (*obj)[i].effect = cambio;

                    break;

                case 3:

                    scanf("%d",&cambio);
                    (*obj)[i].def_ammo = cambio;

                    break;
                }
            }
        }
        break;

    case 'c':

        system("cls");

        puts("Elige la fase que quieres modificar\n");

        for(i = 0; i < elems.stg; i++)
            printf("%d.- Radio: %d\nTurnos hasta que se cierre la zona: %d\n\n",i+1,(*torm)[i].radius,(*torm)[i].turns);

        scanf("%d",&i);
        i--;

        system("cls");

        if(i < elems.stg && i >= 0)
        {
            printf("Elige lo que desees modificar\n\n");

            printf("1.Radio actual: %d\n2.Turnos hasta que se cierre la zona actuales: %d\n",(*torm)[i].radius,(*torm)[i].turns);
            printf("\nIntroduce cualquier otro n%cmero para volver al men%c principal\n ",163,163);

            fflush(stdin);
            scanf("%d",&selec);

            switch(selec)
            {

            case 1:
                printf("Introduce el nuevo valor: ");

                fflush(stdin);
                scanf("%d",&cambio);

                (*torm)[i].radius = cambio;

                break;

            case 2:
                printf("Introduce el nuevo valor: ");

                fflush(stdin);
                scanf("%d",&cambio);

                (*torm)[i].turns = cambio;

                break;
            }
        }
        break;
    }
}


//Cabecera: int cuenta_objetos(r_player player);
//Precondición: player inicializada
//Postcondición: devuelve el numero de objetos de un jugador
int cuenta_objetos(r_player player,r_config config)
{
    int cont = 0;
    while((strcmp(player.bag[cont].id_item, "\0") != 0) && (cont < config.capac_bag))
        cont++;
    return cont;
}


//Cabecera void tienda(r_player **player,r_config config,r_elem elems,r_item *obj,int auxi)
//Precondicion: player, config,elems,obj inicializados
//Postcondicion: permite adquirir nuevos objetos
void tienda(r_player **player,r_config config,r_elem elems,r_item *obj,int auxi)
{

    int i, j, nobj, contaux;

    char sn;

    do
    {
        system("cls");
        printf(" ----------\n | Tienda |\n ----------\n\n");
        j = 0;
        contaux = 0;

        nobj = cuenta_objetos((*player)[auxi], config);

        printf("Dinero actual: %d KiBitcoins\n\n",(*player)[auxi].gold);

        printf("%cQu%c deseas comprar?\n\n",168,130);

        for(i = 0; i < elems.itm; i++)
            printf("%d.-%s --> %d KiBitcoins\n", i+1, obj[i].descrip, obj[i].cost);

        do
        {
            fflush(stdin);
            scanf("%d",&i);
            i--;
            if((*player)[auxi].gold < obj[i].cost)
                printf("\nNo tienes dinero suficiente\n\nElige otro objeto\n\n");

        }
        while(i < elems.itm && i >= 0 && (*player)[auxi].gold < obj[i].cost);

        if(i < elems.itm && i >= 0)
        {

            while(strcmp(obj[i].id,(*player)[auxi].bag[j].id_item) != 0 && j < nobj && contaux != 1) 		//El ultimo elemento se comprueba 2 veces, la segunda vez que lo hace es la que determina si el objeto que ha elegido se encuentra o no dentro de su mochila
            {
                if (j != nobj - 1)
                    j++;
                else
                    contaux = 1;		//Si contaux = 1, ningun elemento de la mochila coincide con el elegido
            }

            if(nobj == 0)
                contaux = 1;

        }

        if (contaux == 0)
        {

            (*player)[auxi].gold -= obj[i].cost;
            (*player)[auxi].bag[j].quant += obj[i].def_ammo;

        }
        else if(nobj == config.capac_bag)
            printf("No tienes espacio suficiente en la mochila");

        else
        {

            (*player)[auxi].gold -= obj[i].cost;
            if(j == 0 && nobj == 0)
            {
                strcpy((*player)[auxi].bag[j].id_item, obj[i].id);
                (*player)[auxi].bag[j].quant = obj[i].def_ammo;
            }
            else
            {

                strcpy((*player)[auxi].bag[j+1].id_item, obj[i].id);
                (*player)[auxi].bag[j+1].quant = obj[i].def_ammo;
            }
        }
        do
        {
            printf("%cQuieres seguir comprando? (s/n) ",168);
            fflush(stdin);
            scanf("%c",&sn);
        }
        while(sn != 'n' && sn != 'N' && sn != 's' && sn != 'S');

    }
    while(sn == 's' || sn == 'S');
}

//Cabecera: void menu_principal(r_player **player,r_config *config,r_elem *elems,r_item **obj,int *auxi);
//Precondicion: player, config, elems, obj, auxi inicializados
//Postcondicion: inicia el menu principal
void menu_principal(r_player **player, r_config *config, r_elem *elems, r_item **obj, int *auxi, int opaux, r_storm **storm, r_coord **coord)
{
    int mselec,auxadmin = 0,auxjgd;

    do
    {

        if(opaux == 0)
        {
            login(player, elems, auxi,*config);
        }

        auxjgd = 0;
        system("cls");
        mostrar_menu_princ((*player),*auxi);
        opaux = 1;
        if(strcmp((*player)[*auxi].type,"JGD") == 0)  		//Menu jugador
        {

            do
            {
                printf("\n\nElige una opci%cn: ",162);
                fflush(stdin);
                scanf("%d",&mselec);
                auxjgd = mselec;

                if (mselec < 1 || mselec > 5)
                    printf("\nERROR. Introduce un n%cmero del 1 al 5\n",163);
            }
            while(mselec < 1 || mselec > 5);

            switch(mselec)
            {
            case 1:
                system("cls");
                jugar(player, *auxi, *config, *elems);
                system("cls");
                break;

            case 2:
                system("cls");
                ver_perfil(player, *auxi);
                system("cls");
                break;

            case 3:
                system("cls");
                tienda(player, *config, *elems, *obj, *auxi);
                system("cls");
                break;

            case 4:
                opaux = 0;
                system("cls");
                break;

            case 5:
                printf("\n\nHasta luego!");
                break;
            }
        }

        else  		//Menu admin
        {
            do
            {
                printf("\n\nElige una opci%cn: ",162);
                fflush(stdin);
                scanf("%d",&mselec);
                auxadmin = mselec;

                if (mselec < 1 || mselec > 7)
                    printf("\nERROR. Introduce un n%cmero del 1 al 7\n",163);
            }
            while(mselec < 1 || mselec > 7);

            switch(mselec)
            {
            case 1:
                system("cls");
                jugar(player, *auxi, *config, *elems);
                system("cls");
                break;

            case 2:
                system("cls");
                comienzo_forzoso(player,*elems);
                break;

            case 3:
                system("cls");
                ver_perfil(player, *auxi);
                system("cls");
                break;

            case 4:
                system("cls");
                tienda(player,*config,*elems,*obj,*auxi);
                system("cls");
                break;

            case 5:
                system("cls");
                ajustes(config, *elems, obj, torm);
                break;

            case 6:
                opaux = 0;
                system("cls");
                break;

            case 7:
                printf("\n\nHasta luego!");
                break;
            }
        }
    }
    while(auxjgd != 5 && auxadmin != 7);
}
