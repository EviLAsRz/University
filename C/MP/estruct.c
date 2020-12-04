#include "estruct.h"

int strToInt(char *);
char *intToStr(int);
void ply_struct(r_player *, r_elem);
void itm_struct(r_item *, r_elem);
void bag_struct(r_player *, r_elem);
void stg_struct(r_storm *, r_elem);
void cfg_struct(r_config *);
void ply_file(r_player *, r_elem);
void itm_file(r_item *, r_elem);
void bag_file(r_player *, r_elem, r_config);
void stg_file(r_storm *, r_elem);
void cfg_file(r_config);


//Cabecera: void get_elems(r_elem *elems)
//Precondición: elems inicializado y los ficheros creados en el directorio
//Postcondición: Guarda el número de elementos de cada fichero en el registro
void get_elems(r_elem *elems)
{
    FILE *f_ply, *f_itm, *f_bag, *f_stg;

    f_ply = fopen("Jugadores.txt", "r");
    f_itm = fopen("Objetos.txt", "r");
    f_bag = fopen("Mochilas.txt", "r");
    f_stg = fopen("Tormenta.txt", "r");

    elems->ply = 0;
    elems->itm = 0;
    elems->bag = 0;
    elems->stg = 0;
    elems->coord = 0;
    char c;

    c = fgetc(f_ply);
    while(c != EOF)
    {
        if(c == '\n')
            elems->ply++;
        c = fgetc(f_ply);
        if(c == EOF)
            elems->ply++;
    }

    c = fgetc(f_itm);
    while(c != EOF)
    {
        if(c == '\n')
            elems->itm++;
        c = fgetc(f_itm);
        if(c == EOF)
            elems->itm++;
    }

    c = fgetc(f_bag);
    while(c != EOF)
    {
        if(c == '\n')
            elems->bag++;
        c = fgetc(f_bag);
        if(c == EOF)
            elems->bag++;
    }

    c = fgetc(f_stg);
    while(c != EOF)
    {
        if(c == '\n')
            elems->stg++;
        c = fgetc(f_stg);
        if(c == EOF)
            elems->stg++;
    }

    fclose(f_ply);
    fclose(f_itm);
    fclose(f_bag);
    fclose(f_stg);
}

//Cabecera:void files_struct(r_player *v_ply, r_item *v_itm, r_bag *v_bag, r_storm *v_stg, r_config *cfg, r_elem elems)
//Precondición: v_ply, v_itm, v_bag, v_stg, cfg y elems inicializados, y los ficheros creados.
//Postcondición: Transfiere la información de los ficheros a las estructuras.
void files_struct(r_player *v_ply, r_item *v_itm, r_storm *v_stg, r_config *cfg, r_elem elems)
{
    ply_struct(v_ply, elems);
    itm_struct(v_itm, elems);
    bag_struct(v_ply, elems);
    stg_struct(v_stg, elems);
    cfg_struct(cfg);
}

//Cabecera: void struct_files(r_player *v_ply, r_item *v_itm, r_bag *v_bag, r_storm *v_stg, r_config cfg, r_elem elems)
//Precondición: v_ply, v_itm, v_bag, v_stg, cfg y elems inicializado
//Postcondición: Transfiere la información de las estructuras a los ficheros
void struct_files(r_player *v_ply, r_item *v_itm, r_storm *v_stg, r_config cfg, r_elem elems)
{
    ply_file(v_ply, elems);
    itm_file(v_itm, elems);
    bag_file(v_ply, elems, cfg);
    stg_file(v_stg, elems);
    cfg_file(cfg);
}

//Cabecera: int strToInt(char *cad)
//Precondición: cad inicializado
//Postcondición: devuelve la cadena convertida a entero
int strToInt(char *cad)
{
    return (int) strtol(cad, NULL, 10);
}

//Cabecera: char *intToStr(int x)
//Precondición: x inicializado
//Postcondición: devuelve el número en forma de cadena
char *intToStr(int x)
{
    char *aux;
    aux = (char *) malloc(5);
    sprintf(aux, "%d", x);
    return aux;
    free(aux);
}

//Cabecera: void ply_struct(r_player *v_ply, r_elem elems)
//Precondición: v_ply y elems inicializados
//Postcondición: transfiere la información del fichero "Jugadores" a la estructura
void ply_struct(r_player *v_ply, r_elem elems)
{
    FILE *f_ply;
    int i, j;
    char cad[80], *str[8];
    //str es un vector de cadenas en el que y e los tokens devueltos por strtok
    //El número de elementos representa los campos del fichero
    if(elems.ply > 0)
    {
        f_ply = fopen("Jugadores.txt", "r");
        if(f_ply != NULL)
        {
            for(i = 0; i < elems.ply; i++)
            {
                //Leo cada linea del fichero
                fgets(cad, 80, f_ply);
                if(i < elems.ply -1)
                    cad[strlen(cad) - 1] = '\0';
                //En str guardo los tokens
                str[0] = strtok(cad, "/");
                for(j = 1; j < 8; j++) //8 es el numero de campos del fichero ply
                    str[j] = strtok(NULL, "/");

                //Una vez tengo las cadenas en str, las paso al vector
                strcpy(v_ply[i].nick, str[0]);
                strcpy(v_ply[i].name, str[1]);
                //Convierto las cadenas en enteros
                v_ply[i].lvl = strToInt(str[2]);
                v_ply[i].gold = strToInt(str[3]);
                v_ply[i].games = strToInt(str[4]);
                v_ply[i].wins = strToInt(str[5]);
                strcpy(v_ply[i].type, str[6]);
                strcpy(v_ply[i].pass, str[7]);

                fseek(f_ply, 0, SEEK_CUR);
            }
        }
        fclose(f_ply);
    }
}

//Cabecera: void itm_struct(r_item *v_itm, r_elem elems)
//Precondición: v_itm y elems inicializados
//Postcondición: transfiere la información del fichero "Objetos" a la estructura
void itm_struct(r_item *v_itm, r_elem elems)
{
    FILE *f_itm;
    int i, j;
    char cad[64], *str[8];
    //Compruebo si hay elementos en el fichero
    if(elems.itm > 0)
    {
        f_itm = fopen("Objetos.txt", "r");
        if(f_itm != NULL)
        {
            for(i = 0; i < elems.itm; i++)
            {
                //Leo cada linea del fichero
                fgets(cad, 64, f_itm);


                if(i < elems.itm -1)
                    cad[strlen(cad) - 1] = '\0';
                //En str guardo los tokens
                str[0] = strtok(cad, "/");
                for(j = 1; j < 8; j++) //7 es el numero de campos del fichero itm
                    str[j] = strtok(NULL, "/");

                //Una vez tengo las cadenas en str, las paso al vector
                strcpy(v_itm[i].id, str[0]);
                strcpy(v_itm[i].descrip, str[1]);
                strcpy(v_itm[i].type, str[2]);
                //Convierto las cadenas en enteros
                v_itm[i].cost = strToInt(str[3]);
                v_itm[i].range = strToInt(str[4]);
                v_itm[i].effect = strToInt(str[5]);
                v_itm[i].def_ammo = strToInt(str[6]);
                v_itm[i].max_shot = strToInt(str[7]);

                fseek(f_itm, 0, SEEK_CUR);
            }
        }
        fclose(f_itm);
    }
}

//Cabecera: void bag_struct(r_bag *v_bag, r_elem elems)
//Precondición: v_bag y elems inicializados
//Postcondición: transfiere la información del fichero "Mochilas" a la estructura
void bag_struct(r_player *v_ply, r_elem elems)
{
    FILE *f_bag;
    int i, j, k, l, cont, acum;
    char cad[30], *str[3], aux_nick[elems.bag][15], aux[30];
    //Compruebo si hay elementos en el fichero
    if(elems.bag > 0)
    {
        f_bag = fopen("Mochilas.txt", "r");
        if(f_bag != NULL)
        {
            //Llenar vector aux_nick
            //En este vector almaceno los nombres de los jugadores en el fichero "Mochilas"
            //para facilitar su uso
            for(i = 0; i < elems.bag; i++)
            {
                fgets(cad, 30, f_bag);
                if(i < elems.bag -1)
                    cad[strlen(cad) - 1] = '\0';
                strcpy(aux, cad);
                strcpy(aux_nick[i], strtok(aux, "/"));
            }
            rewind(f_bag);
            j = 0;
            //En j tiene que estar el indice de la primera aparicion del nombre en aux_nick
            acum = 0;
            l = 0;
            while(j < elems.bag)
            {
                cont = 0;
                //Cuento las apariciones del nombre en el vector de jugadores
                for(k = j; k < elems.bag; k++)
                {
                    if((strcmp(aux_nick[j], aux_nick[k])) == 0)
                        cont++;
                }

                //Encontrar aux_nick[j] en v_ply. y guardarlos en i
                i = 0;
                while((strcmp(aux_nick[j], v_ply[i].nick)) != 0 && i < elems.ply)
                    i++;
                //Leo las cadenas del fichero y lo cargo en las estructuras
                for(j = 0; j < cont; j++)
                {
                    fgets(cad, 30, f_bag);
                    if(l < elems.bag -1) //Elimino el salto de linea de la cadena, solo si no es la ultima linea del fichero
                        cad[strlen(cad) - 1] = '\0';
                    l++;
                    str[0] = strtok(cad, "/");
                    for(k = 1; k < 3; k++) //3 es el numero de campos del fichero bag
                        str[k] = strtok(NULL, "/");
                    strcpy(v_ply[i].bag[j].id_item, str[1]);
                    v_ply[i].bag[j].quant = strToInt(str[2]);
                }
                acum += cont;
                j = acum;
            }
        }
        fclose(f_bag);
    }
}

//Cabecera: void stg_struct(r_storm *v_stg, r_elem elems)
//Precondición: v_stg y elems inicializados
//Postcondición: transfiere la información del fichero "Tormenta" a la estructura
void stg_struct(r_storm *v_stg, r_elem elems)
{
    FILE *f_stg;
    int i;
    char cad[8], *str[2];
    //Compruebo si hay elementos en el fichero
    if(elems.stg > 0)
    {
        f_stg = fopen("Tormenta.txt", "r");
        if(f_stg != NULL)
        {
            for(i = 0; i < elems.stg; i++)
            {
                //Leo cada linea del fichero
                fgets(cad, 8, f_stg);
                if(i < elems.stg -1)
                    cad[strlen(cad) - 1] = '\0';

                //En str guardo los tokens
                str[0] = strtok(cad, "/");
                str[1] = strtok(NULL, "/");
                //Una vez tengo las cadenas en str, las paso al vector
                v_stg[i].radius = strToInt(str[0]);
                v_stg[i].turns = strToInt(str[1]);

                fseek(f_stg, 0, SEEK_CUR);
            }
        }
        fclose(f_stg);
    }
}

//Cabecera: void cfg_struct(r_config *config)
//Precondición: config inicializado
//Postcondición: transfiere la información del fichero "Configuracion" a la estructura
void cfg_struct(r_config *config)
{
    FILE *f_cfg;
    int i;
    char cad[48], *str[12];
    f_cfg = fopen("Configuracion.txt", "r");
    if(f_cfg != NULL)
    {
        //Leo cada linea del fichero
        fgets(cad, 48, f_cfg);

        i = 0;
        //En str guardo los tokens
        str[0] = strtok(cad, "/");
        for(i = 1; i < 12; i++) //11 es el numero de campos del fichero config
            str[i] = strtok(NULL, "/");

        //Una vez tengo las cadenas en str, las paso al vector
        config->radius_map = strToInt(str[0]);
        config->pick_range = strToInt(str[1]);
        config->vis_range = strToInt(str[2]);
        config->def_gold = strToInt(str[3]);
        config->def_dmg = strToInt(str[4]);
        config->def_range = strToInt(str[5]);
        config->win_gold = strToInt(str[6]);
        config->min_player = strToInt(str[7]);
        config->step_dist = strToInt(str[8]);
        config->capac_bag = strToInt(str[9]);
        config->win_lvl = strToInt(str[10]);
        config->max_act = strToInt(str[11]);
    }
    fclose(f_cfg);
}

//Cabecera: void ply_file(r_player *v_ply, r_elem elems)
//Precondición: v_ply y elems inicializados
//Postcondición: pasa la información del registro al fichero "Jugadores"
void ply_file(r_player *v_ply, r_elem elems)
{
    int i = 0;
    FILE *f_ply;
    f_ply = fopen("Jugadores.txt", "w");
    if(f_ply != NULL)
    {
        while (i < elems.ply)
        {
            if(i < elems.ply - 1)
            {
                fprintf(f_ply, "%s/%s/%s/%s/%s/%s/%s/%s\n", v_ply[i].nick, v_ply[i].name,
                        intToStr(v_ply[i].lvl), intToStr(v_ply[i].gold), intToStr(v_ply[i].games),
                        intToStr(v_ply[i].wins), v_ply[i].type, v_ply[i].pass);
            }
            else
            {
                fprintf(f_ply, "%s/%s/%s/%s/%s/%s/%s/%s", v_ply[i].nick, v_ply[i].name,
                        intToStr(v_ply[i].lvl), intToStr(v_ply[i].gold), intToStr(v_ply[i].games),
                        intToStr(v_ply[i].wins), v_ply[i].type, v_ply[i].pass);
            }
            i++;
        }
    }
    fclose(f_ply);
}

//Cabecera: void itm_file(r_item *v_itm, r_elem elems)
//Precondición: v_itm y elems inicializados
//Postcondición: pasa la información del registro al fichero "Objetos"
void itm_file(r_item *v_itm, r_elem elems)
{
    int i = 0;
    FILE *f_itm;
    f_itm = fopen("Objetos.txt", "w");
    if(f_itm != NULL)
    {
        while (i < elems.itm)
        {
            if(i < elems.itm - 1)
            {
                fprintf(f_itm, "%s/%s/%s/%s/%s/%s/%s/%s\n", v_itm[i].id, v_itm[i].descrip,
                        v_itm[i].type,intToStr(v_itm[i].cost), intToStr(v_itm[i].range),
                        intToStr(v_itm[i].effect), intToStr(v_itm[i].def_ammo), intToStr(v_itm[i].max_shot));
            }
            else
            {
                fprintf(f_itm, "%s/%s/%s/%s/%s/%s/%s/%s", v_itm[i].id, v_itm[i].descrip,
                        v_itm[i].type,intToStr(v_itm[i].cost), intToStr(v_itm[i].range),
                        intToStr(v_itm[i].effect), intToStr(v_itm[i].def_ammo), intToStr(v_itm[i].max_shot));
            }
            i++;
        }
    }
    fclose(f_itm);
}

//Cabecera: void bag_file(r_bag *v_bag, r_elem elems)
//Precondición: v_bag y elems inicializados
//Postcondición: pasa la información del registro al fichero "Mochilas"
void bag_file(r_player *v_ply, r_elem elems, r_config config)
{
    int i = 0, j;
    int cont;
    FILE *f_bag;
    f_bag = fopen("Mochilas.txt", "w");
    if(f_bag != NULL)
    {
        while (i < elems.ply)
        {
            cont = 0;
            while((strcmp(v_ply[i].bag[cont].id_item, "\0") != 0) && (cont < config.capac_bag))
                cont++;
            if(i != elems.ply - 1) //Comprueba si es el ultimo elemento del vector jugadores
            {
                    for(j = 0; j < cont; j++)
                        fprintf(f_bag, "%s/%s/%s\n", v_ply[i].nick, v_ply[i].bag[j].id_item, intToStr(v_ply[i].bag[j].quant));
            }
            else
            {
                //Imprime en el fichero los datos y un salto de linea, excepto en la ultima linea que acaba con el EOF
                if(cont > 0)
                {
                    for(j = 0; j < cont - 1; j++)
                        fprintf(f_bag, "%s/%s/%s\n", v_ply[i].nick, v_ply[i].bag[j].id_item, intToStr(v_ply[i].bag[j].quant));
                    fprintf(f_bag, "%s/%s/%s", v_ply[i].nick, v_ply[i].bag[j].id_item, intToStr(v_ply[i].bag[j].quant));
                }
            }

            i++;
        }
    }
    fclose(f_bag);
}
//Cabecera: void stg_file(r_storm *v_stg, r_elem elems)
//Precondición: v_stg y elems inicializados
//Postcondición: pasa la información del registro al fichero "Tormenta"
void stg_file(r_storm *v_stg, r_elem elems)
{
    int i = 0;
    FILE *f_stg;
    f_stg = fopen("Tormenta.txt", "w");
    if(f_stg != NULL)
    {
        while (i < elems.stg)
        {
            if(i < elems.stg - 1)
            {
                fprintf(f_stg, "%s/%s\n", intToStr(v_stg[i].radius), intToStr(v_stg[i].turns));
            }
            else
            {
                fprintf(f_stg, "%s/%s", intToStr(v_stg[i].radius), intToStr(v_stg[i].turns));
            }
            i++;
        }
    }
    fclose(f_stg);
}

//Cabecera: void cfg_file(r_config cfg)
//Precondición: cfg inicializado
//Postcondición:pasa la información del registro al fichero "Configuracion"
void cfg_file(r_config cfg)
{
    FILE *f_cfg;
    f_cfg = fopen("Configuracion.txt", "w");
    if(f_cfg != NULL)
    {
        fprintf(f_cfg, "%s/%s/%s/%s/%s/%s/%s/%s/%s/%s/%s/%s", intToStr(cfg.radius_map), intToStr(cfg.pick_range),
                intToStr(cfg.vis_range), intToStr(cfg.def_gold), intToStr(cfg.def_dmg), intToStr(cfg.def_range),
                intToStr(cfg.win_gold), intToStr(cfg.min_player), intToStr(cfg.step_dist),
                intToStr(cfg.capac_bag), intToStr(cfg.win_lvl), intToStr(cfg.max_act));
    }
    fclose(f_cfg);
}
