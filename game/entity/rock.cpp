#include "../../headers/all_pf_headers.h"
#include "rock.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

void Rock::Init(int x, int y, int row, int col)
{
    Entity::Init("Rock", x, y, row, col, 'R');
    defineEntity();
}

void Rock::InitRandom(vector<vector<Entity>> e, int row, int col)
{
    Entity::InitRandom("Rock", e, row, col, 'R');
    defineEntity();
}

void Rock::defineEntity()
{
    int block_chance = rand() % 200;
    
    string type = "Air";
    char Char = ' ';

    if (block_chance <= 20) // Health Pack [10%]
    {
        type = "Health Pack";
        Char = 'H';
    } else if (block_chance <= 40) // Health Pack [20%]
    {
        type = "Pod";
        Char = 'P';
    }
    e.Init(type, getX(), getY(), getRow(), getCol(), Char);
}

void Rock::setEntity(string type, char char_)
{
    e.Init(type, getX(), getY(), getRow(), getCol(), char_);
}

Entity Rock::getEntity()
{
    return e;
}