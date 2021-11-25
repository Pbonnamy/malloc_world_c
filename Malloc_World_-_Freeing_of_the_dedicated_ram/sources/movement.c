#include "../headers/header.h"

//handle the different encounter on the map (ressource, ennemies, pnj...)
int checkCollision(Level *level, int targetRow, int targetColumn, Player *player, InventoryNode *chest){
    int allowed = 0;

    if(targetRow >= 0 && targetRow < level->rows && targetColumn >= 0 && targetColumn < level->columns){
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

            handleNpc(player, chest);

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

//used to change the postion of the player on the map according to the desired direction (up, down, left, right)
void move (Level *level, Player *player, char direction, InventoryNode *chest){

    level->map[player->row][player->column] = _empty;

    if(direction == 'z'){
        if(checkCollision(level, player->row-1, player->column, player, chest)){
            player->row -= 1;
        }
    }else if(direction == 's'){
        if(checkCollision(level, player->row+1, player->column, player, chest)){
            player->row += 1;
        }
    }else if(direction == 'q'){
        if(checkCollision(level, player->row, player->column-1, player, chest)){
            player->column -= 1;
        }
    }else if (direction == 'd'){
        if(checkCollision(level, player->row, player->column+1, player, chest)){
            player->column += 1;
        }
    }

    level->map[player->row][player->column] = _player;

}

//main loop to handle movement (step 1 -> display the map, step 2 -> ask the player for an action to execute)
void handleMovement(Levels *levels, Player *player){

    char direction;

    printf("\n\n\n");

    do{
        printMap(levels->lv1->map, levels->lv1->rows, levels->lv1->columns);

        printf("\nWhich direction ? (z : up, s : down, q : left, d : right ) (e : exit) : ");
        fflush(stdin);
        scanf("%c", &direction);

        system("cls"); //clear console

        move(levels->lv1, player, direction, levels->chest);

    }while(direction != 'e');
}
