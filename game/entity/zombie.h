#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "entity.h"
using namespace std;

class Zombie: public Entity
{
public:
    void Init(int x, int y, int row, int col, int number, int health = -1, int attack = -1, int range = -1);
    void InitRandom(vector<vector<Entity>> e, int row, int col, int number, int health = -1, int attack = -1, int range = -1);
};

#endif