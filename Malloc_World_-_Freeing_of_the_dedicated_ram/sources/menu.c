#include "../headers/header.h"

void handleAction(Levels *levels, Player *player, char action){

    if(action == '1'){
        printf("\nTODO : Display Character sheet\n\n");
    }else if(action == '2'){
        handleMovement(levels, player);
    }else if(action == '3'){
        printf("\nTODO : Save\n\n");
    }

}

void gameLoop(Levels *levels, Player *player){
    char action;

    printf("\nWelcome to Malloc World !\n\n");

    do{
        printMap(levels->lv1->map, levels->rows, levels->columns);

        printf("\n1 - Character sheet \n"
               "2 - Move \n"
               "3 - Save \n"
               "4 - Exit \n"
               "\nWhat do you want to do : ");


        fflush(stdin);
        scanf("%c", &action);

        system("cls"); //clear console

        handleAction(levels, player, action);

    }while(action != '4');
}
