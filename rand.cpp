//
// Created by Lad on 07.05.2020.
//

#include "rand.h"

int Rand(int low, int high)
{
    random_device rd;
    mt19937 R(rd());
    int r = R();
    if(r < 0)
    {
        r = -r;
    }
    return low + r%(high+1);
}
