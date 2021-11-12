#ifndef RESSOURCE_H
#define RESSOURCE_H

#include "header.h"

struct RessourceNode{
    int harvested;
    int value;
    int row;
    int column;
    RessourceNode *next;
};

#endif
