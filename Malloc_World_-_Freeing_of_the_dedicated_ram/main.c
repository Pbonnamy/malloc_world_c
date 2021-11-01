#include "header.h"

int main()
{
    srand(time(NULL));

    Levels *lv = malloc(sizeof(Levels));
    PlayerPos *pc = malloc(sizeof(PlayerPos));

    initMap(lv, 8, 8, pc);

    handleMovement(lv, pc);

    return 0;
}
