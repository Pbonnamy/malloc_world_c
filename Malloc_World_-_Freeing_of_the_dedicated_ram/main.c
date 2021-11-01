#include "header.h"

int main()
{
    srand(time(NULL));

    Levels *levels = malloc(sizeof(Levels)*1);

    initMap(levels, 7,7);

    handleMovement(levels);

    printf("%d", levels->columns);

    return 0;
}
