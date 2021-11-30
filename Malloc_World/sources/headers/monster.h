#ifndef COMBAT_H
#define COMBAT_H

#include "header.h"

struct MonsterNode{
    int hp;
    int respawn;
    int row;
    int column;
    int value;
    int reference;
    MonsterNode *next;
};

#endif
