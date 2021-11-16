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

InventoryNode *weaponSelect(InventoryNode *inventoryHead){
    printf("\nWeapon selection : \n\n");

    int count = 1 ;

    while(inventoryHead != NULL){
        if(isWeapon(inventoryHead->value)){
            printf("%d - ", count);
            printItem(inventoryHead->value, inventoryHead->reference, inventoryHead->quantity, inventoryHead->durability);
            count ++;
        }
        inventoryHead = inventoryHead->next;
    }

    return NULL;
}

int handleCombat(MonsterNode *monsterNode, Player *player){
    char action;
    int loop = 1;
    int defeated = 0;

    InventoryNode *weapon = weaponSelect(player->inventory);

    return defeated;

    do{
        printf("\nYour are fighting a %s - Hp : %d | Dmg : %s\n\n", MONSTERS[monsterNode->reference][_name], monsterNode->hp, MONSTERS[monsterNode->reference][_monsterDamage]);

        printf("Choose an action ? (a : attack, p : use a potion, f : try to flee)  : ");
        fflush(stdin);
        scanf("%c", &action);

        system("cls"); //clear console

        if(action == 'a'){

        }else if(action == 'p'){

        }else if(action == 'f'){
            loop = flee();
        }

    }while(loop);

    return defeated;
}
