#include "../headers/header.h"

//check if the entity is a monster
int isMonster(int entity){
    if(entity >= _monster1 && entity <= _boss){
        return 1;
    }else{
        return 0;
    }
}

//DEBUG
void printMonsterList(MonsterNode *monsterNode){
    if(monsterNode == NULL){
        printf("Vide");
    }else{
        while(monsterNode != NULL){
            printf("Name : %s\n",MONSTERS[monsterNode->reference][_name]);
            monsterNode = monsterNode->next;
        }
    }
}

//will find the index of the entity in the global 'MONSTER' array
int findMonsterReference(int entity){
    for(int i = 0; i < TOTAL_MONSTERS;i++){
        if(atoi(MONSTERS[i][_entity]) == entity){
            return i;
        }
    }
    return -1;
}

//find a monster in the level monster linked list using its position (x, y)
MonsterNode *findMonsterNode(MonsterNode *monsterNode, int row, int column){
    while(monsterNode != NULL){
        if(monsterNode->column == column && monsterNode->row == row){
            return monsterNode;
        }
        monsterNode = monsterNode->next;
    }

    return NULL;
}

//add a monster to the level monster linked list
void addToMonsterList(MonsterNode **monsterHead, int entity, int row, int column){
    int reference = findMonsterReference(entity);

    MonsterNode *newNode= malloc(sizeof(MonsterNode));
    newNode->column = column;
    newNode->row = row;
    newNode->value = entity;
    newNode->reference = reference;
    newNode->hp = atoi(MONSTERS[reference][_monsterHp]);
    newNode->respawn = 0;
    newNode->next = NULL;

    if(*monsterHead == NULL){
        *monsterHead = newNode;
    }else{
        MonsterNode *lastNode = *monsterHead;

        while(lastNode->next != NULL){
            lastNode = lastNode->next;
        }
        lastNode->next = newNode;
    }
}
