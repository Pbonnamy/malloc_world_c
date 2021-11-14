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
            printf("Name : %s\n",ITEMS[ressourceNode->reference][_name]);
            ressourceNode = ressourceNode->next;
        }
    }
}

int canHarvest(int ressource, InventoryNode *inventoryNode){
    int allowed = 0;

    while(inventoryNode != NULL){
        if(isRequiredTool(inventoryNode->value, ressource, inventoryNode->durability)){
            handleToolDurability(inventoryNode, ressource);
            allowed = 1;
            break;
        }
        inventoryNode = inventoryNode->next;
    }

    return allowed;
}

int getRessourceLevel(int ressource){
    if(ressource == _fir || ressource == _stone || ressource == _herb){
        return 1;
    }else if(ressource == _beech || ressource == _iron || ressource == _lavender){
        return 2;
    }else if(ressource == _oak || ressource == _diamond || ressource == _hemp){
        return 3;
    }

    return -1;
}

RessourceNode *findRessourceNode(RessourceNode *ressourceNode, int row, int column){

    while(ressourceNode != NULL){
        if(ressourceNode->column == column && ressourceNode->row == row){
            return ressourceNode;
        }
        ressourceNode = ressourceNode->next;
    }

    return NULL;
}


int harvestRessource(RessourceNode *ressourceNode, Player *player){
    int converted = mapToItemRessource(ressourceNode->value);
    int allowed = 0;

    if(canHarvest(converted, player->inventory)){
        int quantity = rand2(1,4);

        ressourceNode->harvested = RESPAWN_RESSOURCE;
        addToInventory(&player->inventory, converted, quantity);

        printf("\nYou just harvested %d %s\n\n", quantity, ITEMS[ressourceNode->reference][_name]);

        allowed = 1;
    }else{
        printf("\nYou don't have the required tool or its durability is too low\n\n");
    }

    return allowed;
}

void addToRessourceList(RessourceNode **ressourceHead, int entity, int row, int column){
    RessourceNode *newNode= malloc(sizeof(RessourceNode));
    newNode->row = row;
    newNode->column = column;
    newNode->value = entity;
    newNode->reference = findItemReference(mapToItemRessource(entity));
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
