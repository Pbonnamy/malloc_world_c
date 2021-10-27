#include "header.h"

void handleMovement(){
    char direction;

    do{
        printf("\nWhich direction ? : ");
        scanf("%c", &direction);
        fflush(stdin);
        printf("Direction : %c\n", direction);

    }while(direction != 'p');
}
