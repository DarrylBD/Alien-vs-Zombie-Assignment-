#ifndef ROCK_H
#define ROCK_H

#include "entity.h"
#include "player.h"
using namespace std;

class Rock: public Entity
{
private:
    Entity e;
public:
    void Init(int x, int y, int row, int col);
    void InitRandom(vector<vector<Entity>> e, int row, int col);
    void defineEntity();
    void setEntity(string type, char char_);
    Entity getEntity();
};

#endif