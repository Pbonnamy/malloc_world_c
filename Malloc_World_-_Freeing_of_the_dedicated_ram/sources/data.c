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
    {_beech, -1, _stoneAxe, _ironAxe},
    {_oak, -1, -1, _ironAxe},
    {_stone, _woodPickaxe, _stonePickaxe, _ironPickaxe},
    {_iron, -1, _stonePickaxe, _ironPickaxe},
    {_diamond, -1, -1, _ironPickaxe},
    {_herb, _woodBillhook, _stoneBillhook, _ironBillhook},
    {_lavender, -1, _stoneBillhook, _ironBillhook},
    {_hemp, -1, -1, _ironBillhook},
};

//{"entity", "name", "hp", "damage", "xp"}
char MONSTERS[TOTAL_MONSTERS][5][32]={
    {"12", "Living Armor", "50", "1", "300"},
    {"13", "Zombie", "20", "2", "150"},
    {"14", "Wild Bear", "40", "2", "350"},
    {"15", "Bandit", "30", "1", "150"},
    {"16", "Ghoul", "20", "1", "100"},
    {"17", "Manticore", "", "", ""},
    {"18", "Minotaur", "", "", ""},
    {"19", "Ogre", "", "", ""},
    {"20", "Yeti", "", "", ""},
    {"21", "Werewolf", "", "", ""},
    {"22", "Stone Giant", "", "", ""},
    {"23", "Wyvern", "", "", ""},
    {"24", "Chimera", "", "", ""},
    {"25", "Giant Spider", "", "", ""},
    {"26", "Necromancer", "", "", ""},
    {"99", "Malloc Warlord", "", "", ""}
};


