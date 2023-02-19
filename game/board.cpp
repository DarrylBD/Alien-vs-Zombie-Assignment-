#include "../headers/all_pf_headers.h"
#include "board.h"
#include <iostream>

void Board::Init(int r, int c)
{
    row = r;
    col = c;

    // create dynamic 2D array using vector
    // create empty rows
    map_.resize(col);
    mapEntity.resize(col);
    for (int y = 0; y < col; ++y)
    {
        // resize each row
        map_[y].resize(row);
        mapEntity[y].resize(row);

        // put air into the vector array
        for (int x = 0; x < row; ++x)
        {
            air.Init("Air", x, y, row, col);
            map_[y][x] = ' ';
            mapEntity[y][x] = air;
        }
    }
}


void Board::border() // display border of the row
{
    cout << "  ";
    
    for (int x = 0; x < row; ++x)
    {
        cout << "+-";
    }
    cout << "+" << endl;
}

void Board::displayBoard()
{
    cout << ".: Alien vs Zombie :." << endl;
    // for each row
    for (int y = 0; y < col; ++y)
    {
        border();

        // display row number
        cout << (y + 1) % 10 << " ";

        // display cell content and border of each column
        for (int x = 0; x < row; ++x)
        {
            cout << "|" << map_[y][x];
        }
        cout << "|" << endl;
    }
    
    border();

    // display column number
    cout << "  ";
    
    for (int j = 0; j < row; ++j)
    {
        cout << " " << (j + 1) % 10;
    }
    cout << endl
         << endl;
}

void Board::displayStats(Entity e[], int entity_count, int turn)
{
    for (int i = 0; i < entity_count; ++i)
    {
        string type     = e[i].getType();
        char board_char = e[i].getChar();
        int health      = e[i].getHealth();
        int attack      = e[i].getAttack();
        int range       = e[i].getRangeX();
        
        if (i == turn) { cout << "-> "; }
        else { cout << "   "; }

        if (i > 0) { 
            type += " ";
            type += board_char;
        }

        cout << type;

        for (int i = 0; i < 12 - type.size(); i++)
        {
            cout << " ";
        }

        cout << "HP: ";

        if (health < 100)
        {
            cout << " ";
        } else if (health < 10)
        {
            cout << "  ";
        }

        cout << health << ", ATK: ";

        if (attack < 100)
        {
            cout << " ";
        } else if (attack < 10)
        {
            cout << "  ";
        }

        cout << attack;
        
        if (range > 0) { cout << ", RANGE:  " << range; }
        cout << endl;
    }
}

void Board::addEntity(Entity e, int x, int y)
{
    map_[y][x] = e.getChar();
    mapEntity[y][x] = e;
}

void Board::removeEntity(int x, int y)
{
    air.Init("Air", x, y, row, col);
    map_[y][x] = ' ';
    mapEntity[y][x] = air;
}

Entity Board::getEntity(int x, int y)
{
    return mapEntity[y][x];
}

bool Board::hasEntity(int x, int y)
{
    Entity e = mapEntity[y][x];
    if (e.getType() == "Air")
    {
        return false;
    } else
    {
        return true;
    }
}

void Board::TrailMapSet()
{
    mapTrail = map_;
}

void Board::TrailAdd(int x, int y, char entityChar)
{
    mapTrail[y][x] = entityChar;
}

vector<vector<int>> Board::GetTrail()
{
    vector<vector<int>> TrailPos;
    
    for (int y = 0; y < col; ++y)
    {
        for (int x = 0; x < row; ++x)
        {
            if (mapTrail[y][x] == '.')
            {
                int size = TrailPos.size();
                TrailPos.resize(size + 1);
                TrailPos[size].resize(2);

                TrailPos[size][0] = x;
                TrailPos[size][1] = y;
            }
        }
    }

    return TrailPos;
}

void Board::displayBoardTrail()
{
    cout << ".: Alien vs Zombie :." << endl;
    // for each row
    for (int y = 0; y < col; ++y)
    {
        border();

        // display row number
        cout << (y + 1) % 10 << " ";

        // display cell content and border of each column
        for (int x = 0; x < row; ++x)
        {
            cout << "|" << mapTrail[y][x];
        }
        cout << "|" << endl;
    }
    
    border();

    // display column number
    cout << "  ";
    
    for (int j = 0; j < row; ++j)
    {
        cout << " " << (j + 1) % 10;
    }
    cout << endl
         << endl;
}

vector<vector<Entity>> Board::getBoardEntity()
{
    return mapEntity;
}