#include "../../headers/all_pf_headers.h"
#include "arrow.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;
    
void Arrow::Init(int x, int y, int row, int col, int boost, int dir)
{
    char char_ = SetDirection(dir);
    Entity::Init("Arrow", x, y, row, col, char_);
    SetAttackBoost(boost);
}

void Arrow::InitRandom(vector<vector<Entity>> e, int row, int col, int boost, int dir)
{
    char char_ = SetDirection(dir);
    Entity::InitRandom("Arrow", e, row, col, char_);
    SetAttackBoost(boost);
}

char Arrow::SetDirection(int dir)
{
    if (dir == 0) { dir = ((rand() % 4) + 1) * 2; }

    direction = dir;

    char char_ = ' ';
    switch (direction)
    {
    case 2: // down
        char_ = 'V';
        break;
    case 4: // left
        char_ = '<';
        break;
    case 6: // right
        char_ = '>';
        break;
    case 8: // up
        char_ = '^';
        break;
    default:
        cout << "Error: Direction " << direction << " doesn't exist" << endl;
        pf::Pause();
    }

    return char_;
}

void Arrow::SetAttackBoost(int boost)
{
    if (boost < 0) {
        attack_boost = ((rand() % 4) + 1) * 10;
    } else {
        attack_boost = boost;
    }
}

string Arrow::ChangeDirection()
{
    string cmd;
    switch (direction)
    {
    case 2: // down
        return "down";
    case 4: // left
        return "left";
    case 6: // right
        return "right";
    case 8: // up
        return "up";
    }
    return cmd;
}

int Arrow::getATKBoost()
{
    return attack_boost;
}