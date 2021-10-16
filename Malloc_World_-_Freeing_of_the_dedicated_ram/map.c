#include "header.h"

int rand2 (int min, int max){
    return (rand()%(max-min+1)) + min;
}

void printMap(int **map, int rows, int columns){

    for (int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            printf(" %2d ", map[i][j]);
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

void populate(int **map, int rows, int columns, int entity, int max){
    int row = rand2(0,rows-1);
    int column = rand2(0,columns-1);

    for(int i = 0 ; i< max; i++){
        while(map[row][column] != 0){
            row = rand2(0,rows-1);
            column = rand2(0,rows-1);
        }
        map[row][column] = entity;
    }
}

void populateLevel(int **map, int rows, int columns, int level){
    populate(map, rows, columns, playerVal, 1);
    populate(map, rows, columns, npcVal, 1);
    populate(map, rows, columns, wallVal, 7);

    if(level == 1){
        populate(map, rows, columns, plant1Val, 3);
        populate(map, rows, columns, rock1Val, 3);
        populate(map, rows, columns, wood1Val, 3);
        populate(map, rows, columns, portal1Val, 1);
    }else if(level == 2){
        populate(map, rows, columns, plant2Val, 3);
        populate(map, rows, columns, rock2Val, 3);
        populate(map, rows, columns, wood2Val, 3);
        populate(map, rows, columns, portal1Val, 1);
        populate(map, rows, columns, portal2Val, 1);
    }else if(level == 3){
        populate(map, rows, columns, plant3Val, 3);
        populate(map, rows, columns, rock3Val, 3);
        populate(map, rows, columns, wood3Val, 3);
        populate(map, rows, columns, portal2Val, 1);
    }
}

void initMap(){
    srand(time(NULL));

    int rows = 7;
    int columns = 7;

    int **lv1 = createLevel(rows,columns);
    populateLevel(lv1, rows, columns,1);

    int **lv2 = createLevel(rows,columns);
    populateLevel(lv2, rows, columns,2);

    int **lv3 = createLevel(rows,columns);
    populateLevel(lv3, rows, columns,3);

    printMap(lv3, rows, columns);
}
