#ifndef RESSOURCE_H
#define RESSOURCE_H

#include "header.h"

struct Ressource{
    int harvested;
    int value;
    int row;
    int column;
};

struct RessourceList{
    Ressource ressource;
    RessourceList * next;
};

#endif
