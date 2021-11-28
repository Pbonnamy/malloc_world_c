#include "../headers/header.h"

//used to write a map in the save file
void saveMap(Level *level, FILE *file){

    fprintf(file,"-- ZONE %d --\n", level->value);

    for (int i = 0; i < level->rows; i++){
        for(int j = 0; j < level->columns; j++){
            if(j+1 == level->columns){
                fprintf(file,"%d", level->map[i][j]);
            }else{
                fprintf(file,"%d ", level->map[i][j]);
            }
        }
        fprintf(file,"\n");
    }
}

//used to write the player inventory in the save file
void saveInventory(InventoryNode *inventoryHead, FILE *file){
    int count = 0;
    int durability;

    while(inventoryHead != NULL){
        count ++;
        if(inventoryHead->durability == _nothing){
            durability = 0;
        }else{
            durability = inventoryHead->durability;
        }

        fprintf(file,"{%d}@{%d}@{%d}\n", inventoryHead->quantity, inventoryHead->value, durability);

        inventoryHead = inventoryHead->next;
    }

    while(count < MAX_INVENTORY_COUNT){
        count ++;
        fprintf(file,"{0}@{0}@{0}\n");
    }
}

//used to write the chest content in the save file
void saveChest(InventoryNode *chest, FILE *file){

    while(chest != NULL){
        fprintf(file,"{%d}@{%d}", chest->quantity, chest->value);
        chest = chest->next;

        if(chest != NULL){
            fprintf(file,"\n");
        }
    }
}

//used to write the player in the save file
void savePlayer(Player *player, FILE *file, InventoryNode *chest){
    fprintf(file,"{%d}\n", player->level);

    int index = findLevelRequirement(player->level + 1);
    fprintf(file, "{%d}/{%d}\n", player->xp, LEVELS[index][_xpRequired]);

    fprintf(file,"{%d}/{%d}\n", player->currentHp, player->maxHp);

    fprintf(file,"-- INVENTORY --\n");

    saveInventory(player->inventory, file);

    fprintf(file,"-- STORAGE --\n");

    saveChest(chest, file);
}

//main save function (1 -> save map, 2-> save player (info + inventory + chest))
void save(Levels *levels, Player *player){
    FILE *file = fopen("save.txt", "w");

    fprintf(file,"=== MAP ===\n");

    saveMap(levels->lv1, file);
    saveMap(levels->lv2, file);
    saveMap(levels->lv3, file);

    fprintf(file,"=== PLAYER ===\n");

    savePlayer(player, file, levels->chest);

    printf("\nGame saved.\n");
    fclose(file);
}

//used to skip a line in the text file
void skipLine(FILE *file, int skip){
    int count = 0;
    char buffer[255];

    while(count < skip){
        count ++;
        fgets(buffer, 255, file);
    }

}

//retrieve the size of the map in the save file
void checkMapSize(FILE *file, Level *level){
    char buffer[255];
    int countRow = 0;
    int countCol = 0;
    int calculatedCol = 0;

    while(fgets(buffer, 255, file)){

        if(buffer[1] == '=' || buffer[1] == '-'){
            break;
        }
        countRow++;

        if(!calculatedCol){
            char *column = strtok(buffer, " ");

            while(column != NULL ) {
              column = strtok(NULL, " ");
              countCol++;
            }

           calculatedCol = 1;
        }
    };

    level->columns = countCol;
    level->rows = countRow;
}

//will populate the level with the informations from the save file
void fillLevel(Level *level, FILE *file, Player *player){
    int col = 0;
    int row = 0;
    char buffer[255];
    char *column;
    int entity;

    while(row < level->rows){
        fgets(buffer, 255, file);
        buffer[strcspn(buffer, "\n")] = 0;
        column = strtok(buffer, " ");

        while(column != NULL ) {
            entity = atoi(column);
            level->map[row][col] = entity;

            if(isMapRessource(entity)){
                addToRessourceList(&level->ressourceList, entity, row, col);
            }else if(isMonster(entity)){
                addToMonsterList(&level->monsterList, entity, row, col);
            }else if (entity == _player){
                player->currentMapLvl = level->value;
                player->row = row;
                player->column = col;
            }

            column = strtok(NULL, " ");
            col ++;
        }
        col = 0;

        row ++;
    }
}

//used to retrieve info of the 3 different levels in the save file
void loadLevels(FILE *file, Levels *levels, Player *player){
    skipLine(file, 2);

    levels->lv1 = malloc(sizeof(Level));
    levels->lv2 = malloc(sizeof(Level));
    levels->lv3 = malloc(sizeof(Level));

    checkMapSize(file, levels->lv1);
    checkMapSize(file, levels->lv2);
    checkMapSize(file, levels->lv3);

    createLevel(levels->lv1, levels->lv1->rows, levels->lv1->columns, 1);
    createLevel(levels->lv2, levels->lv2->rows, levels->lv2->columns, 2);
    createLevel(levels->lv3, levels->lv3->rows, levels->lv3->columns, 3);

    fseek(file, 0, SEEK_SET);
    skipLine(file, 2);

    fillLevel(levels->lv1, file, player);
    skipLine(file, 1);
    fillLevel(levels->lv2, file, player);
    skipLine(file, 1);
    fillLevel(levels->lv3, file, player);
}

//used to retrieve different informations from a line containing an item ({QTY}@{OBJECTID}@{DURABILITY?})
int processItemLine(char buffer[255], int infoPos){
    char *splited;
    char *res;
    int count = 0;
    char tmpBuffer[255];

    strncpy(tmpBuffer, buffer, 255);

    while(count < infoPos){
        if(count == 0){
            splited = strtok(tmpBuffer, "@");
        }else{
            splited = strtok(NULL, "@");
        }

        count ++;
    }

    res = strtok(splited, "{}");

    return atoi(res);
}

//used to retrieve the different items of the player inventory in the save file
void loadInventory(FILE *file, Player *player){
    int count = 0;
    char buffer[255];
    int quantity;
    int item;
    int durability;

    while(count < MAX_INVENTORY_COUNT){
        fgets(buffer, 255, file);

        item = processItemLine(buffer, _itemPos);
        quantity = processItemLine(buffer, _quantityPos);
        durability = processItemLine(buffer, _durabilityPos);

        if(durability == 0){
            durability = _notSpecified;
        }

        if(item != 0){
            addToStorage(&player->inventory, item, quantity, MAX_INVENTORY_COUNT, durability);
        }

        count++;
    }
}

//used to retrieve the different items of the chest in the save file
void loadChest(FILE *file, Levels *levels){
    char buffer[255];
    int item;
    int quantity;

    while(fgets(buffer, 255, file)){
        item = processItemLine(buffer, _itemPos);
        quantity = processItemLine(buffer, _quantityPos);

        addToStorage(&levels->chest, item, quantity, NO_STORAGE_LIMIT, _notSpecified);
    }
}

//used to retrieve the info of a player from teh save file (1 -> info, 2 -> inventory, 3-> chest)
void loadPlayer(FILE *file, Player *player, Levels *levels){
    char buffer[255];
    char *res;

    fgets(buffer, 255, file); //level
    res = strtok(buffer, "{}");
    player->level = atoi(res);

    fgets(buffer, 255, file); //xp
    res = strtok(buffer, "{}");
    player->xp = atoi(res);

    fgets(buffer, 255, file); //hp / current hp
    res = strtok(buffer, "{}");
    player->currentHp = atoi(res);
    res = strtok(NULL, "{}");
    res = strtok(NULL, "{}");
    player->maxHp = atoi(res);

    skipLine(file, 1);
    player->inventory = NULL;
    loadInventory(file, player);

    skipLine(file, 1);
    levels->chest = NULL;
    loadChest(file, levels);
}

//main function to load the different informations from the save.txt file (1 -> load level, 2 -> load player)
void loadSave(Levels *levels, Player *player) {
    FILE *file = fopen("save.txt", "r");

    if(!file){
        printf("\nNo save file available\n");
        return;
    }

    loadLevels(file, levels, player);
    skipLine(file, 1);
    loadPlayer(file, player, levels);

    fclose(file);
}


