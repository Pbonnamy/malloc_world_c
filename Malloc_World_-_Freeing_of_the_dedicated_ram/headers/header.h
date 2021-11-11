#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Monster Monster;
typedef struct MonsterList MonsterList;
typedef struct Levels Levels;
typedef struct Level Level;
typedef struct PlayerPos PlayerPos;
typedef struct Ressource Ressource;
typedef struct RessourceList RessourceList;

#include "combat.h"
#include "ressource.h"
#include "map.h"
#include "player.h"

void initMap (Levels *lv, int rows, int columns, PlayerPos *pc);
void printMap(int **level, int rows, int columns);

void handleMovement(Levels *lv, PlayerPos *pc);

#endif
