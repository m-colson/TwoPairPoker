#pragma once

#include <stdio.h>
#include <stdlib.h>

int randBetween(int min,int max) {
    return (rand()%(max-min))+min;
}