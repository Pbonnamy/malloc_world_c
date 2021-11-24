#include "../headers/header.h"

//test if an item is a weapon
int isWeapon(int entity){
    if(entity == _woodSword || entity == _stoneSword || entity == _ironSword || entity == _diamondSword||
       entity == _stoneSpear || entity == _ironSpear || entity == _diamondSpear||
       entity == _stoneHammer || entity == _ironHammer || entity == _diamondHammer){
        return 1;
    }else{
        return 0;
    }
}

//test if an item is an armor
int isArmor(int entity){
    if(entity == _stoneArmor || entity == _ironArmor || entity == _diamondArmor){
        return 1;
    }else{
        return 0;
    }
}

//test if an item is an tool
int isTool(int entity){
    if(entity == _woodPickaxe || entity == _woodBillhook || entity == _woodAxe ||
       entity == _stonePickaxe || entity == _stoneBillhook || entity == _stoneAxe ||
       entity == _ironPickaxe || entity == _ironBillhook || entity == _ironAxe){
        return 1;
    }else{
        return 0;
    }
}

//test if an item is a potion
int isHeal(int entity){
    if(entity == _potion1 || entity == _potion2 || entity == _potion3){
        return 1;
    }else{
        return 0;
    }
}

//test if an item is a ressource
int isItemRessource(int entity){
    if(entity == _fir || entity == _stone || entity == _herb ||
       entity == _beech || entity == _iron || entity == _lavender ||
       entity == _oak || entity == _diamond || entity == _hemp){
        return 1;
    }else{
        return 0;
    }
}

//find the index of the item in the global ITEM array
int findItemReference(int entity){
    for(int i = 0; i < TOTAL_ITEMS;i++){
        if(atoi(ITEMS[i][_entity]) == entity){
            return i;
        }
    }
    return -1;
}

//find the maximum durability of a given item
int getDurability(int item){
    if(isTool(item)){
        return TOOL_DURABILITY;
    }else if(item == _woodSword || item == _stoneSword || item == _ironSword || item == _diamondSword){
        return SWORD_DURABILITY;
    }else if(item == _stoneSpear || item == _ironSpear || item == _diamondSpear){
        return SPEAR_DURABILITY;
    }else if(item == _stoneHammer || item == _ironHammer || item == _diamondHammer){
        return HAMMER_DURABILITY;
    }

    return -1;
}

//check if has enough durability to harvest a ressource
int checkDurability(int ressource, int durability){
    int allowed = 1;

    if(getRessourceLevel(ressource) == 1){
        if(durability < WEAR_LV1){
            allowed = 0;
        }
    }else if(getRessourceLevel(ressource) == 2){
        if(durability < WEAR_LV2){
            allowed = 0;
        }
    }else if(getRessourceLevel(ressource) == 3){
        if (durability < WEAR_LV3){
            allowed = 0;
        }
    }

    return allowed;
}

//find if the given tool can harvest a specified ressource
int isRequiredTool(int tool, int ressource, int durability){
    int allowed = 0;

    for(int i = 0; i < TOTAL_REQUIRED; i++){
        if(ressource == REQUIRED_TOOL[i][_ressource]){
            for (int j = _firstPossibleTool; j <= _lastPossibleTool; j++){
                if(tool == REQUIRED_TOOL[i][j] && checkDurability(ressource, durability)){
                    allowed = 1;
                }
            }
        }
    }

    return allowed;
}

//decrease durability of tool according to harvested ressource
void handleToolDurability(InventoryNode *inventoryNode, int ressource){
    if(getRessourceLevel(ressource) == 1){
        inventoryNode->durability -= WEAR_LV1;
    }else if(getRessourceLevel(ressource) == 2){
        inventoryNode->durability -= WEAR_LV2;
    }else if(getRessourceLevel(ressource) == 3){
        inventoryNode->durability -= WEAR_LV3;
    }

    if(inventoryNode->durability < 0){
        inventoryNode->durability = 0;
    }
}

//print a single item
void printItem(int item, int reference, int quantity, int durability){
    if(isTool(item)){
        printf("%d/%d %s\n", durability, getDurability(item), ITEMS[reference][_name]);
    }else if(isWeapon(item)){
        printf("%d/%d %s (damage : %s)\n", durability, getDurability(item), ITEMS[reference][_name], ITEMS[reference][_info]);
    }else if(isArmor(item)){
        printf("%s (damage resistance : %s %%)\n", ITEMS[reference][_name], ITEMS[reference][_info]);
    }else if(isItemRessource(item)){
        printf("%d %s\n", quantity, ITEMS[reference][_name]);
    }else if(isHeal(item)){
        printf("%s (heal : %s HP)\n", ITEMS[reference][_name], ITEMS[reference][_info]);
    }
}

//find an iteml in the inventory of the player with its type and a position index
InventoryNode *findItem(InventoryNode *inventoryHead, int itemType, int index){
    int count = 0;

    while(inventoryHead != NULL){
        if((isWeapon(inventoryHead->value) && itemType == _weapon) ||
           (isArmor(inventoryHead->value) && itemType == _armor) ||
           (isHeal(inventoryHead->value) && itemType == _heal) ||
            itemType == _none){

            count ++;
            if(count == index){
                printf("\n%s selected : ", ITEM_TYPE[itemType]);
                printItem(inventoryHead->value, inventoryHead->reference, inventoryHead->quantity, inventoryHead->durability);
                return inventoryHead;
            }
        }
        inventoryHead = inventoryHead->next;
    }

    return NULL;
}

//display all items present in the player inventory corresponding to the given type
int availableItems(InventoryNode *inventoryHead, int itemType){
    int count = 0;

    while(inventoryHead != NULL){
        if((isWeapon(inventoryHead->value) && itemType == _weapon) ||
           (isArmor(inventoryHead->value) && itemType == _armor) ||
           (isHeal(inventoryHead->value) && itemType == _heal) ||
           itemType == _none){

            count ++;
            printf("%d - ", count);
            printItem(inventoryHead->value, inventoryHead->reference, inventoryHead->quantity, inventoryHead->durability);
        }
        inventoryHead = inventoryHead->next;
    }

    return count;
}

//remove an item from the inventory
void removeItem(InventoryNode **inventoryHead, InventoryNode *nodeToRemove){

    if(*inventoryHead == nodeToRemove){
        *inventoryHead = nodeToRemove->next;
    }else{
        InventoryNode *itemNode = *inventoryHead;

        while(itemNode->next != NULL){
            if(itemNode->next == nodeToRemove){
                itemNode->next = nodeToRemove->next;
                return;
            }
            itemNode = itemNode->next;
        }
    }


};

//handling item selection for a given type
InventoryNode *itemSelect(InventoryNode *inventoryHead, int itemType){
    printf("\n%s Availables : \n\n", ITEM_TYPE[itemType]);
    int chosen;

    int index = availableItems(inventoryHead, itemType);

    if(index == 0){
        printf("No %s available !\n", ITEM_TYPE[itemType]);
        return NULL;
    }else if(index == 1){
        return findItem(inventoryHead, itemType, index);
    }else{
        do{
            printf("\nWhich %s : ", ITEM_TYPE[itemType]);

            fflush(stdin);
            scanf("%d", &chosen);
        }while(chosen <= 0 && chosen > index);

        return findItem(inventoryHead, itemType, chosen);
    }
}

