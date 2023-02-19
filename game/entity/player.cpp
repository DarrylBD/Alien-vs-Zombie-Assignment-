#include "../../headers/all_pf_headers.h"
#include "player.h"
#include <iostream>

void Player::Init(int row, int col, int x, int y)
{
    if (x < 0) { x = row / 2; }
    if (y < 0) { y = col / 2; }

    Entity::Init("Alien", x, y, row, col, 'A');
    SetStats(100, 0);
}