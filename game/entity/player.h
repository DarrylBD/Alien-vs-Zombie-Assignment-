#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
using namespace std;

class Player: public Entity
{
public:
    void Init(int row, int col, int x = -1, int y = -1);
};

#endif