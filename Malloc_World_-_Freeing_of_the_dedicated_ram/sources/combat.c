#include "../headers/header.h"

int flee(){
    int rate = rand2(1,100);
    int loop = 1;

    if(rate <= FLEE_RATE){
        loop = 0;
    }

    if(loop == 1){
        printf("\nYou failed to flee\n");
    }else if(loop == 0){
        printf("\nYou fled\n\n");
    }

    return loop;
}

void attack(MonsterNode *monsterNode, InventoryNode *weapon){
    if(weapon != NULL && weapon->durability > 0){
        int damage = atoi(ITEMS[weapon->reference][_info]);
        monsterNode->hp -= damage;

        if(monsterNode->hp <= 0){
            monsterNode->hp = 0;
        }

        printf("\nYou deal %d damage\n", damage);
        weapon->durability -= WEAR_COMBAT;

        if(weapon->durability == 0){
            printf("\nYour weapon is now broken\n");
        }
    }else{
        printf("\nYour deal 0 damage\n");
    }
}

void monsterAttack(Player *player, InventoryNode *armor, MonsterNode *monster){
    int damage = atoi(MONSTERS[monster->reference][_monsterDamage]);

    if(armor != NULL){
        damage -= round((damage*atoi(ITEMS[armor->reference][_info]))/100);
    }

    player->currentHp -= damage;

    printf("\nYou take %d damage\n", damage);
}

int findLevelRequirement(int level){

    for(int i = 0; i < TOTAL_LEVELS; i++){
        if(LEVELS[i][_level] == level){
            return i;
        }
    }

    return -1;
}

void leveling(Player *player, MonsterNode *monster){
    int xp = atoi(MONSTERS[monster->reference][_monsterXp]);
    player->xp += xp;

    printf("\nYou defeated '%s'. You gain %d xp.\n", MONSTERS[monster->reference][_name], xp);
    int index = findLevelRequirement(player->level + 1);

    if(index != -1){
        if(player->xp >= LEVELS[index][_xpRequired]){
            player->level = LEVELS[index][_level];
            player->maxHp += LEVELS[index][_levelBonus];
            player->currentHp = player->maxHp;

            player->xp -= LEVELS[index][_xpRequired];

            printf("\nYou level up ! You are now level %d\n", player->level);
        }
    }
}

void handlePotion(Player *player, int index){

    int count = 0;

    InventoryNode *inventoryHead = player->inventory;

    while(inventoryHead != NULL){
        if (isHeal(inventoryHead->value)){
            count ++;
            if(count == index){
                player->currentHp += atoi(ITEMS[inventoryHead->reference][_info]);

                if(player->currentHp > player->maxHp){
                    player->currentHp = player->maxHp;
                }

                removeItem(player->inventory, _heal, index);

                return;
            }
        }
        inventoryHead = inventoryHead->next;
    }
}

void potion(Player *player){
    printf("\n%s Availables : \n\n", ITEM_TYPE[_heal]);
    int chosen;

    int index = availableItems(player->inventory, _heal);

    if(index == 0){
        printf("No %s available !\n", ITEM_TYPE[_heal]);
    }else if(index == 1){
        handlePotion(player, index);
    }else{
        do{
            printf("\nChoose a %s : ", ITEM_TYPE[_heal]);

            fflush(stdin);
            scanf("%d", &chosen);
        }while(chosen <= 0 && chosen > index);

        handlePotion(player, index);
    }
}

int handleCombat(MonsterNode *monsterNode, Player *player){
    char action;
    int loop = 1;
    int defeated = 0;

    printf("\nYour are fighting a %s - Hp : %d | Dmg : %s\n", MONSTERS[monsterNode->reference][_name], monsterNode->hp, MONSTERS[monsterNode->reference][_monsterDamage]);

    InventoryNode *weapon = itemSelect(player->inventory, _weapon);

    InventoryNode *armor = itemSelect(player->inventory, _armor);

    do{
        printf("\nChoose an action ? (a : attack, p : use a potion, f : try to flee)  : ");
        fflush(stdin);
        scanf("%c", &action);

        system("cls"); //clear console

        if(action == 'a'){
            attack(monsterNode, weapon);
        }else if(action == 'p'){
            potion(player);
        }else if(action == 'f'){
            loop = flee();
        }

        if(loop){
            if(monsterNode->hp > 0){
                monsterAttack(player, armor, monsterNode);
            }

            if(player->currentHp > 0){
                if(monsterNode-> hp > 0){
                    printf("\nYour HP : %d | Ennemy HP : %d\n", player->currentHp, monsterNode->hp);
                }else{
                    if(monsterNode->value != _boss){
                        leveling(player, monsterNode);
                        loop = 0;
                        defeated = 1;
                    }else{
                        printf("\nYou killed the boss. YOU WIN.\n");
                    }
                }
            }else{
                printf("\nYou are dead. GAME OVER.\n");
                loop = 0;
            }
        }

    }while(loop);

    return defeated;
}
