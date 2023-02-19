#ifndef ARROW_H
#define ARROW_H

#include "entity.h"
using namespace std;

class Arrow: public Entity
{
private:
    int direction;
    int attack_boost;
public:
    void Init(int x, int y, int row, int col, int boost = -1, int dir = 0);
    void InitRandom(vector<vector<Entity>> e, int row, int col, int boost = -1, int dir = 0);
    void SetAttackBoost(int boost);
    char SetDirection(int dir);
    string ChangeDirection();
    int getATKBoost();
};

#endif