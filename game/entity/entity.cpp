#include "../../headers/all_pf_headers.h"
#include "entity.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Entity::Init(string type, int x, int y, int row, int col, char c)
{
    this->type = type;
    move(x, y);

    this->row = row;
    this->col = col;
    this->c = c;
    used = false;
}

void Entity::InitRandom(string type, vector<vector<Entity>> e, int row, int col, char c)
{
    int x = rand() % row;
    int y = rand() % col;
    
    while (e[y][x].getType() != "Air")
    {
        x = rand() % row;
        y = rand() % col;
    }
    Entity::Init(type, x, y, row, col, c);
}

void Entity::SetStats(int health, int attack, int range_x, int range_y)
{
    this->health = health;
    this->attack = attack;
    this->range_x = range_x;
    this->range_y = range_y;
}

void Entity::move(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Entity::heal(int heal)
{
    health += heal;
}

int Entity::getX()
{
    return x;
}

int Entity::getY()
{
    return y;
}

string Entity::getType()
{
    return type;
}

int Entity::getHealth()
{
    return health;
}

int Entity::getAttack()
{
    return attack;
}

int Entity::getRow()
{
    return row;
}

int Entity::getCol()
{
    return col;
}

int Entity::getRangeX()
{
    return range_x;
}

int Entity::getRangeY()
{
    return range_y;
}

char Entity::getChar()
{
    return c;
}

void Entity::BoostAttack(int boost)
{
    attack += boost;
}

void Entity::damage(int hp)
{
    health -= hp;
}

vector<int> Entity::get_range_target(vector<vector<Entity>> board, string target_type)
{
    int size = 0;
    int index = 0;
    int longest_distance = 0;

    vector<vector<int>> pos;
    
    int y_ = y - range_y;
    while (y_ <= (y + range_y))
    {
        if (y_ >= 0 && y_ < col)
        {
            int x_ = x - range_x;
        
            while (x_ <= (x + range_x))
            {
                if (x_ >= 0 && x_ < row)
                {
                    if (board[y_][x_].getType() == target_type)
                    {
                        size++;
                        pos.resize(size);
                        pos[size - 1].resize(2);

                        pos[size - 1][0] = x_;
                        pos[size - 1][1] = y_;
                    }
                }
                x_++;
            }
        }
        y_++;
    }

    if (size > 1)
    {
        for (int i = 0; i < size; i++)
        {
            int distance = pos[i][0] + pos[i][1];
            if (longest_distance < distance)
            {
                longest_distance = distance;
                index = i;
            }
        }
    }
    
    return pos[index];
}

bool Entity::range_has_target(vector<vector<Entity>> board, string target_type)
{
    int y_ = y - range_y;
    while (y_ <= (y + range_y))
    {
        if (y_ >= 0 && y_ < col)
        {
            int x_ = x - range_x;
        
            while (x_ <= (x + range_x))
            {
                if (x_ >= 0 && x_ < row)
                {
                    if (board[y_][x_].getType() == target_type)
                    {
                        return true;
                    }
                }
                x_++;
            }
        }
        y_++;
    }

    return false;
}


bool Entity::isDead()
{
    if (health <= 0)
    {
        return true;
    }
    return false;
}

bool Entity::isUsed()
{
    return used;
}

void Entity::setUsed()
{
    used = true;
}