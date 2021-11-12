#ifndef COMBAT_H
#define COMBAT_H

#include "header.h"

struct MonsterNode{
    int maxHp;
    int currentHp;
    int damage;
    int respawn;
    int row;
    int column;
    int value;
    MonsterNode *next;
};

#endif
