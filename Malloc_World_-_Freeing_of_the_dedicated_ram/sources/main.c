#include "../headers/header.h"

int main(){
    srand(time(NULL));

    char action;

    do{

        printf("\n----------- MAIN MENU ----------\n\n");

        printf("1 - PLAY \n"
               "2 - LOAD SAVE \n"
               "3 - EXIT \n"
               "\nChoose en option : ");

        fflush(stdin);
        scanf("%c", &action);

        system("cls"); //clear console

        handleMainMenu(action);

    }while(action != '3');

    return 0;
}
