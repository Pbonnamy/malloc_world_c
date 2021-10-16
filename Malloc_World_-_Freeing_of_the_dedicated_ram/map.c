#include "header.h"

void printMap(int **map, int rows, int columns){

    for (int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            printf(" %d ", map[i][j]);
        }
        printf("\n");
    }
}

void initMap(int rows, int columns){
    int ** map = malloc(sizeof(int*)*rows);

    for(int i = 0; i < columns; i ++){
        map[i] = malloc(sizeof(int)*columns);
    }

    for(int j = 0; j < rows; j++){
        for(int k = 0; k < columns; k++){
            map[j][k] = 0;
        }
    }

    printMap(map, rows, columns);
}
