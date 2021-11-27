#include "../headers/header.h"

//a simple function generating a random number between min and max included
int rand2 (int min, int max){
    return (rand()%(max-min+1)) + min;
}

void getColor(int entity){
    if(entity == _player){
        printf(YELLOW);
    }else if(isMapRessource(entity)){
        printf(GREEN);
    }else if(entity == _wall){
        printf(MAGENTA);
    }else if(entity == _npc){
        printf(BLUE);
    }else if(isMonster(entity)){
        printf(RED);
    }else if(entity == _portal1 || entity == _portal2){
        printf(CYAN);
    }
}
//used to display the map to the player
void printMap(int **map, int rows, int columns){

    for (int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            getColor(map[i][j]);
            printf(" %2d " RESET, map[i][j]);
        }
        printf("\n");
    }
}

//create a struct level (filled with 0)
void createLevel(Level *level, int rows, int columns, int nbLevel){
    level->map = malloc(sizeof(int*)*rows);
    level->monsterList = NULL;
    level->ressourceList = NULL;
    level->value = nbLevel;
    level->rows = rows;
    level->columns = columns;

    for(int i = 0; i < columns; i ++){
        level->map[i] = malloc(sizeof(int)*columns);
    }

    for(int j = 0; j < rows; j++){
        for(int k = 0; k < columns; k++){
            level->map[j][k] = 0;
        }
    }
}

// add the player on the map
void addPlayer(Level *level, Player *player){
    int row;
    int column;

    do{
        row = rand2(0, level->rows-1);
        column = rand2(0, level->columns-1);
    }while(level->map[row][column] != _empty);

    player->row = row;
    player->column = column;

    level->map[row][column] = _player;
}

//will add a number of entity to the map
void populate(Level *level, int entity, int quantity){
    int row;
    int column;
    int monsterVal;

    for(int i = 0 ; i< quantity; i++){
        do{
            row = rand2(0, level->rows-1);
            column = rand2(0, level->columns-1);
        }while(level->map[row][column] != _empty);

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

//used to add the different entities (monster, ressource, pnj...) to the map
void populateLevel(Level *level){
    populate(level, _npc, 1);
    populate(level, _wall, 7);

    if(level->value == 1){
        populate(level, _plant1, 3);
        populate(level, _rock1, 3);
        populate(level, _wood1, 3);
        populate(level, _portal1, 1);
        populate(level, _monster1, 10);
    }else if(level->value == 2){
        populate(level, _plant2, 3);
        populate(level, _rock2, 3);
        populate(level, _wood2, 3);
        populate(level, _portal1, 1);
        populate(level, _portal2, 1);
        populate(level, _monster2, 10);
    }else if(level->value == 3){
        populate(level, _plant3, 3);
        populate(level, _rock3, 3);
        populate(level, _wood3, 3);
        populate(level, _portal2, 1);
        populate(level, _monster3, 10);
        populate(level, _boss, 1);
    }
}

//used to init the map (create & populate it)
void initMap(Levels *levels, int rows, int columns, Player *player){

    levels->lv1 = malloc(sizeof(Level));
    levels->lv2 = malloc(sizeof(Level));
    levels->lv3 = malloc(sizeof(Level));
    levels->chest = NULL;

    createLevel(levels->lv1, rows, columns, 1);
    populateLevel(levels->lv1);
    addPlayer(levels->lv1, player);

    createLevel(levels->lv2, rows, columns, 2);
    populateLevel(levels->lv2);

    createLevel(levels->lv3, rows, columns, 3);
    populateLevel(levels->lv3);
}
