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
typedef struct InventoryNode InventoryNode;
typedef struct Player Player;
typedef struct Ressource Ressource;
typedef struct RessourceList RessourceList;

#include "combat.h"
#include "ressource.h"
#include "map.h"
#include "player.h"

void initMap(Levels *levels, int rows, int columns, Player *player);
void initPlayer(Player *player);
void printMap(int **map, int rows, int columns);
void handleMovement(Levels *levels, Player *player);

#endif
