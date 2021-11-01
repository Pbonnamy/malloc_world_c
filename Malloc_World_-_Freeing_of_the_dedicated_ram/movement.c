#include "header.h"


void move (int ** level, PlayerPos * pc, char direction){

    level[pc->posRow][pc->posColumn] = 0;

    if(direction == 'z'){
        level[(pc->posRow)-1][pc->posColumn] = 1;
        pc->posRow -= 1;
    }else if(direction == 's'){
        level[pc->posRow+1][pc->posColumn] = 1;
        pc->posRow += 1;
    }else if(direction == 'q'){
        level[pc->posRow][pc->posColumn-1] = 1;
        pc->posColumn -= 1;
    }else if (direction == 'd'){
        level[pc->posRow][pc->posColumn+1] = 1;
        pc->posColumn += 1;
    }

}

void handleMovement(Levels *lv, PlayerPos *pc){

    //printMap(lv->lv1,lv->rows,lv->columns);

    char direction;

    do{
        printMap(lv->lv1,lv->rows,lv->columns);

        printf("\nWhich direction ? (z : up, s : down, q : left, d : right ): ");
        fflush(stdin);
        scanf("%c", &direction);

        move(lv->lv1, pc, direction);
    }while(direction != 'e');
}
