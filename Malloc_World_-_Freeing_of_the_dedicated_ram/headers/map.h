#ifndef MAP_H
#define MAP_H

#include "header.h"

struct Levels{
    Level *lv1;
    Level *lv2;
    Level *lv3;
    int rows;
    int columns;
};

struct Level{
    int **map;
    RessourceNode *ressourceList;
    MonsterNode *monsterList;
    int value;
};

enum mapEntity{
    _empty = 0,
    _player = 1,
    _portal2 = -3,
    _portal1 = -2,
    _wall = -1,
    _npc = 2,
    _plant1 = 3,
    _rock1 = 4,
    _wood1 = 5,
    _plant2 = 6,
    _rock2 = 7,
    _wood2 = 8,
    _plant3 = 9,
    _rock3 = 10,
    _wood3 = 11,
    _monster1 = 12,
    _monster2 = 17,
    _monster3 = 22,
    _lastMonster = 27,
    _boss = 99
};

#endif
