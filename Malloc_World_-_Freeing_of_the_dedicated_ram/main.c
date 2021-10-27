#include "header.h"

int main(int argc, char **argv)
{
    srand(time(NULL));

    Levels levels = initMap(7,7);

    printMap(levels.lv1, levels.rows, levels.columns);

    handleMovement();

    return 0;
}
