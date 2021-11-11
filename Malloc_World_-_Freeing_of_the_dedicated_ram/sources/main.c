#include "../headers/header.h"

int main()
{
    srand(time(NULL));

    Levels *levels = malloc(sizeof(Levels));
    Player *player = malloc(sizeof(Player));

    initMap(levels, 10, 10, player);
    initPlayer(player);

    //handleMovement(levels, player);

    return 0;
}
