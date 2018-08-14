#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

int roll(int max)
{
    // return a pseudo-random number between 0 and max
    return (rand() % max);
}

