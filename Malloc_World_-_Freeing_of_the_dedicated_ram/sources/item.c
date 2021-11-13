#include "../headers/header.h"

int isWeapon(int entity){
    if(entity == _woodSword || entity == _stoneSword || entity == _ironSword || entity == _diamondSword||
       entity == _stoneSpear || entity == _ironSpear || entity == _diamondSpear||
       entity == _stoneHammer || entity == _ironHammer || entity == _diamondHammer){
        return 1;
    }else{
        return 0;
    }
}

int isArmor(int entity){
    if(entity == _stoneArmor || entity == _ironArmor || entity == _diamondArmor){
        return 1;
    }else{
        return 0;
    }
}

int isTool(int entity){
    if(entity == _woodPickaxe || entity == _woodBillhook || entity == _woodAxe ||
       entity == _stonePickaxe || entity == _stoneBillhook || entity == _stoneAxe ||
       entity == _ironPickaxe || entity == _ironBillhook || entity == _ironAxe){
        return 1;
    }else{
        return 0;
    }
}

int isHeal(int entity){
    if(entity == _potion1 || entity == _potion2 || entity == _potion3){
        return 1;
    }else{
        return 0;
    }
}

int isItemRessource(int entity){
    if(entity == _fir || entity == _stone || entity == _herb ||
       entity == _beech || entity == _iron || entity == _lavender ||
       entity == _oak || entity == _diamond || entity == _hemp){
        return 1;
    }else{
        return 0;
    }
}

int findItemReference(int entity){
    for(int i = 0; i < TOTAL_ITEMS;i++){
        if(atoi(ITEMS[i][_entity]) == entity){
            return i;
        }
    }
    return -1;
}

int getDurability(int item){
    if(isTool(item)){
        return TOOL_DURABILITY;
    }else if(item == _woodSword || item == _stoneSword || item == _ironSword || item == _diamondSword){
        return SWORD_DURABILITY;
    }else if(item == _stoneSpear || item == _ironSpear || item == _diamondSpear){
        return SPEAR_DURABILITY;
    }else if(item == _stoneHammer || item == _ironHammer || item == _diamondHammer){
        return HAMMER_DURABILITY;
    }

    return -1;
}

int checkDurability(int ressource, int durability){
    int allowed = 1;

    if(getRessourceLevel(ressource) == 1){
        if(durability < WEAR_LV1){
            allowed = 0;
        }
    }else if(getRessourceLevel(ressource) == 2){
        if(durability < WEAR_LV2){
            allowed = 0;
        }
    }else if(getRessourceLevel(ressource) == 3){
        if (durability < WEAR_LV3){
            allowed = 0;
        }
    }

    return allowed;
}

int isRequiredTool(int tool, int ressource, int durability){
    int allowed = 0;

    for(int i = 0; i < TOTAL_REQUIRED; i++){
        if(ressource == REQUIRED_TOOL[i][_ressource]){
            for (int j = _firstPossibleTool; j <= _lastPossibleTool; j++){
                if(tool == REQUIRED_TOOL[i][j] && checkDurability(ressource, durability)){
                    allowed = 1;
                }
            }
        }
    }

    return allowed;
}

void handleToolDurability(InventoryNode *inventoryNode, int ressource){
    if(getRessourceLevel(ressource) == 1){
        inventoryNode->durability -= WEAR_LV1;
    }else if(getRessourceLevel(ressource) == 2){
        inventoryNode->durability -= WEAR_LV2;
    }else if(getRessourceLevel(ressource) == 3){
        inventoryNode->durability -= WEAR_LV3;
    }

    if(inventoryNode->durability < 0){
        inventoryNode->durability = 0;
    }
}

void printItem(int item, int reference, int quantity, int durability){
    if(isTool(item)){
        printf("%d/%d %s\n", durability, getDurability(item), ITEMS[reference][_name]);
    }else if(isWeapon(item)){
        printf("%d/%d %s (damage : %s)\n", durability, getDurability(item), ITEMS[reference][_name], ITEMS[reference][_info]);
    }else if(isArmor(item)){
        printf("%s (damage resistance : %s %%)\n", ITEMS[reference][_name], ITEMS[reference][_info]);
    }else if(isItemRessource(item)){
        printf("%d %s\n", quantity, ITEMS[reference][_name]);
    }else if(isHeal(item)){
        printf("%d %s (heal : %s HP)\n", quantity, ITEMS[reference][_name], ITEMS[reference][_info]);
    }
}

