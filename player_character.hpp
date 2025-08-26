#ifndef PLAYER_CHARACTER_H
# define PLAYER_CHARACTER_H

typedef struct    s_pc t_pc;

typedef struct    s_pc
{
    char    *name;
    int        initiative;
    t_pc    *next;
} t_pc;

#endif
