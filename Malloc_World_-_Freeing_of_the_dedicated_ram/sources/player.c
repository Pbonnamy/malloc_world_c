#include "../headers/header.h"

struct item{
    int id;
    char* name;
    enum type{
        Arme,
        Outil,
        Ressource,
        Armure,
        Soin,
    };
    char* description;
};
typedef struct item item;

typedef struct Player{
    char* username;
    int experience;
    int level;
    int life_point;
    int max_hit_point;
    item item[];
}Player;

