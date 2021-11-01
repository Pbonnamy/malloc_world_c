#include "header.h"


int rand2 (int min, int max){
    return (rand()%(max-min+1)) + min;
}

void printMap(int **level, int rows, int columns){

    for (int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            printf(" %2d ", level[i][j]);
        }
        printf("\n");
    }
}

int ** createLevel(int rows, int columns){
    int **map = malloc(sizeof(int*)*rows);

    for(int i = 0; i < columns; i ++){
        map[i] = malloc(sizeof(int)*columns);
    }

    for(int j = 0; j < rows; j++){
        for(int k = 0; k < columns; k++){
            map[j][k] = 0;
        }
    }

    return map;
}

void addPlayer(int **map, int rows, int columns, PlayerPos *pc){
    int row = rand2(0,rows-1);
    int column = rand2(0,columns-1);

    while(map[row][column] != 0){
        row = rand2(0,rows-1);
        column = rand2(0,rows-1);
    }

    pc->posRow = row;
    pc->posColumn = column;

    map[row][column] = player;
}

void populate(int **map, int rows, int columns, int entity, int quantity){
    int row = rand2(0,rows-1);
    int column = rand2(0,columns-1);

    for(int i = 0 ; i< quantity; i++){
        while(map[row][column] != 0){
            row = rand2(0,rows-1);
            column = rand2(0,rows-1);
        }
        if(entity == monster1){
            map[row][column] = rand2(monster1,monster2-1);
        }else if(entity == monster2){
            map[row][column] = rand2(monster2,monster3-1);
        }else if(entity == monster3){
            map[row][column] = rand2(monster3,lastMonster-1);
        }else{
            map[row][column] = entity;
        }
    }
}

void populateLevel(int **map, int rows, int columns, int level){
    populate(map, rows, columns, npc, 1);
    populate(map, rows, columns, wall, 7);

    if(level == 1){
        populate(map, rows, columns, plant1, 3);
        populate(map, rows, columns, rock1, 3);
        populate(map, rows, columns, wood1, 3);
        populate(map, rows, columns, portal1, 1);
        populate(map, rows, columns, monster1, 10);
    }else if(level == 2){
        populate(map, rows, columns, plant2, 3);
        populate(map, rows, columns, rock2, 3);
        populate(map, rows, columns, wood2, 3);
        populate(map, rows, columns, portal1, 1);
        populate(map, rows, columns, portal2, 1);
        populate(map, rows, columns, monster2, 10);
    }else if(level == 3){
        populate(map, rows, columns, plant3, 3);
        populate(map, rows, columns, rock3, 3);
        populate(map, rows, columns, wood3, 3);
        populate(map, rows, columns, portal2, 1);
        populate(map, rows, columns, monster3, 10);
        populate(map, rows, columns, boss, 1);
    }
}

void initMap(Levels *lv, int rows, int columns, PlayerPos *pc){

    lv->rows = rows;
    lv->columns = columns;

    lv->lv1 = createLevel(rows,columns);
    populateLevel(lv->lv1, rows, columns, 1);
    addPlayer(lv->lv1, rows, columns, pc);

    lv->lv2 = createLevel(rows,columns);
    populateLevel(lv->lv2, rows, columns, 2);

    lv->lv3 = createLevel(rows,columns);
    populateLevel(lv->lv3, rows, columns, 3);
}
