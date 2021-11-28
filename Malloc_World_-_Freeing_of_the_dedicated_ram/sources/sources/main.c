#include "../headers/header.h"

int main(){
    srand(time(NULL));

    char action;

    do{
        printf("\n----------- MAIN MENU ----------\n\n");

        printf("1 - New Game \n"
               "2 - Load Save \n"
               "3 - Exit \n"
               "\nChoose en option : ");

        fflush(stdin);
        scanf("%c", &action);

        system("cls"); //clear console

        handleMainMenu(action);

    }while(action != '3');

    return 0;
}
