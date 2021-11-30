#include "../headers/header.h"

//handling gameloop action (1 -> display character sheet / 2 -> move on the map / 3 -> Save progression
int handleAction(Levels *levels, Player *player, char action){
    int state = _continu;

    if(action == '1'){
        displayCharacter(player);
    }else if(action == '2'){
        state = handleMovement(levels, player);
    }else if(action == '3'){
        save(levels, player);
    }

    return state;
}

// main game loop
void gameLoop(Levels *levels, Player *player){
    char action;
    int state = _continu;
    do{

        printf("\n----------- MENU ----------\n\n");

        printf("1 - Character sheet \n"
               "2 - Move \n"
               "3 - Save \n"
               "4 - Exit \n"
               "\nChoose en option : ");


        fflush(stdin);
        scanf("%c", &action);

        system("cls"); //clear console

        state = handleAction(levels, player, action);

    }while(action != '4' && state != _end);

    freeEverything(levels, player);
}

//handling main menu action (1 -> play game / 2 -> load save / 3 -> quit)
void handleMainMenu(char action){
    if(action == '3'){
        return;
    }

    int state = _allowed;

    Levels *levels = malloc(sizeof(Levels));
    Player *player = malloc(sizeof(Player));

    if(action == '1'){

        initMap(levels, INIT_MAP_ROWS, INIT_MAP_COLUMNS, player);
        initPlayer(player);

    }else if(action == '2'){
        state = loadSave(levels, player);
    }

    //printRessourceList(levels->lv1->ressourceList);
    //printMonsterList(levels->lv1->monsterList);

    if(action == '1' || action == '2'){
        if(state == _allowed){
            gameLoop(levels, player);
        }
    }

}
