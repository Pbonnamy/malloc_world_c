#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "map.h"
#include "player.h"
#include "combat.h"
#include "ressource.h"

typedef struct Player Player;

typedef struct {
    int posRow;
    int posColumn;
}PlayerPos; // Will be merged later with struct player

void initMap (Levels *lv, int rows, int columns, PlayerPos *pc);
void printMap(int **level, int rows, int columns);

void handleMovement(Levels *lv, PlayerPos *pc);

