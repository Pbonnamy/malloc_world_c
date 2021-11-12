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
    for(int i = 0; i < TOTAL_DATAS;i++){
        if(atoi(DATAS[i][_entity]) == entity){
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

void printItem(int item, int reference, int quantity, int durability){
    if(isTool(item)){
        printf("%s (durability : %d / %d)\n", DATAS[reference][_name], durability, getDurability(item));
    }else if(isWeapon(item)){
        printf("%s (durability : %d / %d) - (damage : %s)\n", DATAS[reference][_name], durability, getDurability(item), DATAS[reference][_info]);
    }else if(isArmor(item)){
        printf("%s (damage resistance : %s %% )\n", DATAS[reference][_name], DATAS[reference][_info]);
    }else if(isItemRessource(item)){
        printf("%d %s\n", quantity, DATAS[reference][_name]);
    }else if(isHeal(item)){
        printf("%d %s (heal : %s HP)\n", quantity, DATAS[reference][_name], DATAS[reference][_info]);
    }
}

