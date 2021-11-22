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

    int** map = malloc(sizeof(int*)*4);
    for (size_t i =0; i <4; i+=1) {
        map[i] = malloc(sizeof(int)*4);
    }
    for (size_t i = 0; i<4; i+=1) {
        for (size_t j = 0; j<4; j+=1) {
            map[i][j] = 0;
        }
    }
    writeInFile(map);
    readFile();
    freeMap(map);

    return 0;
}
