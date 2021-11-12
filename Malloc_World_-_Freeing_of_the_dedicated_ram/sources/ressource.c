#include "../headers/header.h"

int isMapRessource(int entity){
    if(entity== _plant1 || entity == _plant2 || entity == _plant3 ||
        entity == _wood1 || entity == _wood2 || entity == _wood3 ||
        entity == _rock1 || entity == _rock2 || entity == _rock3){
        return 1;
    }else{
        return 0;
    }
}

int mapToItemRessource(int ressource){
    for(int i = 0; i < TOTAL_CONVERTED; i++){
        if(CONVERTED_RESSOURCE[i][_mapRessource] == ressource){
            return CONVERTED_RESSOURCE[i][_itemRessource];
        }
    }

    return -1;
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

void harvestRessource(int ressource){
    int converted = mapToItemRessource(ressource);
    int quantity = rand2(1,4);
    printf("\nYou just harvested %d %s\n\n", quantity, DATAS[findItemReference(converted)][_name]);
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
