#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum mapEntity{
    playerVal = 1,
    portal2Val = -3,
    portal1Val = -2,
    wallVal = -1,
    npcVal = 2,
    plant1Val = 3,
    rock1Val = 4,
    wood1Val = 5,
    plant2Val = 6,
    rock2Val = 7,
    wood2Val = 8,
    plant3Val = 9,
    rock3Val = 10,
    wood3Val = 11,
};

void initMap ();
