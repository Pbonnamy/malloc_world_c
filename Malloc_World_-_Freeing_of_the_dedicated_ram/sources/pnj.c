#include "../headers/header.h"

//used to repair all the items of the player inventory
void repair(InventoryNode *inventoryHead){

    while(inventoryHead != NULL){
        inventoryHead->durability = getDurability(inventoryHead->value);
        inventoryHead = inventoryHead->next;
    }

    printf("\nAll your items are now repaired.\n");
}

int transfer(InventoryNode **inventoryHead, InventoryNode *item, int storageLimit){

    InventoryNode *newNode = malloc(sizeof(InventoryNode));

    memcpy(newNode, item, sizeof (InventoryNode));
    newNode->next = NULL;

    int transfered = 0;

    if(*inventoryHead == NULL){
        *inventoryHead = newNode;
        transfered = 1;
    }else{
        InventoryNode *lastNode = *inventoryHead;
        int count = 1;

        while(lastNode->next != NULL){
            item->quantity = addIfStackable(item->value, lastNode, item->quantity);
            lastNode = lastNode->next;
            count++;
        }

        if(item->quantity > 0){ //Handling Last Node
            item->quantity = addIfStackable(item->value, lastNode, item->quantity);
        }

        if(storageLimit){
            if(count < storageLimit && item->quantity > 0){
                newNode->quantity = item->quantity;
                lastNode->next = newNode;
                transfered = 1;
            }
        }else{
            if(item->quantity > 0){
                newNode->quantity = item->quantity;
                newNode->durability = getDurability(newNode->value); //repa
                lastNode->next = newNode;
                transfered = 1;
            }
        }
    }

    if(item->quantity == 0){
        transfered = 1;
    }

    if(!transfered){
        printf("\nImpossible to transfer Item\n\n");
    }

    return transfered;
}

void transferItem(Player *player, InventoryNode *chest){
    char choice;

    do{
        printf("\n1 - Transfer item from inventory to chest \n"
               "2 - Transfer item from chest to inventory \n"
               "3 - Exit \n"
               "\nChoose en option : ");

        fflush(stdin);
        scanf("%c", &choice);

        system("cls");


        if(choice == '1'){
            InventoryNode *item = itemSelect(player->inventory, _none);
            if(item != NULL){
                if(transfer(&chest, item, _noStorageLimit)){
                    removeItem(&player->inventory, item);
                }
            }

        }else if(choice == '2'){
            InventoryNode *item = itemSelect(chest, _none);
            if(item != NULL){
                if(transfer(&player->inventory, item, MAX_INVENTORY_COUNT)){
                    removeItem(&chest, item);
                }
            }
        }

    }while(choice != '3');
}

//main npc loop (repair, craft, item transfer between chest and player inventory)
void handleNpc(Player *player, InventoryNode *chest){
    char action;

    do{

        printf("\nChoose an action ? (r : repair, c : craft, t : transfer item) (e : exit) : ");
        fflush(stdin);
        scanf("%c", &action);

        system("cls"); //clear console

        if(action == 'r'){
            repair(player->inventory);
        }else if(action == 'c'){

        }else if(action == 't'){
            transferItem(player, chest);
        }

    }while(action != 'e');
}
