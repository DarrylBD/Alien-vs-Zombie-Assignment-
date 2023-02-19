#include "../../headers/all_pf_headers.h"
#include "health_pack.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

void HealthPack::Init(int x, int y, int row, int col, int heal_)
{
    Entity::Init("Health Pack", x, y, row, col, 'H');
    SetHeal(heal_);
}

void HealthPack::InitRandom(vector<vector<Entity>> e, int row, int col, int heal_)
{
    Entity::InitRandom("Health Pack", e, row, col, 'H');
    SetHeal(heal_);
}

void HealthPack::SetHeal(int heal_)
{
    if (heal_ < 0) {
        heal = ((rand() % 5) + 1) * 10;
    } else {
        heal = heal_;
    }
}

int HealthPack::use_health_pack()
{
    return heal;
}