#include "../headers/all_pf_headers.h"
#include "settings.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

void Settings::Display(int type)
{
    pf::ClearScreen();
    string game_mode_str[4] = {"Classic", "Limited", "Waves", "Endless"};

    switch (type)
    {
    case 1:
        cout << "-----------------" << endl
             << "  Game Settings  " << endl
             << "-----------------" << endl
             << "0. Game Mode : " << game_mode_str[game_mode] << endl;
        if (game_mode == 2) {
            cout << "1. Waves : " << waves << endl
                 << "-----------------" << endl
                 << "  Board Settings " << endl
                 << "-----------------" << endl
                 << "2. Board Rows : " << rows << endl
                 << "3. Board Columns : " << columns << endl
                 << "-----------------" << endl
                 << "  Turn Settings  " << endl
                 << "-----------------" << endl
                 << "4. Zombie Turn : " << zombie_turn << endl
                 << "5. Player Turn : " << player_turn << endl;
        } else {
            cout << "-----------------" << endl
                 << "  Board Settings " << endl
                 << "-----------------" << endl
                 << "1. Board Rows : " << rows << endl
                 << "2. Board Columns : " << columns << endl
                 << "-----------------" << endl
                 << "  Turn Settings  " << endl
                 << "-----------------" << endl
                 << "3. Zombie Turn : " << zombie_turn << endl
                 << "4. Player Turn : " << player_turn << endl;
            if (game_mode < 2)
            {
                cout << "-----------------" << endl
                     << " Entity Settings " << endl
                     << "-----------------" << endl
                     << "5. Zombie Count : " << zombies << endl;
                if (game_mode == 1)
                {
                    cout << "6. Pod Count : " << pods << endl
                         << "7. Arrow Count : " << arrows << endl
                         << "8. Rock Count : " << rocks << endl
                         << "9. Health Pack Count : " << health_pack << endl;
                }
            }
        }
        cout << endl;
        break;
    case 2:
        cout << "----------------" << endl
             << " Game Mode List " << endl
             << "----------------" << endl
             << "0. " << game_mode_str[0] << " : Kill all zombies on the board." << endl
             << "1. " << game_mode_str[1] << " : It's Classic, but there are limited consumables on the board." << endl
             << "2. " << game_mode_str[2] << " : Classic mode, but number of zombies are randomized and get more difficult every round." << endl
             << "3. " << game_mode_str[3] << " : Endless waves. Survive as many of them as possible." << endl
                                                                                                      << endl;
        break;
    default:
        cout << "-----------------------" << endl
             << " Default Game Settings" << endl
             << "-----------------------" << endl
             << "Game Mode : " << game_mode_str[game_mode] << endl;
        if (game_mode == 2) { cout << "Waves : " << waves << endl; }
        cout << "Board Rows : " << rows << endl
             << "Board Columns : " << columns << endl
             << "Zombie Turn : " << zombie_turn << endl
             << "Player Turn : " << player_turn << endl;

        if (game_mode < 2)
        {
            cout << "Zombie Count : " << zombies << endl;
            if (game_mode == 1)
            {
                cout << "Pod Count : " << pods << endl
                     << "Arrow Count : " << arrows << endl
                     << "Rock Count : " << rocks << endl
                     << "Health Pack Count : " << health_pack << endl;
            }
        }
        cout << endl;
        break;
    }
}

void Settings::ChangeSettings()
{
    while (true)
    {
        int cmd;
        while (true) {
            Display(1);
            cout << "Which setting would you like to edit? (input -1 to use current settings) ==> ";
            cin >> cmd;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(256,'\n');
                cout << "Error: Input is not an Integer" << endl
                                                         << endl;
            } else if (cmd > 9 || (cmd > 5 && game_mode != 1)) {
                cout << "Error: Input is not in range" << endl
                                                       << endl;
            } else {
                break;
            }
            pf::Pause();
        }
        if (cmd < 0) { break; } 
        command_process(cmd);
    }
}

void Settings::command_process(int cmd)
{
    string list_of_settings[] = {"Waves", "Rows", "Columns", "turns for zombies", "turns for player", "Zombies", "Pods", "Arrows", "Rocks", "Health Packs"};

    int new_value = 0;

    if (cmd == 0){
        while (true) {
            Display(2);
            cout << "Pick your Game Mode (-1 if random) ==> ";
            cin >> new_value;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(256,'\n');
                cout << "Error: Input is not an Integer" << endl
                                                        << endl;
            } else if (new_value > 3) {
                cout << "Error: Input is not in range" << endl
                                                       << endl;
            } else {
                break;
            }
            pf::Pause();
        }
    }
    else {
        while (true) {
            int minus = 0;
            if (game_mode == 2) { minus = 1; }
            Display(1);
            cout << "Enter number of " << list_of_settings[cmd - minus] << " (-1 if random) ==> ";
            cin >> new_value;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(256,'\n');
                cout << "Error: Input is not an Integer" << endl
                                                         << endl;
            }
            else if ((cmd == 1 && (new_value >= 0 && new_value < 2)))
            {
                cout << "Error: Input is not in range" << endl
                                                       << endl;
            } else {
                break;
            }
            pf::Pause();
        }
    }

    int random_val = 0;
    if (new_value < 0) {
        if (cmd == 0)
        {
            random_val = 5;
        } else {
            if (game_mode == 2)
            {
                switch (cmd)
                {
                case 1:
                    new_value = RandomWaves();
                    break;
                case 2:
                case 3:
                    new_value = RandomBoard();
                    break;
                case 4:
                case 5:
                case 6:
                    new_value = RandomZombies();
                    break;
                default:
                    new_value = RandomConsumables();
                    break;
                }
            } else {
                switch (cmd)
                {
                case 1:
                case 2:
                    new_value = RandomBoard();
                    break;
                case 3:
                case 4:
                case 5:
                    new_value = RandomZombies();
                    break;
                default:
                    new_value = RandomConsumables();
                    break;
                }
            }
        }
    }

    if (cmd == 0) // Game Mode
    {
        if (game_mode != new_value)
        {
            switch (new_value)
            {
            case 2:
            case 3:
                zombies = RandomZombies();
            case 0:
                pods        = RandomConsumables();
                arrows      = RandomConsumables();
                health_pack = RandomConsumables();
                rocks       = RandomConsumables();
            case 1:
                waves = RandomWaves();
                break;
            }
        }
        game_mode = new_value;
    } else {
        if (game_mode == 2) {
            if (cmd == 1) { waves = new_value; } // Waves
            cmd--;
        }
        switch (cmd)
        {
        case 1: // Rows
            rows = new_value;
            break;
        case 2: // Columns
            columns = new_value;
            break;
        case 3: // Zombie Turns
            zombie_turn = new_value;
            break;
        case 4: // Player Turns
            player_turn = new_value;
            break;
        case 5: // Zombies
            zombies = new_value;
            break;
        case 6: // Pods
            pods = new_value;
            break;
        case 7: // Arrows
            arrows = new_value;
            break;
        case 8: // Rocks
            rocks = new_value;
            break;
        case 9: // Health Packs
            health_pack = new_value;
            break;
        }
    }
}

int Settings::RandomBoard()
{
    return (rand() % 20) + 1;
}

int Settings::RandomWaves()
{
    return (rand() % 2) + 2;
}

int Settings::RandomZombies()
{
    return (rand() % 3) + 1;
}

int Settings::RandomConsumables()
{
    int rand_value;

    if (rows > columns) { rand_value = rows; }
    else { rand_value = columns; }

    return (rand() % rand_value) + 1;
}

void Settings::Init()
{
    game_mode   = 0;
    player_turn = 1;
    zombie_turn = 1;
    rows        = 9;
    columns     = 5;
    waves       = 2;

    zombies = RandomZombies();
    pods        = RandomConsumables();
    arrows      = RandomConsumables();
    health_pack = RandomConsumables();
    rocks       = RandomConsumables();

    while (true)
    {
        Display();

        string choice;

        cout << "Do you wish to change the game settings (y/n)? ==> ";
        cin >> choice;
        choice = pf::LowerCaseConvert(choice);
        if (choice == "y") {
            ChangeSettings();
        } else if (choice == "n") {
            break;
        } else {
            cout << "Error: Invalid Input " << endl
                                            << endl;
            pf::Pause();
        }
    }
}

int Settings::GetRow()
{
    return rows;
}


int Settings::GetCol()
{
    return columns;
}

int Settings::GetZombies()
{
    return zombies;
}

int Settings::GetRocks()
{
    return rocks;
}

int Settings::GetHealthPack()
{
    return health_pack;
}

int Settings::GetArrow()
{
    return arrows;
}

int Settings::GetZombieTurn()
{
    return zombie_turn;
}

int Settings::GetPlayerTurn()
{
    return player_turn;
}

int Settings::GetGameMode()
{
    return game_mode;
}

int Settings::GetWaves()
{
    return waves;
}

int Settings::GetPod()
{
    return pods;
}