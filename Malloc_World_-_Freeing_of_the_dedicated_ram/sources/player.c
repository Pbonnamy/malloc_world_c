#include "../headers/header.h"

//display the inventory of the player
void printInventory(InventoryNode *inventoryNode){
    if(inventoryNode == NULL){
        printf("\nInventory : (empty)\n");
    }else{
        printf("\nInventory :\n\n");
        while(inventoryNode != NULL){
            printItem(inventoryNode->value, inventoryNode->reference, inventoryNode->quantity, inventoryNode->durability);
            inventoryNode = inventoryNode->next;
        }
    }

    printf("\n---------------------------\n");
}

//display the character sheet of the player (statistics + inventory)
void displayCharacter(Player *player){
    printf("\n----- Character sheet -----\n\n");
    printf("Hp : %d / %d\n", player->currentHp,player->maxHp);
    printf("Level : %d\n", player->level);
    printf("Xp : %d\n", player->xp);

    printInventory(player->inventory);
}

//try to add a certain quantity to an inventory node if its a ressource (which is stackable)
int addIfStackable(int item, InventoryNode * inventoryNode, int quantity){
    if(isItemRessource(item) && inventoryNode->value == item && inventoryNode->quantity < MAX_RESSOURCE_STACK){
        if((inventoryNode->quantity + quantity) > MAX_RESSOURCE_STACK){
            quantity -= MAX_RESSOURCE_STACK - inventoryNode->quantity;
            inventoryNode->quantity += MAX_RESSOURCE_STACK - inventoryNode->quantity;
        }else{
            inventoryNode->quantity += quantity;
            quantity = 0;
        }
    }

    return quantity;
}

//add a certain amount of an item to the player inventory
void addToInventory(InventoryNode **inventoryHead, int item, int quantity){
    InventoryNode *newNode= malloc(sizeof(InventoryNode));
    newNode->value = item;
    newNode->quantity = quantity;
    newNode->durability = getDurability(item);
    newNode->reference = findItemReference(item);
    newNode->next = NULL;

    if(*inventoryHead == NULL){
        *inventoryHead = newNode;
    }else{
        InventoryNode *lastNode = *inventoryHead;
        int count = 1;

        while(lastNode->next != NULL){
            quantity = addIfStackable(item, lastNode, quantity);
            lastNode = lastNode->next;
            count++;
        }

        if(quantity > 0){ //Handling Last Node
            quantity = addIfStackable(item, lastNode, quantity);
        }

        if(count < MAX_INVENTORY_COUNT && quantity > 0){
            newNode->quantity = quantity;
            lastNode->next = newNode;
        }
    }
}

//used to init the player according to the rules
void initPlayer(Player *player){
    player->level = 1;
    player->xp = 0;
    player->maxHp = 100;
    player->currentHp = 100;
    player->currentMapLvl = 1;
    player->inventory = NULL;

    addToInventory(&player->inventory, _woodSword, 1);
    addToInventory(&player->inventory, _woodPickaxe, 1);
    addToInventory(&player->inventory, _woodBillhook, 1);
    addToInventory(&player->inventory, _potion1, 1);
    addToInventory(&player->inventory, _woodAxe, 1);
    addToInventory(&player->inventory, _potion1, 1);
}
