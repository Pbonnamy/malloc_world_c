#include "../headers/header.h"

void printInventory(InventoryNode *inventoryNode){
    if(inventoryNode == NULL){
        printf("Empty inventory");
    }else{
        while(inventoryNode != NULL){
            printf("Entity : %d | Quantity : %d\n",inventoryNode->value,inventoryNode->quantity);
            inventoryNode = inventoryNode->next;
        }
    }

    printf("\n---------------------------\n\n");
}

void displayCharacter(Player *player){
    printf("----- Character sheet -----\n\n");
    printf("Hp : %d / %d\n", player->currentHp,player->maxHp);
    printf("level : %d\n", player->level);
    printf("Xp : %d\n", player->xp);

    printf("\nInventory :\n\n");
    printInventory(player->inventory);
}

void addToInventory(InventoryNode **inventoryHead, int item, int quantity){
    InventoryNode *newNode= malloc(sizeof(InventoryNode));
    newNode->value = item;
    newNode->quantity = quantity;
    newNode->next = NULL;

    if(*inventoryHead == NULL){
        *inventoryHead = newNode;
    }else{
        InventoryNode *lastNode = *inventoryHead;

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

}
