#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>
#include "entity/entity.h"
using namespace std;

class Board
{
private:
    vector<vector<char>> map_;
    vector<vector<char>> mapTrail;
    vector<vector<Entity>> mapEntity;
    Entity air;

    int row, col;
    void border();
public:
    void Init(int r, int c);
    void displayBoard();
    void displayStats(Entity e[], int entity_count, int turn);
    void addEntity(Entity e, int x, int y);
    void removeEntity(int x, int y);
    Entity getEntity(int x, int y);
    bool hasEntity(int x, int y);
    // Trails
    void TrailMapSet();
    void TrailAdd(int x, int y, char entityChar = '.');
    vector<vector<int>> GetTrail();
    void displayBoardTrail();
    vector<vector<Entity>> getBoardEntity();
};

#endif