#include "header.h"

int main()
{
    srand(time(NULL));

    Levels *levels = malloc(sizeof(Levels)*1);

    initMap(levels, 8,8);

    handleMovement(levels);

    return 0;
}
