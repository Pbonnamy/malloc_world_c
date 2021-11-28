#include "../headers/header.h"

//{"entity", "name", "additionnal informations"}
                        //armor -> damage resistance
                        //weapon -> damage
                        //potion -> hp restored
char ITEMS[TOTAL_ITEMS][3][32] = {
    {"1", "Wood Sword", "1"},
    {"2", "Wood Pickaxe", ""},
    {"3", "Wood Billhook", ""},
    {"4", "Wood Axe", ""},
    {"5", "Fir", ""},
    {"6", "Stone", ""},
    {"7", "Herb", ""},
    {"8", "Stone Sword", "2"},
    {"9", "Stone Spear", "3"},
    {"10", "Stone Hammer", "4"},
    {"11", "Stone Armor", "10"},
    {"12", "Stone Pickaxe", ""},
    {"13", "Stone BillHook", ""},
    {"14", "Stone Axe", ""},
    {"15", "Health Potion I", "30"},
    {"16", "Beech", ""},
    {"17", "Iron", ""},
    {"18", "Lavender", ""},
    {"19", "Iron Sword", "5"},
    {"20", "Iron Spear", "7"},
    {"21", "Iron Hammer", "10"},
    {"22", "Iron Armor", "20"},
    {"23", "Iron Pickaxe", ""},
    {"24", "Iron Billhook", ""},
    {"25", "Iron Axe", ""},
    {"26", "Health Potion II", "80"},
    {"27", "Oak", ""},
    {"28", "Diamond", ""},
    {"29", "Hemp", ""},
    {"30", "Diamond Sword", "10"},
    {"31", "Diamond Spear", "15"},
    {"32", "Diamond Hammer", "20"},
    {"33", "Diamond Armor", "40"},
    {"34", "Health Potion III", "200"}
};

//{"map ressource", "item ressource"}
int CONVERTED_RESSOURCE[TOTAL_CONVERTED][2]= {
    {_wood1, _fir},
    {_wood2, _beech},
    {_wood3, _oak},
    {_rock1, _stone},
    {_rock2, _iron},
    {_rock3, _diamond},
    {_plant1, _herb},
    {_plant2, _lavender},
    {_plant3, _hemp}
};

//{"ressource", "required tool 1", "required tool 2", "required tool 3"}
int REQUIRED_TOOL[TOTAL_REQUIRED][4]= {
    {_fir, _woodAxe, _stoneAxe, _ironAxe},
    {_beech, _nothing, _stoneAxe, _ironAxe},
    {_oak, _nothing, _nothing, _ironAxe},
    {_stone, _woodPickaxe, _stonePickaxe, _ironPickaxe},
    {_iron, _nothing, _stonePickaxe, _ironPickaxe},
    {_diamond, _nothing, _nothing, _ironPickaxe},
    {_herb, _woodBillhook, _stoneBillhook, _ironBillhook},
    {_lavender, _nothing, _stoneBillhook, _ironBillhook},
    {_hemp, _nothing, _nothing, _ironBillhook},
};

//{"entity", "name", "hp", "damage", "xp"}
char MONSTERS[TOTAL_MONSTERS][5][32]={
    {"12", "Living Armor", "20", "1", "300"},
    {"13", "Zombie", "20", "2", "250"},
    {"14", "Wild Bear", "15", "2", "350"},
    {"15", "Bandit", "18", "1", "250"},
    {"16", "Ghoul", "13", "1", "200"},
    {"17", "Manticore", "40", "2", "420"},
    {"18", "Minotaur", "38", "3", "450"},
    {"19", "Ogre", "33", "3", "500"},
    {"20", "Yeti", "35", "4", "480"},
    {"21", "Werewolf", "41", "3", "520"},
    {"22", "Stone Giant", "75", "5", "850"},
    {"23", "Wyvern", "62", "6", "780"},
    {"24", "Chimera", "57", "5", "750"},
    {"25", "Giant Spider", "55", "4", "720"},
    {"26", "Necromancer", "71", "6", "860"},
    {"99", "Malloc Warlord", "82", "8", "1000"}
};

//{"item type name"}
char ITEM_TYPE[4][32]= { "Weapon", "Armor", "Potion", "Item"};

// {"level", "xp required", "hp bonus"}
int LEVELS[TOTAL_LEVELS][3] = {
    {2, 1000, 10},
    {3, 1100, 20},
    {4, 1200, 30},
    {5, 1300, 40},
    {6, 1400, 50},
    {7, 1600, 50},
    {8, 1700, 50},
    {9, 1800, 75},
    {10, 1900, 75}
};

// {"item", "minimum map level", "ressource 1", "quantity ressource 1", "ressource 2", "quantity ressource 2"}
int CRAFT[TOTAL_CRAFTS][6] = {
    {_woodSword, 1, _fir, 3, _nothing, _nothing},
    {_stoneSword, 1, _fir, 2, _stone, 3},
    {_ironSword, 2, _beech, 2, _iron, 4},
    {_diamondSword, 3, _oak, 2, _diamond, 5},
    {_stoneSpear, 1, _fir, 3, _stone, 4},
    {_ironSpear, 2, _beech, 3, _iron, 5},
    {_diamondSpear, 3, _oak, 3, _diamond, 6},
    {_stoneHammer, 1, _fir, 2, _stone, 6},
    {_ironHammer, 2, _beech, 2, _iron, 7},
    {_diamondHammer, 3, _oak, 2, _diamond, 8},
    {_stoneArmor, 1, _stone, 10, _nothing, _nothing},
    {_ironArmor, 2, _iron, 12, _nothing, _nothing},
    {_diamondArmor, 3, _oak, 16, _nothing, _nothing},
    {_woodPickaxe, 1, _fir, 3, _nothing, _nothing},
    {_stonePickaxe, 1, _fir, 2, _stone, 3},
    {_ironPickaxe, 2, _beech, 2, _iron, 4},
    {_woodAxe, 1, _fir, 3, _nothing, _nothing},
    {_stoneAxe, 1, _fir, 2, _stone, 3},
    {_ironAxe, 2, _beech, 2, _iron, 4},
    {_woodBillhook, 1, _fir, 3, _nothing, _nothing},
    {_stoneBillhook, 1, _fir, 2, _stone, 3},
    {_ironBillhook, 2, _beech, 2, _iron, 4},
    {_potion1, 1, _herb, 2, _nothing, _nothing},
    {_potion2, 2, _lavender, 2, _nothing, _nothing},
    {_potion3, 3, _hemp, 2, _nothing, _nothing}
};
