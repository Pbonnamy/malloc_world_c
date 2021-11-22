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

    int** map = malloc(sizeof(int*)*4);
    for (size_t i =0; i <4; i+=1) {
        map[i] = malloc(sizeof(int)*4);
    }
    for (size_t i = 0; i<4; i+=1) {
        for (size_t j = 0; j<4; j+=1) {
            map[i][j] = 0;
        }
    }
    writeInFile(map);
    readFile();
    freeMap(map);

    return 0;
}
