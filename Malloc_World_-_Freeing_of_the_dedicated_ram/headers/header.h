#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct MonsterNode MonsterNode;
typedef struct Levels Levels;
typedef struct Level Level;
typedef struct InventoryNode InventoryNode;
typedef struct Player Player;
typedef struct RessourceNode RessourceNode;

#include "combat.h"
#include "ressource.h"
#include "map.h"
#include "player.h"
#include "data.h"
#include "item.h"

#define TOOL_DURABILITY 10
#define SWORD_DURABILITY 10
#define SPEAR_DURABILITY 8
#define HAMMER_DURABILITY 5

#define MAX_RESSOURCE_STACK 20
#define MAX_INVENTORY_COUNT 10

#define WEAR_LV1 1
#define WEAR_LV2 2
#define WEAR_LV3 4

#define TOTAL_DATAS 34
extern char DATAS[TOTAL_DATAS][3][32];

#define TOTAL_CONVERTED 9
extern int CONVERTED_RESSOURCE[TOTAL_CONVERTED][2];

#define TOTAL_REQUIRED 9
int REQUIRED_TOOL[TOTAL_REQUIRED][4];

//PLAYER
void initPlayer(Player *player);
void displayCharacter(Player *player);
void printInventory(InventoryNode *inventoryNode);
void addToInventory(InventoryNode **inventoryHead, int item, int quantity);
int addIfStackable(int item, InventoryNode * inventoryNode, int quantity);

//MOVEMENT
void handleMovement(Levels *levels, Player *player);
int checkCollision(Level *level, int targetRow, int targetColumn, int rows, int columns, Player *player);
void move(Level *level, Player *player, char direction, int rows, int columns);

// MAP
int rand2 (int min, int max);
void printMap(int **map, int rows, int columns);
void createLevel(Level *level, int rows, int columns, int nbLevel);
void addPlayer(Level *level, int rows, int columns, Player *player);
void populate(Level *level, int rows, int columns, int entity, int quantity);
void populateLevel(Level *level, int rows, int columns);
void initMap(Levels *levels, int rows, int columns, Player *player);

//RESSOURCE
int isMapRessource(int entity);
void addToRessourceList(RessourceNode **ressourceHead, int entity, int row, int column);
void printRessourceList(RessourceNode *ressourceNode);
int mapToItemRessource(int ressource);
int harvestRessource(RessourceNode *ressource, int row, int column, Player *player, Level *level);
int canHarvest(int ressource, InventoryNode *inventoryNode);
int getRessourceLevel(int ressource);
RessourceNode *findRessourceNode(RessourceNode *ressourceNode, int row, int column);

//COMBAT
int isMonster(int entity);
void addToMonsterList(MonsterNode **monsterHead, int entity, int row, int column);
void printMonsterList(MonsterNode *monsterNode);

//MENU
void gameLoop(Levels *levels, Player *player);
void handleAction(Levels *levels, Player *player, char action);

//ITEM
int isWeapon(int entity);
int isArmor(int entity);
int isTool(int entity);
int isHeal(int entity);
int isItemRessource(int entity);
int getDurability(int item);
void printItem(int item, int reference, int quantity, int durability);
int findItemReference(int entity);
int checkDurability(int ressource, int durability);
int isRequiredTool(int tool, int ressource, int durability);
void handleToolDurability(InventoryNode *inventoryNode, int ressource);

#endif
