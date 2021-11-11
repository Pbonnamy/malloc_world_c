#ifndef PLAYER_H
#define PLAYER_H

#include "header.h"

struct Inventory{
    int value;
    int quantity;
    Inventory *next;
};

struct Player{
    int level;
    int xp;
    int maxHp;
    int currentHp;
    int row;
    int column;
    Inventory *inventory;
};

enum items{
    _woodSword = 1,
    _woodPickaxe = 2,
    _woodBillhook = 3,
    _woodAxe = 4,
    _stoneSword = 8,
    _stoneSpear = 9,
    _stoneHammer = 10,
    _stoneArmor = 11,
    _stonePickaxe = 12,
    _stoneBillhook = 13,
    _stoneAxe = 14,
    _ironSword = 19,
    _ironSpear = 20,
    _ironHammer = 21,
    _ironArmor = 22,
    _ironPickaxe = 23,
    _ironBillhook = 24,
    _ironAxe = 25,
    _diamondSword = 30,
    _diamondSpear = 31,
    _diamondHammer = 32,
    _diamondArmor = 33,
    _potion1 = 15,
    _potion2 = 26,
    _potion3 = 34
};

#endif

