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

void initMap(){
    int rows = 10;
    int columns = 10;

    int **lv1 = createLevel(rows,columns);

    printMap(lv1, rows, columns);
}
