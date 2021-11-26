#include "../headers/header.h"

//used to repair all the items of the player inventory
void repair(InventoryNode *inventoryHead){

    while(inventoryHead != NULL){
        inventoryHead->durability = getDurability(inventoryHead->value);
        inventoryHead = inventoryHead->next;
    }

    printf("\nAll your items are now repaired.\n");
}

int hasRessource(InventoryNode *inventory, InventoryNode *chest, int ressource, int quantity){

    while(inventory != NULL){
        if(inventory->value == ressource){
            quantity -= inventory->quantity;
        }
        inventory = inventory->next;
    }

    while(chest != NULL){
        if(chest->value == ressource){
            quantity -= chest->quantity;
        }
        chest = chest->next;
    }

    if(quantity <= 0){
        return 1;
    }else{
        return 0;
    }
}

int craftIndex(int item){
    for(int i = 0; i < TOTAL_CRAFTS; i++){
        if(CRAFT[i][_item] == item){
            return i;
        }
    }

    return -1;
}

int canCraft(InventoryNode *inventory, InventoryNode *chest, int item){
    int index = craftIndex(item);

    int ressource1 = CRAFT[index][_craftRessource1];
    int quantity1 = CRAFT[index][_craftQuantity1];
    int ressource2 = CRAFT[index][_craftRessource2];
    int quantity2 = CRAFT[index][_craftQuantity2];

    if(!hasRessource(inventory, chest, ressource1, quantity1)){
        return 0;
    }

    if(ressource2 != _nothing && !hasRessource(inventory, chest, ressource2, quantity2)){
        return 0;
    }

    return 1;
}

void craftableItemList(InventoryNode *inventory, InventoryNode *chest){
    int item;
    int ressourceRef;
    int count = 0;

    printf("\nCraftable items : \n\n");

    for(int i = 0; i < TOTAL_CRAFTS; i++){
        item = CRAFT[i][_item];

        if(canCraft(inventory, chest, item)){
            count ++;
            printf("%d - ", count);

            ressourceRef = findItemReference(CRAFT[i][_craftRessource1]);

            printf("%d %s ", CRAFT[i][_craftQuantity1], ITEMS[ressourceRef][_name]);

            if(CRAFT[i][_craftRessource2] != _nothing){
                ressourceRef = findItemReference(CRAFT[i][_craftRessource2]);
                printf("+ %d %s ", CRAFT[i][_craftQuantity2], ITEMS[ressourceRef][_name]);
            }

            printf(": ");

            printItem(item, findItemReference(item), 1, getDurability(item));
        }
    }

    if(count == 0){
        printf("No craftable Items\n");
    }
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
            craftableItemList(player->inventory, chest);
        }else if(action == 't'){
            transferItem(player, chest);
        }

    }while(action != 'e');

    printf("\n\n\n");
}
