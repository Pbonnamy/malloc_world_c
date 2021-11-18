#ifndef PLAYER_H
#define PLAYER_H

#include "header.h"

struct InventoryNode{
    int value;
    int quantity;
    int reference;
    int durability;
    InventoryNode *next;
};

struct Player{
    int level;
    int xp;
    int maxHp;
    int currentHp;
    int row;
    int column;
    int currentMapLvl;
    InventoryNode *inventory;
};

#endif

