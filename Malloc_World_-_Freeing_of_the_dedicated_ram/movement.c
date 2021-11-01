#include "header.h"

int checkCollision(int ** level, int targetRow, int targetColumn, int rows, int columns){
    int allowed = 0;

    if(targetRow >= 0 && targetRow < rows && targetColumn >= 0 && targetColumn < columns){
        allowed = 1;
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

    do{
        printMap(lv->lv1,lv->rows,lv->columns);

        printf("\nWhich direction ? (z : up, s : down, q : left, d : right ): ");
        fflush(stdin);
        scanf("%c", &direction);

        move(lv->lv1, pc, direction, lv->rows, lv->columns);
    }while(direction != 'e');
}
