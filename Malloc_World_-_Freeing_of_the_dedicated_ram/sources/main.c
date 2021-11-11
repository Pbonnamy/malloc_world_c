#include "../headers/header.h"

int main()
{
    srand(time(NULL));

    Levels *levels = malloc(sizeof(Levels));
    Player *player = malloc(sizeof(Player));

    initMap(levels, 8, 8, player);

    handleMovement(levels, player);

    return 0;
}
