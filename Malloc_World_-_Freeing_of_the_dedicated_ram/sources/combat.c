#include "../headers/header.h"

//when the player is trying to flee during combat
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

//when the player is attacking the monster
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

//when the monster is attacking the player
void monsterAttack(Player *player, InventoryNode *armor, MonsterNode *monster){
    int damage = atoi(MONSTERS[monster->reference][_monsterDamage]);

    if(armor != NULL){
        damage -= round((damage*atoi(ITEMS[armor->reference][_info]))/100);
    }

    player->currentHp -= damage;

    printf("\nYou take %d damage\n", damage);
}

//to find how many xp the player need to reach the new level
int findLevelRequirement(int level){

    for(int i = 0; i < TOTAL_LEVELS; i++){
        if(LEVELS[i][_level] == level){
            return i;
        }
    }

    return TOTAL_LEVELS-1;
}

//calculate how many xp the player gained after defeating the monster
//reach the next level is requirement are met
void leveling(Player *player, MonsterNode *monster){
    int xp = atoi(MONSTERS[monster->reference][_monsterXp]);
    player->xp += xp;

    printf("\nYou defeated '%s'. You gain %d xp.\n\n", MONSTERS[monster->reference][_name], xp);
    int index = findLevelRequirement(player->level + 1);

    if(player->level < MAX_LEVEL){
        if(player->xp >= LEVELS[index][_xpRequired]){
            player->level = LEVELS[index][_level];
            player->maxHp += LEVELS[index][_levelBonus];
            player->currentHp = player->maxHp;

            player->xp -= LEVELS[index][_xpRequired];

            printf("You level up ! You are now level %d.\n\n", player->level);
        }
    }

    monster->respawn = RESPAWN_MONSTER;
}

//when the player try to heal with a potion during a combat
void handlePotion(Player *player, InventoryNode *potion){
    int heal = atoi(ITEMS[potion->reference][_info]);

    if(player->currentHp + heal > player->maxHp){
        heal = player->maxHp - player->currentHp;
    }

    player->currentHp += heal;

    printf("\nYou healed %d HP\n", heal);

    removeItem(&player->inventory, potion);
}

//main combat loop : (step 1 -> gear selection) then (step 2 -> a loop (player attack then monster attack) till one die)
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
            InventoryNode *potion = itemSelect(player->inventory, _heal);
            if(potion != NULL){
                handlePotion(player, potion);
            }
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
