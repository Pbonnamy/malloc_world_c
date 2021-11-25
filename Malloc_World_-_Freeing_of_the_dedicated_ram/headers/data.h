#ifndef DATA_H
#define DATA_H

#include "header.h"

enum dataType{
    _entity = 0,
    _name = 1,
    _info = 2,
    _mapRessource = 0,
    _itemRessource = 1,
    _ressource = 0,
    _firstPossibleTool = 1,
    _lastPossibleTool = 3,
    _monsterHp = 2,
    _monsterDamage = 3,
    _monsterXp = 4,
    _level = 0,
    _xpRequired = 1,
    _levelBonus = 2,
    _noStorageLimit = 0,
    _nothing = -1,
    _item = 0,
    _minCraftlvl = 1,
    _craftRessource1 = 2,
    _craftQuantity1 = 3,
    _craftRessource2 = 4,
    _craftQuantity2 = 5,
};

#endif
