#ifndef ESTRUCT_H_INCLUDED
#define ESTRUCT_H_INCLUDED

#ifndef LIBRARIES
#define LIBRARIES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#endif // LIBRARIES

typedef struct
{
    char id_item[6];
    int quant, equipped;
} r_bag;
//fasilito/FRC01/15

typedef struct
{
    char nick[15], name[25], status[4], type[4], pass[15];
    int lvl, life, shield, gold, games, wins, order;
    r_bag *bag;
} r_player;

typedef struct
{
    char id[6], descrip[25], type[9];
    int cost, range, effect, def_ammo, max_shot;
} r_item;

typedef struct
{
    int x, y, radius, turns;
} r_storm;

typedef struct
{
    char type[15], id_nick[15];
    int x, y;
} r_coord;

typedef struct
{
    int radius_map, pick_range, vis_range, def_gold, def_dmg, def_range;
    int win_gold, min_player, step_dist, capac_bag, win_lvl, max_act;
} r_config;

typedef struct
{
    int ply, itm, bag, stg, coord;
}r_elem;

void get_elems(r_elem *elems);
void files_struct(r_player *, r_item *, r_storm *, r_config *, r_elem);
void struct_files(r_player *, r_item *, r_storm *, r_config, r_elem);

#endif // ESTRUCT_H_INCLUDED
