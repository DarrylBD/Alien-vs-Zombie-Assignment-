#ifndef HEALTH_PACK_H
#define HEALTH_PACK_H

#include "entity.h"
using namespace std;

class HealthPack: public Entity
{
private:
    int heal;
public:
    void Init(int x, int y, int row, int col, int heal_ = -1);
    void InitRandom(vector<vector<Entity>> e, int row, int col, int heal_ = -1);
    void SetHeal(int heal_);
    int use_health_pack();
};

#endif