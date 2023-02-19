#include "../../headers/all_pf_headers.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "zombie.h"
using namespace std;

void Zombie::Init(int x, int y, int row, int col, int number, int health, int attack, int range)
{
    string string_ = to_string(number);
    char const *char_ = string_.c_str();

    Entity::Init("Zombie", x, y, row, col, char_[0]);

    if (health < 0) { health = 50 * (1 + (rand() % 5)); }
    if (attack < 0) { attack = 5 * (1 + (rand() % 5)); }
    if (range < 0) { range = 1 + (rand() % 5); }
    SetStats(health, attack, range, range);
}

void Zombie::InitRandom(vector<vector<Entity>> e, int row, int col, int number, int health, int attack, int range)
{
    string string_ = to_string(number);
    char const *char_ = string_.c_str();

    Entity::InitRandom("Zombie", e, row, col, char_[0]);

    if (health < 0) { health = 50 * (1 + (rand() % 5)); }
    if (attack < 0) { attack = 5 * (1 + (rand() % 5)); }
    if (range < 0) { range = 1 + (rand() % 5); }
    SetStats(health, attack, range, range);
}