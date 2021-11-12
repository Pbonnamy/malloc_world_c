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

//PLAYER
void initPlayer(Player *player);
void printInventory(InventoryNode *inventoryNode);
void addToInventory(InventoryNode **inventoryHead, int item, int quantity);

//MOVEMENT
void handleMovement(Levels *levels, Player *player);
int checkCollision(Level *level, int targetRow, int targetColumn, int rows, int columns);
void move(Level *level, Player *player, char direction, int rows, int columns);

// MAP
int rand2 (int min, int max);
void printMap(int **map, int rows, int columns);
void createLevel(Level *level, int rows, int columns, int nbLevel);
void addPlayer(Level *level, int rows, int columns, Player *player);
void populate(int **map, int rows, int columns, int entity, int quantity);
void populateLevel(Level *level, int rows, int columns);
void initMap(Levels *levels, int rows, int columns, Player *player);

#endif
