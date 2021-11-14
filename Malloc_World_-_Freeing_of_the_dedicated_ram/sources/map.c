#include "../headers/header.h"

int rand2 (int min, int max){
    return (rand()%(max-min+1)) + min;
}

void printMap(int **map, int rows, int columns){

    for (int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            if(map[i][j] == _player){
                printf(RED " %2d " RESET, map[i][j]);
            }else{
                printf(" %2d ", map[i][j]);
            }

        }
        printf("\n");
    }
}

void createLevel(Level *level, int rows, int columns, int nbLevel){
    level->map = malloc(sizeof(int*)*rows);
    level->monsterList = NULL;
    level->ressourceList = NULL;
    level->value = nbLevel;

    for(int i = 0; i < columns; i ++){
        level->map[i] = malloc(sizeof(int)*columns);
    }

    for(int j = 0; j < rows; j++){
        for(int k = 0; k < columns; k++){
            level->map[j][k] = 0;
        }
    }
}

void addPlayer(Level *level, int rows, int columns, Player *player){
    int row = rand2(0,rows-1);
    int column = rand2(0,columns-1);

    while(level->map[row][column] != _empty){
        row = rand2(0,rows-1);
        column = rand2(0,rows-1);
    }

    player->row = row;
    player->column = column;

    level->map[row][column] = _player;
}

void populate(Level *level, int rows, int columns, int entity, int quantity){
    int row = rand2(0,rows-1);
    int column = rand2(0,columns-1);
    int monsterVal;

    for(int i = 0 ; i< quantity; i++){
        while(level->map[row][column] != _empty){
            row = rand2(0,rows-1);
            column = rand2(0,rows-1);
        }

        if(entity == _monster1){
            monsterVal = rand2(_monster1, _monster2-1);
            level->map[row][column] = monsterVal;
        }else if(entity == _monster2){
            monsterVal = rand2(_monster2, _monster3-1);
            level->map[row][column] = monsterVal;
        }else if(entity == _monster3){
            monsterVal = rand2(_monster3, _lastMonster-1);
            level->map[row][column] = monsterVal;
        }else{
            level->map[row][column] = entity;
        }

        if(isMapRessource(entity)){
            addToRessourceList(&level->ressourceList, entity, row, column);
        }else if (isMonster(entity)){
            addToMonsterList(&level->monsterList, monsterVal, row, column);
        }
    }
}

void populateLevel(Level *level, int rows, int columns){
    populate(level, rows, columns, _npc, 1);
    populate(level, rows, columns, _wall, 7);

    if(level->value == 1){
        populate(level, rows, columns, _plant1, 3);
        populate(level, rows, columns, _rock1, 3);
        populate(level, rows, columns, _wood1, 3);
        populate(level, rows, columns, _portal1, 1);
        populate(level, rows, columns, _monster1, 10);
    }else if(level->value == 2){
        populate(level, rows, columns, _plant2, 3);
        populate(level, rows, columns, _rock2, 3);
        populate(level, rows, columns, _wood2, 3);
        populate(level, rows, columns, _portal1, 1);
        populate(level, rows, columns, _portal2, 1);
        populate(level, rows, columns, _monster2, 10);
    }else if(level->value == 3){
        populate(level, rows, columns, _plant3, 3);
        populate(level, rows, columns, _rock3, 3);
        populate(level, rows, columns, _wood3, 3);
        populate(level, rows, columns, _portal2, 1);
        populate(level, rows, columns, _monster3, 10);
        populate(level, rows, columns, _boss, 1);
    }
}

void initMap(Levels *levels, int rows, int columns, Player *player){

    levels->rows = rows;
    levels->columns = columns;

    levels->lv1 = malloc(sizeof(Level));
    levels->lv2 = malloc(sizeof(Level));
    levels->lv3 = malloc(sizeof(Level));

    createLevel(levels->lv1, rows, columns, 1);
    populateLevel(levels->lv1, rows, columns);
    addPlayer(levels->lv1, rows, columns, player);

    createLevel(levels->lv2, rows, columns, 2);
    populateLevel(levels->lv2, rows, columns);

    createLevel(levels->lv3, rows, columns, 3);
    populateLevel(levels->lv3, rows, columns);
}
