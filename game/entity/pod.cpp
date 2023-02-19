#include "../../headers/all_pf_headers.h"
#include "pod.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

void Pod::Init(int x, int y, int row, int col, int atk)
{
    if (atk < 0) { atk = set_attack(); }
    SetStats(0, atk, row, col);
    Entity::Init("Pod", x, y, row, col, 'P');
}

void Pod::InitRandom(vector<vector<Entity>> e, int row, int col, int atk)
{
    if (atk < 0) { atk = set_attack(); }
    SetStats(0, atk, row, col);
    Entity::InitRandom("Pod", e, row, col, 'P');
}

int Pod::set_attack()
{
    int ret = 10 * (1 + (rand() % 5));
    return ret;
}