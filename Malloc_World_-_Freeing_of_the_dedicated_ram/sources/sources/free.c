#include "../headers/header.h"

void freeMonsterList(MonsterNode *head){

    MonsterNode *tmp;

    while (head != NULL){
       tmp = head;
       head = head->next;
       free(tmp);
    }
}

void freeRessourceList(RessourceNode *head){
    RessourceNode *tmp;

    while (head != NULL){
       tmp = head;
       head = head->next;
       free(tmp);
    }
}

void freeMap(int **map, int rows){

    for(int i = 0; i < rows; i ++){
        free(map[i]);
    }

    free(map);
}

void freeStorage(InventoryNode *head){
    InventoryNode *tmp;

    while (head != NULL){
       tmp = head;
       head = head->next;
       free(tmp);
    }
}

void freeLevel(Level *level){
    freeMonsterList(level->monsterList);
    freeRessourceList(level->ressourceList);
    freeMap(level->map, level->rows);
    free(level);
}

void freeEverything(Levels *levels, Player *player){
    freeLevel(levels->lv1);
    freeLevel(levels->lv2);
    freeLevel(levels->lv3);
    freeStorage(levels->chest);
    free(levels);

    freeStorage(player->inventory);
    free(player);
}
