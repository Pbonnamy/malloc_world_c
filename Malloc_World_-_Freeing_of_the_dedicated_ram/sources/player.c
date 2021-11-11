#include "../headers/header.h"

void printInventory(Inventory *inventory){
    if(inventory == NULL){
        printf("Inventaire vide");
    }else{
        while(inventory != NULL){
            printf("Value : %d | Quantity : %d\n",inventory->value,inventory->quantity);
            inventory = inventory->next;
        }
    }
}

void addToInventory(Inventory **inventory, int item, int quantity){
    Inventory *newNode= malloc(sizeof(Inventory));
    newNode->value = item;
    newNode->quantity = quantity;
    newNode->next = NULL;

    if(*inventory == NULL){
        *inventory = newNode;
    }else{
        Inventory *lastNode = *inventory;

        while(lastNode->next != NULL){
            lastNode = lastNode->next;
        }
        lastNode->next = newNode;
    }
}

void initPlayer(Player *player){
    player->level = 1;
    player->xp = 0;
    player->maxHp = 100;
    player->currentHp = 100;
    player->inventory = NULL;

    addToInventory(&player->inventory, _woodSword, 1);
    addToInventory(&player->inventory, _woodPickaxe, 1);
    addToInventory(&player->inventory, _woodBillhook, 1);
    addToInventory(&player->inventory, _woodAxe, 1);

    printInventory(player->inventory);
}
