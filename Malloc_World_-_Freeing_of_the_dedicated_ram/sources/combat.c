#include "../headers/header.h"

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
            printf("Value : %d\n",monsterNode->value);
            monsterNode = monsterNode->next;
        }
    }
}

void addToMonsterList(MonsterNode **monsterHead, int entity, int row, int column){
    MonsterNode *newNode= malloc(sizeof(MonsterNode));
    newNode->column = column;
    newNode->row = row;
    newNode->value = entity;
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
