#include "../headers/header.h"

int flee(){
    int rate = rand2(1,100);
    int loop = 0;

    if(rate <= FLEE_RATE){
        loop = 1;
    }

    if(loop == 1){
        printf("\nYou failed to flee\n");
    }else if(loop == 0){
        printf("\nYou fled\n\n");
    }

    return loop;
}

InventoryNode *findItem(InventoryNode *inventoryHead, int itemType, int index){
    int count = 0;

    while(inventoryHead != NULL){
        if(isWeapon(inventoryHead->value) && itemType == _weapon){
            count ++;
            if(count == index){
                printf("\n%s selected : ", ITEM_TYPE[itemType]);
                printItem(inventoryHead->value, inventoryHead->reference, inventoryHead->quantity, inventoryHead->durability);
                return inventoryHead;
            }
        }else if(isArmor(inventoryHead->value) && itemType == _armor){
            count ++;
            if(count == index){
                printf("\n%s selected : ", ITEM_TYPE[itemType]);
                printItem(inventoryHead->value, inventoryHead->reference, inventoryHead->quantity, inventoryHead->durability);
                return inventoryHead;
            }
        }else if (isHeal(inventoryHead->value) && itemType == _heal){
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

int availableItems(InventoryNode *inventoryHead, int itemType){
    int count = 0;

    while(inventoryHead != NULL){
        if(isWeapon(inventoryHead->value) && itemType == _weapon){
            count ++;
            printf("%d - ", count);
            printItem(inventoryHead->value, inventoryHead->reference, inventoryHead->quantity, inventoryHead->durability);
        }else if(isArmor(inventoryHead->value) && itemType == _armor){
            count ++;
            printf("%d - ", count);
            printItem(inventoryHead->value, inventoryHead->reference, inventoryHead->quantity, inventoryHead->durability);
        }else if (isHeal(inventoryHead->value) && itemType == _heal){
            count ++;
            printf("%d - ", count);
            printItem(inventoryHead->value, inventoryHead->reference, inventoryHead->quantity, inventoryHead->durability);
        }
        inventoryHead = inventoryHead->next;
    }

    return count;
}

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
            printf("\nChoose a %s : ", ITEM_TYPE[itemType]);

            fflush(stdin);
            scanf("%d", &chosen);
        }while(chosen <= 0 && chosen > index);

        return findItem(inventoryHead, itemType, index);
    }
}

int handleCombat(MonsterNode *monsterNode, Player *player){
    char action;
    int loop = 1;
    int defeated = 0;

    InventoryNode *weapon = itemSelect(player->inventory, _weapon);

    do{
        printf("\nYour are fighting a %s - Hp : %d | Dmg : %s\n\n", MONSTERS[monsterNode->reference][_name], monsterNode->hp, MONSTERS[monsterNode->reference][_monsterDamage]);

        printf("Choose an action ? (a : attack, p : use a potion, f : try to flee)  : ");
        fflush(stdin);
        scanf("%c", &action);

        system("cls"); //clear console

        if(action == 'a'){

        }else if(action == 'p'){
            InventoryNode *potion = itemSelect(player->inventory, _heal);
        }else if(action == 'f'){
            loop = flee();
        }

    }while(loop);

    return defeated;
}
