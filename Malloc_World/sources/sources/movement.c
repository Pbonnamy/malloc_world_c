#include "../headers/header.h"

//get the current level the player is in
Level *getCurrentMap(Player *player, Levels *levels){
    if(player->currentMapLvl == 1){
        return levels->lv1;
    }else if(player->currentMapLvl == 2){
        return levels->lv2;
    }else if(player->currentMapLvl == 3){
        return levels->lv3;
    }

    return NULL;
}

//used to switch between the 3 different map level
void switchLevel(int target, Player *player, Levels *levels){

    Level *currentMap = getCurrentMap(player, levels);
    currentMap->map[player->row][player->column] = _empty;

    if(target == _portal1){
       if(player->currentMapLvl == 1){
            player->currentMapLvl = 2;
       }else if (player->currentMapLvl == 2){
            player->currentMapLvl = 1;
       }
    }else if(target == _portal2){
        if(player->currentMapLvl == 2){
            player->currentMapLvl = 3;
       }else if (player->currentMapLvl == 3){
            player->currentMapLvl = 2;
       }
    }

    printf("\nYou switched to map level %d\n\n", player->currentMapLvl);

    Level *newMap = getCurrentMap(player, levels);
    addPlayer(newMap, player);
}

//handle the different encounter on the map (ressource, ennemies, pnj...)
int checkCollision(Level *level, int targetRow, int targetColumn, Player *player, Levels *levels){
    int allowed = _notAllowed;

    if(targetRow >= 0 && targetRow < level->rows && targetColumn >= 0 && targetColumn < level->columns){
        int target = level->map[targetRow][targetColumn];

        if(isMapRessource(target)){

            RessourceNode *ressourceNode = findRessourceNode(level->ressourceList, targetRow, targetColumn);
            allowed = harvestRessource(ressourceNode, player);

        }else if (isMonster(target)){

            MonsterNode *monsterNode = findMonsterNode(level->monsterList, targetRow, targetColumn);
            allowed = handleCombat(monsterNode, player);

        }else if (target == _portal1 || target == _portal2){

            switchLevel(target, player, levels);

        }else if (target == _npc){

            handleNpc(player, levels->chest);

        }else if( target ==  _wall){

            printf("\nImpossible : this is a wall\n\n");

        }else{
            printf("\n\n\n");
            allowed = _allowed;
        }
    }else{
        printf("\nError : movement not allowed\n\n");
    }

    return allowed;
}


//used to change the postion of the player on the map according to the desired direction (up, down, left, right)
int move (Level *level, Player *player, char direction, Levels *levels){

    level->map[player->row][player->column] = _empty;
    int state = _notAllowed;

    if(direction == 'z'){
        if((state = checkCollision(level, player->row-1, player->column, player, levels))){
            player->row -= 1;
        }
    }else if(direction == 's'){
        if((state = checkCollision(level, player->row+1, player->column, player, levels))){
            player->row += 1;
        }
    }else if(direction == 'q'){
        if((state = checkCollision(level, player->row, player->column-1, player, levels))){
            player->column -= 1;
        }
    }else if (direction == 'd'){
        if((state = checkCollision(level, player->row, player->column+1, player, levels))){
            player->column += 1;
        }
    }

    Level *current = getCurrentMap(player, levels); //if level has changed
    current->map[player->row][player->column] = _player;

    return state;
}

//main loop to handle movement (step 1 -> display the map, step 2 -> ask the player for an action to execute)
int handleMovement(Levels *levels, Player *player){

    char direction;
    int state = _continu;

    printf("\n\n\n");

    do{
        Level *currentLevel = getCurrentMap(player, levels);

        respawnMonsters(currentLevel, currentLevel->monsterList, player);
        respawnRessource(currentLevel, currentLevel->ressourceList, player);

        printMap(currentLevel->map, currentLevel->rows, currentLevel->columns);

        printf("\nWhich direction ? (z : up, s : down, q : left, d : right ) (e : exit) : ");
        fflush(stdin);
        scanf("%c", &direction);

        system("cls"); //clear console

        state = move(currentLevel, player, direction, levels);

    }while(direction != 'e' && state != _end);

    return state;
}
