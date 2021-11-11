#ifndef COMBAT_H
#define COMBAT_H

#include "header.h"

struct Monster {
    int maxHp;
    int currentHp;
    int damage;
    int respawn;
    int row;
    int column;
};

struct MonsterList{
    Monster *monster;
    MonsterList *next;
};

#endif
