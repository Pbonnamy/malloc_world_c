#include "header.h"

int checkCollision(int ** level, int targetRow, int targetColumn, int rows, int columns){
    int allowed = 0;

    if(targetRow >= 0 && targetRow < rows && targetColumn >= 0 && targetColumn < columns){
        int target = level[targetRow][targetColumn];

        if(target == plant1 || target == plant2 || target == plant3 ||
           target == wood1 || target == wood2 || target == wood3 ||
           target == rock1 || target == rock2 || target == rock3){

            printf("\nTODO : harvest ressource\n\n");

        }else if (target >= monster1 && target <= boss){

            printf("\nTODO : combat\n\n");

        }else if (target == portal1 || target == portal2){

            printf("\nTODO : switch level\n\n");

        }else if (target == npc){

            printf("\nTODO : handle npc\n\n");

        }else if( target ==  wall){

            printf("\nImpossible : this is a wall\n\n");

        }else{
            printf("\n\n\n");
            allowed = 1;
        }
    }else{
        printf("\nError : movement not allowed\n\n");
    }

    return allowed;
}

void move (int ** level, PlayerPos * pc, char direction, int rows, int columns){

    level[pc->posRow][pc->posColumn] = 0;

    if(direction == 'z'){
        if(checkCollision(level, pc->posRow-1, pc->posColumn, rows, columns)){
            pc->posRow -= 1;
        }
    }else if(direction == 's'){
        if(checkCollision(level, pc->posRow+1, pc->posColumn, rows, columns)){
            pc->posRow += 1;
        }
    }else if(direction == 'q'){
        if(checkCollision(level, pc->posRow, pc->posColumn-1, rows, columns)){
            pc->posColumn -= 1;
        }
    }else if (direction == 'd'){
        if(checkCollision(level, pc->posRow, pc->posColumn+1, rows, columns)){
            pc->posColumn += 1;
        }
    }

    level[pc->posRow][pc->posColumn] = 1;

}

void handleMovement(Levels *lv, PlayerPos *pc){

    char direction;

    printf("\nWelcome to Malloc World !\n\n");

    do{

        printMap(lv->lv1,lv->rows,lv->columns);

        printf("\nWhich direction ? (z : up, s : down, q : left, d : right ) (e : exit) : ");
        fflush(stdin);
        scanf("%c", &direction);

        system("cls"); //clear console

        move(lv->lv1, pc, direction, lv->rows, lv->columns);

    }while(direction != 'e');
}
