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

    fclose(file);
}
