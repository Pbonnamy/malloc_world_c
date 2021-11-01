#include "header.h"

int main()
{
    srand(time(NULL));

    Levels *lv = malloc(sizeof(Levels)*1);
    PlayerPos *pc = malloc(sizeof(PlayerPos)*1);

    initMap(lv, 8, 8, pc);

    handleMovement(lv, pc);

    return 0;
}
