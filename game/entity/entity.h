#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>
using namespace std;

class Entity
{
private:
    int x, y;
    int row, col;
    int health;
    int attack;
    int range_x, range_y;
    char c;
    string type;
    bool used;

public:
    void Init(string type, int x, int y, int row, int col, char c = ' ');
    void InitRandom(string type, vector<vector<Entity>> e, int row, int col, char c);
    void SetStats(int health, int attack, int range_x = 0, int range_y = 0);
    void move(int x, int y);
    void heal(int heal);
    int getX();
    int getY();
    string getType();
    int getHealth();
    int getAttack();
    int getRow();
    int getCol();
    int getRangeX();
    int getRangeY();
    char getChar();
    void BoostAttack(int boost);
    void damage(int hp);
    vector<int> get_range_target(vector<vector<Entity>> board, string target_type);
    bool range_has_target(vector<vector<Entity>> board, string target_type);
    bool isDead();
    bool isUsed();
    void setUsed();
};

#endif