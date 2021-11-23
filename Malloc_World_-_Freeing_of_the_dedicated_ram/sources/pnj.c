#include "../headers/header.h"

//used to repair all the items of the player inventory
void repair(InventoryNode *inventoryHead){

    while(inventoryHead != NULL){
        inventoryHead->durability = getDurability(inventoryHead->value);
        inventoryHead = inventoryHead->next;
    }

    printf("\nAll your items are now repaired.\n");
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

        }else if(choice == '2'){

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
