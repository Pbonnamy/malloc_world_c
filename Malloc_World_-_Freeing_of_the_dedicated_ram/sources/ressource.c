#include "../headers/header.h"

int isRessource(int entity){
    if(entity== _plant1 || entity == _plant2 || entity == _plant3 ||
        entity == _wood1 || entity == _wood2 || entity == _wood3 ||
        entity == _rock1 || entity == _rock2 || entity == _rock3){

        return 1;
    }else{
        return 0;
    }
}

//DEBUG
void printRessourceList(RessourceNode *ressourceNode){
    if(ressourceNode == NULL){
        printf("Vide");
    }else{
        while(ressourceNode != NULL){
            printf("Value : %d\n",ressourceNode->value);
            ressourceNode = ressourceNode->next;
        }
    }
}

void addToRessourceList(RessourceNode **ressourceHead, int entity, int row, int column){
    RessourceNode *newNode= malloc(sizeof(RessourceNode));
    newNode->row = row;
    newNode->column = column;
    newNode->value = entity;
    newNode->harvested = 0;
    newNode->next = NULL;

    if(*ressourceHead == NULL){
        *ressourceHead = newNode;
    }else{
        RessourceNode *lastNode = *ressourceHead;

        while(lastNode->next != NULL){
            lastNode = lastNode->next;
        }
        lastNode->next = newNode;
    }
}
