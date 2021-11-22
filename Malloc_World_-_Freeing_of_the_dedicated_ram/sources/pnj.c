#include "../headers/header.h"

void repair(InventoryNode *inventoryHead){

    while(inventoryHead != NULL){
        inventoryHead->durability = getDurability(inventoryHead->value);
        inventoryHead = inventoryHead->next;
    }

    printf("\nAll your items are now repaired.\n");
}

void handleNpc(Player *player){
    char action;

    do{

        printf("\nChoose an action ? (r : repair, c : craft, t : transfer) (e : exit) : ");
        fflush(stdin);
        scanf("%c", &action);

        system("cls"); //clear console

        if(action == 'r'){
            repair(player->inventory);
        }else if(action == 'c'){

        }else if(action == 't'){

        }

    }while(action != 'e');
}
