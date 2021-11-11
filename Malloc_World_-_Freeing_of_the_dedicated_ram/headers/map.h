#ifndef MAP_H
#define MAP_H

#include "header.h"

struct Levels{
    int **lv1;
    int **lv2;
    int **lv3;
    int rows;
    int columns;
};

struct Level{
    int **map;
    RessourceList ressourceList;
    MonsterList monsterList;
    int value;
};

enum mapEntity{
    player = 1,
    portal2 = -3,
    portal1 = -2,
    wall = -1,
    npc = 2,
    plant1 = 3,
    rock1 = 4,
    wood1 = 5,
    plant2 = 6,
    rock2 = 7,
    wood2 = 8,
    plant3 = 9,
    rock3 = 10,
    wood3 = 11,
    monster1 = 12,
    monster2 = 22,
    monster3 = 32,
    lastMonster = 42,
    boss = 99
};

#endif
