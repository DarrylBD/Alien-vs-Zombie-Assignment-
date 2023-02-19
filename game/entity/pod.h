#ifndef POD_H
#define POD_H

#include "entity.h"
using namespace std;

class Pod: public Entity
{
public:
    void Init(int x, int y, int row, int col, int atk = -1);
    void InitRandom(vector<vector<Entity>> e, int row, int col, int atk = -1);
    int set_attack();
};

#endif