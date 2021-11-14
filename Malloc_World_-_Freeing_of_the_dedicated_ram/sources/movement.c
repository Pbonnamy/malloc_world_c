#include "../headers/header.h"

int checkCollision(Level *level, int targetRow, int targetColumn, int rows, int columns, Player *player){
    int allowed = 0;

    if(targetRow >= 0 && targetRow < rows && targetColumn >= 0 && targetColumn < columns){
        int target = level->map[targetRow][targetColumn];

        if(isMapRessource(target)){

            RessourceNode *ressourceNode = findRessourceNode(level->ressourceList, targetRow, targetColumn);
            allowed = harvestRessource(ressourceNode, player);

        }else if (isMonster(target)){

            MonsterNode *monsterNode = findMonsterNode(level->monsterList, targetRow, targetColumn);
            allowed = handleCombat(monsterNode, player);

        }else if (target == _portal1 || target == _portal2){

            printf("\nTODO : switch level\n\n");

        }else if (target == _npc){

            printf("\nTODO : handle npc\n\n");

        }else if( target ==  _wall){

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

void move (Level *level, Player *player, char direction, int rows, int columns){

    level->map[player->row][player->column] = _empty;

    if(direction == 'z'){
        if(checkCollision(level, player->row-1, player->column, rows, columns, player)){
            player->row -= 1;
        }
    }else if(direction == 's'){
        if(checkCollision(level, player->row+1, player->column, rows, columns, player)){
            player->row += 1;
        }
    }else if(direction == 'q'){
        if(checkCollision(level, player->row, player->column-1, rows, columns, player)){
            player->column -= 1;
        }
    }else if (direction == 'd'){
        if(checkCollision(level, player->row, player->column+1, rows, columns, player)){
            player->column += 1;
        }
    }

    level->map[player->row][player->column] = _player;

}

void handleMovement(Levels *levels, Player *player){

    char direction;

    printf("\n\n\n");

    do{
        printMap(levels->lv1->map, levels->rows, levels->columns);

        printf("\nWhich direction ? (z : up, s : down, q : left, d : right ) (e : exit) : ");
        fflush(stdin);
        scanf("%c", &direction);

        system("cls"); //clear console

        move(levels->lv1, player, direction, levels->rows, levels->columns);

    }while(direction != 'e');
}
