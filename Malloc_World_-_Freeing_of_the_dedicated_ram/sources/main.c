#include "../headers/header.h"

int main()
{
    srand(time(NULL));

    Levels *levels = malloc(sizeof(Levels));
    Player *player = malloc(sizeof(Player));

    initMap(levels, 10, 10, player);
    initPlayer(player);

    //printRessourceList(levels->lv1->ressourceList);
    //printMonsterList(levels->lv1->monsterList);

    gameLoop(levels, player);

    return 0;
}
