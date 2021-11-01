#include "header.h"


void move (int ** level, PlayerPos * pc, char direction){

    level[pc->posRow][pc->posColumn] = 0;

    if(direction == 'z'){
        pc->posRow -= 1;
    }else if(direction == 's'){
        pc->posRow += 1;
    }else if(direction == 'q'){
        pc->posColumn -= 1;
    }else if (direction == 'd'){
        pc->posColumn += 1;
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

        move(lv->lv1, pc, direction);
    }while(direction != 'e');
}
