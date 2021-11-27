#include "../headers/header.h"

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

void saveChest(InventoryNode *chest, FILE *file){

    while(chest != NULL){
        fprintf(file,"{%d}@{%d}", chest->quantity, chest->value);
        chest = chest->next;

        if(chest != NULL){
            fprintf(file,"\n");
        }
    }
}

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

void skipLine(FILE *file, int skip){
    int count = 0;
    char buffer[255];

    while(count < skip){
        count ++;
        fgets(buffer, 255, file);
    }

}

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

void fillLevel(Level *level, FILE *file){
    int col = 0;
    int row = 0;
    char buffer[255];
    char *column;

    while(row < level->rows){
        fgets(buffer, 255, file);

        buffer[strcspn(buffer, "\n")] = 0;

        column = strtok(buffer, " ");

        while(column != NULL ) {
            level->map[row][col] = atoi(column);
            column = strtok(NULL, " ");
            col ++;
        }
        col = 0;

        row ++;
    }
}


void loadLevels(FILE *file, Levels *levels){
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

    fillLevel(levels->lv1, file);
    skipLine(file, 1);
    fillLevel(levels->lv2, file);
    skipLine(file, 1);
    fillLevel(levels->lv3, file);

}

void loadSave(Levels *levels, Player *player) {
    FILE *file = fopen("save.txt", "r");

    if(!file){
        printf("\nNo save file available\n");
        return;
    }

    loadLevels(file, levels);

    //gameLoop(levels, player);

    fclose(file);
}


