// ********************************************************* 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: #### 
// Names: ############ | ####################
// IDs: ########## | ##########
// Emails: ########## | ##########
// Phones: ########## | ##########
// ********************************************************* 

// TODO: Fill in the missing information above and delete this line.

#include "headers/all_pf_headers.h"
#include "headers/all_game_headers.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>
using namespace std;

Settings settings;
Board board;
Player player;

Rock* rocks;
HealthPack* health_packs;
Zombie* zombies;
Arrow* arrows;
Pod* pods;
Entity* all_attacking_entities;

string cmd;
int Row;
int Col;
int PlayerX;
int PlayerY;
int ZombieTurn;
int PlayerTurn;

int key = 890645358;

int GameMode;
int waves;
int wave_count;

int RockNum;
int ZombieNum;
int ArrowNum;
int PodNum;
int HealthPackNum;
int live_entities;
string filetype = ".sav";

struct timespec ts;

/* Display Board */

void BoardDisplay(int type = 0, int turn = 0)
{
    switch (type)
    {
    case 1:
        board.displayBoardTrail();
        break;
    default:
        board.displayBoard();
    }
    board.displayStats(all_attacking_entities, live_entities, turn);
    cout << endl;
}

void refresh_stats()
{
    all_attacking_entities = new Entity[live_entities];
    int i = 0;
    if (!player.isDead()) {
        all_attacking_entities[0] = player;
        i++;
    }

    for (int j = 0; j < ZombieNum; j++)
    {
        if (!zombies[j].isDead())
        {
            all_attacking_entities[i] = zombies[j];
            i++;
        }
    }
}

void refresh_board(int type = 0, int turn = 0)
{
    refresh_stats();
    pf::ClearScreen();
    BoardDisplay(type, turn);
    if (GameMode > 1) {
        cout << "Wave: " << wave_count;
        if (GameMode == 2) { cout << " / " << waves; }
        cout << endl;
    }
}

void zombie_output(int turn_no, string type, int index, int var = 0)
{
    if (!player.isDead()) { index++; }
    refresh_board(var, index);
    cout << type << " Turn: " << turn_no << "/" << ZombieTurn << endl;
}

/* Define Multiple at once (overwrites old list) */

void define_rocks()
{
    rocks = new Rock[RockNum];
    for (int i = 0; i < RockNum; i++)
    {
        rocks[i].InitRandom(board.getBoardEntity(), Row, Col);
        board.addEntity(rocks[i], rocks[i].getX(), rocks[i].getY());
    }
}

void define_health_packs()
{
    health_packs = new HealthPack[HealthPackNum];
    for (int i = 0; i < HealthPackNum; i++)
    {
        health_packs[i].InitRandom(board.getBoardEntity(), Row, Col);
        board.addEntity(health_packs[i], health_packs[i].getX(), health_packs[i].getY());
    }
}

void define_pod()
{
    pods = new Pod[PodNum];
    for (int i = 0; i < PodNum; i++)
    {
        pods[i].InitRandom(board.getBoardEntity(), Row, Col);
        board.addEntity(pods[i], pods[i].getX(), pods[i].getY());
    }
}

void define_arrows()
{
    arrows = new Arrow[ArrowNum];
    for (int i = 0; i < ArrowNum; i++)
    {
        arrows[i].InitRandom(board.getBoardEntity(), Row, Col);
        board.addEntity(arrows[i], arrows[i].getX(), arrows[i].getY());
    }
}

void define_zombies()
{
    zombies = new Zombie[ZombieNum];
    live_entities = ZombieNum + 1;
    for (int i = 0; i < ZombieNum; i++)
    {
        int health, attack, range;
        
        health = 50 * (wave_count + (rand() % 5));
        attack = 5 * (wave_count + (rand() % 5));
        range = wave_count + (rand() % 5);

        zombies[i].InitRandom(board.getBoardEntity(), Row, Col, i + 1, health, attack, range);
        board.addEntity(zombies[i], zombies[i].getX(), zombies[i].getY());
    }
}

/* Define only one entity in a specific spot */

void define_rock(int x, int y, string entity_type = "")
{
    Rock* r = new Rock[RockNum + 1];
    r[RockNum].Init(x, y, Row, Col);

    if (entity_type != "")
    {
        char char_;
        if (entity_type == "Health Pack") { char_ = 'H'; }
        else if (entity_type == "Pod") { char_ = 'P'; }
        r[RockNum].setEntity(entity_type, char_);
    }
    
    board.addEntity(r[RockNum], x, y);

    for (int i = 0; i < RockNum; i++)
    {
        r[i] = rocks[i];
    }

    rocks = r;
    RockNum++;
}

void define_health_pack(int x, int y, int heal = -1)
{
    HealthPack* h = new HealthPack[HealthPackNum + 1];
    h[HealthPackNum].Init(x, y, Row, Col, heal);
    board.addEntity(h[HealthPackNum], x, y);

    for (int i = 0; i < HealthPackNum; i++)
    {
        h[i] = health_packs[i];
    }

    health_packs = h;
    HealthPackNum++;
}

void define_pod(int x, int y, int atk = -1)
{
    Pod* p = new Pod[PodNum + 1];
    p[PodNum].Init(x, y, Row, Col, atk);
    board.addEntity(p[PodNum], x, y);

    for (int i = 0; i < PodNum; i++)
    {
        p[i] = pods[i];
    }

    pods = p;
    PodNum++;
}

void define_arrow(int x, int y, int boost = -1, int dir = 0)
{
    Arrow* a = new Arrow[ArrowNum + 1];
    a[ArrowNum].Init(x, y, Row, Col, boost, dir);
    board.addEntity(a[ArrowNum], x, y);

    for (int i = 0; i < ArrowNum; i++)
    {
        a[i] = arrows[i];
    }

    arrows = a;
    ArrowNum++;
}

void define_zombie(int x, int y, int number, int hp = -1, int atk = -1, int range = -1)
{
    Zombie* z = new Zombie[ZombieNum + 1];
    z[ZombieNum].Init(x, y, Row, Col, number, hp, atk, range);
    board.addEntity(z[ZombieNum], x, y);

    for (int i = 0; i < ZombieNum; i++)
    {
        z[i] = zombies[i];
    }

    zombies = z;
    ZombieNum++;
    live_entities++;
}

/* Consumable Entities */

void UseHealthPack()
{
    for (int i = 0; i < HealthPackNum; i++)
    {
        if (((health_packs[i].getX() == PlayerX) && (health_packs[i].getY() == PlayerY)) && !health_packs[i].isUsed())
        {
            health_packs[i].setUsed();
            HealthPack h = health_packs[i];
            int hp = h.use_health_pack();
            player.heal(hp);
            break;
        }
    }
}

void UseArrow()
{
    for (int i = 0; i < ArrowNum; i++)
    {
        if (((arrows[i].getX() == PlayerX) && (arrows[i].getY() == PlayerY)) && !arrows[i].isUsed())
        {
            arrows[i].setUsed();
            Arrow a = arrows[i];
            cmd = a.ChangeDirection();
            player.BoostAttack(20);
            break;
        }
    }
}

void UsePod()
{
    bool zombie_on_board = false;
    vector<int> pos;
    pos.resize(2);
    Pod p;
    int ATK;
    for (int i = 0; i < PodNum; i++)
    {
        if (((pods[i].getX() == PlayerX) && (pods[i].getY() == PlayerY)) && !pods[i].isUsed())
        {
            pods[i].setUsed();
            p = pods[i];
            ATK = p.getAttack();
            pos = p.get_range_target(board.getBoardEntity(), "Zombie");
            zombie_on_board = true;
            break;
        }
    }

    if (!zombie_on_board) { return; }

    Zombie z;
    
    for (int i = 0; i < ZombieNum; i++)
    {
        if ((zombies[i].getX() == pos[0] && zombies[i].getY() == pos[1]) && !zombies[i].isDead())
        {
            zombies[i].damage(ATK);
            z = zombies[i];
            break;
        }
    }

    string type = z.getType();
    type += " ";
    type += z.getChar();

    if (z.isDead()) {
        board.TrailAdd(z.getX(), z.getY(), ' ');
        board.removeEntity(z.getX(), z.getY());
        live_entities--;
    }

    refresh_board(1);
    cout << player.getType() << " has found a " << p.getType() << "!" << endl
         << type << " took " << ATK << " damage." << endl;
    if (z.isDead())
    {
        cout << type << " is defeated!" << endl;
    } else 
    {
        cout << type << " is standing at " << z.getHealth() << "."  << endl;
    }
    pf::Pause();
}

void checkRock(Entity e)
{
    Rock r;
    for (int i = 0; i < RockNum; i++)
    {
        if ((rocks[i].getX() == e.getX() && rocks[i].getY() == e.getY()) && !rocks[i].isUsed())
        {
            rocks[i].setUsed();
            r = rocks[i];
            break;
        }
    }
    string type = r.getType();

    int X = r.getX();
    int Y = r.getY();
    
    board.removeEntity(X, Y);
    Entity consumable = r.getEntity();
    board.TrailAdd(PlayerX, PlayerY, player.getChar());
    board.TrailAdd(X, Y, consumable.getChar());
    if (consumable.getType() != "Air") {
        board.addEntity(consumable, X, Y);
    }
    refresh_board(1);
    cout << player.getType() << " stumbles upon a " << type << "." << endl;

    if (consumable.getType() == "Air") {
        cout << "There was nothing underneath..." << endl;
    } else {
        cout << player.getType() << " found a " << consumable.getType() << " underneath!" << endl;
        if (consumable.getType() == "Health Pack") { define_health_pack(X, Y); }
        else if (consumable.getType() == "Pod") { define_pod(X, Y); }
    }
    cout << endl;
    pf::Pause();
}

/* Attacking Entities */

void zombie_attack(int turn_no, int index, string type)
{
    Zombie z = zombies[index];
    string player_type = player.getType();
    int ZombieATK = z.getAttack();


    if (z.range_has_target(board.getBoardEntity(), player_type))
    {
        player.damage(ZombieATK);

        if (z.isDead()) {
            board.TrailAdd(player.getX(), player.getY(), ' ');
            board.removeEntity(player.getX(), player.getY());
            live_entities--;
        }

        zombie_output(turn_no, type, index);
        cout << type << " attacks " << player_type << "!" << endl
             << player_type << " took " << ZombieATK << " damage." << endl;
        if (!player.isDead())
        {
            cout << player_type << " is standing at " << player.getHealth() << "."  << endl;
        }
    } else {
        zombie_output(turn_no, type, index);
        cout << type << " is unable to attack " << player_type << "." << endl
             << player_type << " is too far." << endl;
    }
    
    cout << endl;
    pf::Pause();
}

bool player_attack(Entity e)
{
    board.TrailAdd(PlayerX, PlayerY, player.getChar());
    int PlayerATK   = player.getAttack();
    Zombie z;

    for (int i = 0; i < ZombieNum; i++)
    {
        if ((zombies[i].getX() == e.getX() && zombies[i].getY() == e.getY()) && !zombies[i].isDead())
        {
            zombies[i].damage(PlayerATK);
            z = zombies[i];
            break;
        }
    }
    string type = z.getType();
    type += " ";
    type += z.getChar();

    if (z.isDead()) {
        board.TrailAdd(z.getX(), z.getY(), ' ');
        board.removeEntity(z.getX(), z.getY());
        live_entities--;
    }

    refresh_board(1);

    cout << player.getType() << " attacks " << type << "!" << endl
            << type << " took " << PlayerATK << " damage." << endl;
    if (z.isDead())
    {
        cout << type << " is defeated!" << endl;
    } else 
    {
        cout << type << " is standing at " << z.getHealth() << "."  << endl;
    }
    cout << endl;
    pf::Pause();

    return !z.isDead();
}

/* Entity Check */

void ConsumableCheck(Entity e)
{
    string type = e.getType();
    string article = "a";

    int PlayerATK   = player.getAttack();
    int PlayerHP    = player.getHealth();

    board.TrailAdd(PlayerX, PlayerY, player.getChar());
    if (e.getType() == "Health Pack") { UseHealthPack(); }
    else if (e.getType() == "Arrow") { UseArrow(); article = "an"; }
    else if (e.getType() == "Pod") { UsePod(); return; }
    
    string stat_changed = "";
    int difference = 0;
    
    if (PlayerATK != player.getAttack()) {
        stat_changed = "ATTACK";
        difference = player.getAttack() - PlayerATK;
    } else if (PlayerHP != player.getHealth()) {
        stat_changed = "HP";
        difference = player.getHealth() - PlayerHP;
    }
    
    refresh_board(1);
    cout << player.getType() << " has found " << article << " " << type << "!" << endl;
    cout << type << "'s " << stat_changed << " has increased by " << difference << "." << endl
                                                                                       << endl;
    
    board.removeEntity(PlayerX, PlayerY);
    pf::Pause();
    if (GameMode == 1) { board.TrailMapSet(); }
}

bool BlockCheck(Entity e)
{
    string type = e.getType();
    bool blocked = false;
    
    if (type == "Rock") {
        checkRock(e);
        blocked = true;
    } else if (type == "Zombie") {
        blocked = player_attack(e);
    }
    if (GameMode == 1 && blocked) { board.TrailMapSet(); }
    return blocked;
}

/* Movement */

void ReplaceTrail()
{
    vector<vector<int>> TrailPos = board.GetTrail();
    int size = TrailPos.size();
    int TrailX;
    int TrailY;
    int random;
    for (int i = 0; i < size; i++)
    {
        TrailX = TrailPos[i][0];
        TrailY = TrailPos[i][1];

        random = rand() % 100;
        if (random < 20)
        {
            define_arrow(TrailX, TrailY);
        } else {
            random = rand() % 100;
            if (random < 20)
            {
                define_health_pack(TrailX, TrailY);
            } else {
                random = rand() % 100;
                if (random < 20)
                {
                    define_rock(TrailX, TrailY);
                } else {
                random = rand() % 100;
                if (random < 20)
                {
                    define_pod(TrailX, TrailY);
                }
            }
            }
        }
    }
}

bool move_check(Entity e)
{
    Entity obj;
    int X = e.getX();
    int Y = e.getY();
    int counter = 0;

    if (Y == Col - 1)
    {
        counter++;
    } else {
        obj = board.getEntity(X, Y + 1);
        if (obj.getType() != "Air") {
            counter++;
        }
    }

    if (Y == 0)
    {
        counter++;
    } else {
        obj = board.getEntity(X, Y - 1);
        if (obj.getType() != "Air") {
            counter++;
        }
    }

    if (X == 0)
    {
        counter++;
    } else {
        obj = board.getEntity(X - 1, Y);
        if (obj.getType() != "Air") {
            counter++;
        }
    }

    if (X == Row - 1)
    {
        counter++;
    } else {
        obj = board.getEntity(X + 1, Y);
        if (obj.getType() != "Air") {
            counter++;
        }
    }

    return (counter >= 4);
}

void player_movement()
{
    Entity e;
    int counter = 0;
    int PlayerXTemp = PlayerX;
    int PlayerYTemp = PlayerY;
    bool block_check = false;

    board.removeEntity(PlayerX, PlayerY);
    board.TrailMapSet();
    while (true)
    {
        if (cmd == "down" && PlayerYTemp < Col - 1) 
        {
            PlayerYTemp += 1;
        } else if (cmd == "up" && PlayerYTemp > 0)
        {
            PlayerYTemp -= 1;
        } else if (cmd == "left" && PlayerXTemp > 0)
        {
            PlayerXTemp -= 1;
        } else if (cmd == "right" && PlayerXTemp < Row - 1)
        {
            PlayerXTemp += 1;
        } else
        {
            break;
        }

        e = board.getEntity(PlayerXTemp, PlayerYTemp);
        block_check = BlockCheck(e);
        if (block_check) {
            break;
        } else {
            board.TrailAdd(PlayerX, PlayerY);
            PlayerX = PlayerXTemp;
            PlayerY = PlayerYTemp;
            e = board.getEntity(PlayerX, PlayerY);

            if (e.getType() != "Air") {
                ConsumableCheck(e);
            }
        }
        counter++;
    }
    player.move(PlayerX, PlayerY);
    board.addEntity(player, PlayerX, PlayerY);
    board.TrailAdd(PlayerX, PlayerY, player.getChar());
    if (!block_check)
    {
        refresh_board(1);
        cout << player.getType() << " hit the border" << endl;
        pf::Pause();
    }
    
    if (GameMode != 1) { ReplaceTrail(); }
}

bool zombie_movement(int turn_no, int index, string type)
{
    Entity e;
    string dir;
    int XTemp = zombies[index].getX();
    int YTemp = zombies[index].getY();

    board.TrailMapSet();
    if (move_check(zombies[index]))
    {
        zombie_output(turn_no, type, index, 1);
        cout << type << " is unable to move." << endl
                                              << endl;
        pf::Pause();
        return false;
    }

    board.removeEntity(XTemp, YTemp);
    board.TrailAdd(XTemp, YTemp);
    while (true)
    {
        int X = zombies[index].getX();
        int Y = zombies[index].getY();

        int cmd = (rand() % 4);
        
        switch (cmd)
        {
        case 0: // down
            Y += 1;
            dir = "down";
            break;
        case 1: // up
            Y -= 1;
            dir = "up";
            break;
        case 2: // left
            X -= 1;
            dir = "left";
            break;
        case 3: // right
            X += 1;
            dir = "right";
            break;
        }
        
        if ((Y < Col && Y >= 0) && (X >= 0 && X < Row))
        {
            e = board.getEntity(X, Y);
            if (e.getType() == "Air") {
                zombies[index].move(X, Y);
                board.addEntity(zombies[index], X, Y);
                board.TrailAdd(X, Y, zombies[index].getChar());
                zombie_output(turn_no, type, index, 1);
                cout << type << " has moved 1 space " << dir << endl
                                                             << endl;
                pf::Pause();
                break;
            }
        }
    }
    
    if (GameMode != 1) { ReplaceTrail(); }
    return true;
}

/* Waves */

bool new_wave()
{
    wave_count++;
    if (GameMode != 3 && wave_count > waves) { return true; }
    ZombieNum = settings.RandomZombies();
    define_zombies();
    refresh_board();
    cout << "It looks like more zombies has appeared!" << endl;
    pf::Pause();
    return false;
}

/* Quit */

bool quit()
{
    string ret;
    cout << "Are you sure you want to quit? (y/n) => ";
    cin >> ret;
    ret = pf::LowerCaseConvert(ret);
    if (ret == "y") {
        return true;
    } else if (ret == "n") {
        return false;        
    } else {
        cout << "Error: Invalid Input " << endl
                                        << endl;
        pf::Pause();
    }
    
    return false;
}

/* Help */

void list()
{
    cout << "Commands:" << endl
         << "down  - move down" << endl
         << "up    - move up" << endl
         << "left  - move left" << endl
         << "right - move right" << endl
         << "arrow  - change direction of an arrow" << endl
         << "help  - display user commands" << endl
         << "save  - save the game" << endl
         << "load  - load the game" << endl
         << "quit  - quit the game" << endl
                                    << endl;
    pf::Pause();
}

/* Change Arrow Dir */

void change_arrow_dir()
{
    int x, y, dir, index;
    bool found_arrow = false;
    refresh_board();
    cout << "Direction: " << endl
         << "0: down"     << endl
         << "1: left"     << endl
         << "2: right"    << endl
         << "3: up"       << endl
                          << endl
         << "Enter Row, Column and Direction => ";
    cin >> x >> y >> dir;
    if ((x < 1 || x > Row) || (y < 1 || y > Col)) { cout << "Error: X and Y values are out of range" << endl; pf::Pause(); return; }

    int x2 = x - 1;
    int y2 = y - 1;

    for (int i = 0; i < ArrowNum; i++)
    {
        if (((arrows[i].getX() == x2) && (arrows[i].getY() == y2)) && !arrows[i].isUsed()) { index = 1; found_arrow = true; break; }
    }

    if (!found_arrow) { cout << "Error: No arrow in that position" << endl; pf::Pause(); return; }
    string cmd;

    switch (dir)
    {
    case 0:
        cmd = "down";
        break;
    case 1:
        cmd = "left";
        break;
    case 2:
        cmd = "right";
        break;
    case 3:
        cmd = "up";
        break;
    default:
        cout << "Error: Unknown Direction" << endl;
        pf::Pause();
        return;
    }
    
    board.removeEntity(x2, y2);
    arrows[index].Init(x2, y2, Row, Col, -1, (dir + 1) * 2);
    board.addEntity(arrows[index], x2, y2);
    refresh_board();
    cout << "Changed Arrow is position (" << x << "," << y << ") direction to " << cmd << "." << endl;
    pf::Pause();
}

/* Save & Load */

bool save_exist(string filename)
{
    ifstream save_exist;
    save_exist.open(filename);
    if (save_exist) {
        save_exist.close();
        return true;
    }
    return false;
}

void save()
{
    int index = 0;
    string filename;
    do
    {
        filename = "save/Save";
        filename += to_string(index);
        filename += filetype;
        index++;
    } while (save_exist(filename));

    ofstream SaveFile(filename);
    SaveFile << GameMode << endl
             << Row << endl
             << Col << endl
             << ZombieTurn << endl
             << PlayerTurn << endl
             << wave_count << endl
             << waves << endl
             << player.getX() << endl
             << player.getY() << endl
             << player.getHealth() << endl
             << player.getAttack() << endl
             << "Zombie" << endl;
    
    for (int i = 0; i < ZombieNum; i++)
    {
        if (!zombies[i].isDead())
        {
            Zombie z = zombies[i];
            SaveFile << z.getChar() << endl
                     << z.getX() << endl
                     << z.getY() << endl
                     << z.getHealth() << endl
                     << z.getAttack() << endl
                     << z.getRangeX() << endl
                                       << endl;
        }
    }

    SaveFile << "Arrow" << endl;

    for (int i = 0; i < ArrowNum; i++)
    {
        if (!arrows[i].isUsed())
        {
            Arrow a = arrows[i];
            SaveFile << a.getX() << endl
                     << a.getY() << endl
                     << a.ChangeDirection() << endl
                     << a.getATKBoost() << endl
                                        << endl;
        }
    }
    
    SaveFile << "Pod" << endl;

    for (int i = 0; i < PodNum; i++)
    {
        if (!pods[i].isUsed())
        {
            Pod p = pods[i];
            SaveFile << p.getX() << endl
                     << p.getY() << endl
                     << p.getAttack() << endl
                                      << endl;
        }
    }
    
    SaveFile << "Health Pack" << endl;

    for (int i = 0; i < HealthPackNum; i++)
    {
        if (!health_packs[i].isUsed())
        {
            HealthPack h = health_packs[i];
            SaveFile << h.getX() << endl
                     << h.getY() << endl
                     << h.use_health_pack() << endl
                                            << endl;
        }
    }
    
    SaveFile << "Rock" << endl;

    for (int i = 0; i < RockNum; i++)
    {
        if (!rocks[i].isUsed())
        {
            Rock r = rocks[i];
            SaveFile << r.getX() << endl
                     << r.getY() << endl
                     << r.getEntity().getType() << endl
                                                << endl;
        }
    }
    
    SaveFile << "End" << endl;
    
    SaveFile.close();
    pf::encrypt(filename, key);

    cout << "Save Successful" << endl;
    pf::Pause();
}

void load()
{
    int index = 0;
    string filename;
    do
    {
        filename = "save/Save";
        filename += to_string(index);
        filename += filetype;
        index++;
    } while (save_exist(filename));
    index -= 2;

    if (index > 0)
    {
        cout << "Pick a save file from 0 to " << index << " => ";
        cin >> index;
    } else if (index < 0)
    {
        cout << "Error: No save file detected." << endl;
        pf::Pause();
        return;
    }
    
    filename = "save/Save";
    filename += to_string(index);
    filename += filetype;
    int current_line = 0;
    int counter = 0;
    ifstream SaveFile = pf::decrypt(filename, key);
    string line_str;
    
    int PlayerHP, PlayerATK;
    while (getline(SaveFile, line_str))
    {
        current_line++;
        if (line_str == "Zombie") { break; }
        int value = stoi(line_str);
        switch (current_line)
        {
        case 1:
            GameMode = value;
            break;
        case 2:
            Row = value;
            break;
        case 3:
            Col = value;
            break;
        case 4:
            ZombieTurn = value;
            break;
        case 5:
            PlayerTurn = value;
            break;
        case 6:
            wave_count = value;
            break;
        case 7:
            waves = value;
            break;
        case 8:
            PlayerX = value;
            break;
        case 9:
            PlayerY = value;
            break;
        case 10:
            PlayerHP = value;
            break;
        case 11:
            PlayerATK = value;
            break;
        }
    }

    board.Init(Row, Col);
    player.Init(Row, Col, PlayerX, PlayerY);
    player.SetStats(PlayerHP, PlayerATK);
    board.addEntity(player, PlayerX, PlayerY);
    current_line = 0;

    int ZombNum, ZombX, ZombY, ZombHP, ZombATK, ZombRange;
    ZombieNum = 0;
    live_entities = 1;
    zombies = new Zombie[ZombieNum];
    while (getline(SaveFile, line_str))
    {
        current_line++;
        if (line_str == "Arrow") { break; }
        if (current_line == 7) {
            define_zombie(ZombX, ZombY, ZombNum, ZombHP, ZombATK, ZombRange);
            current_line = 0;
            continue;
        }
        int value = stoi(line_str);
        switch (current_line)
        {
        case 1:
            ZombNum = value;
            break;
        case 2:
            ZombX = value;
            break;
        case 3:
            ZombY = value;
            break;
        case 4:
            ZombHP = value;
            break;
        case 5:
            ZombATK = value;
            break;
        case 6:
            ZombRange = value;
            break;
        }
    }

    int ArrowX, ArrowY, ArrowBoost, dir;
    ArrowNum = 0;
    current_line = 0;
    arrows = new Arrow[ArrowNum];
    while (getline(SaveFile, line_str))
    {
        current_line++;
        if (line_str == "Pod") { break; }
        if (current_line == 3) {
            if (line_str == "down") {
                dir = 2;
            }
            else if (line_str == "left") {
                dir = 4;
            }
            else if (line_str == "right") {
                dir = 6;
            }
            else if (line_str == "up") {
                dir = 8;
            }
            continue;
        }
        if (current_line == 5) {
            define_arrow(ArrowX, ArrowY, ArrowBoost, dir);
            current_line = 0;
            continue;
        }
        int value = stoi(line_str);
        switch (current_line)
        {
        case 1:
            ArrowX = value;
            break;
        case 2:
            ArrowY = value;
            break;
        case 4:
            ArrowBoost = value;
            break;
        }
    }

    int PodX, PodY, PodATK;
    PodNum = 0;
    current_line = 0;
    pods = new Pod[PodNum];
    while (getline(SaveFile, line_str))
    {
        current_line++;
        if (line_str == "Health Pack") { break; }
        if (current_line == 4) {
            define_pod(PodX, PodY, PodATK);
            current_line = 0;
            continue;
        }
        int value = stoi(line_str);
        switch (current_line)
        {
        case 1:
            PodX = value;
            break;
        case 2:
            PodY = value;
            break;
        case 3:
            PodATK = value;
            break;
        }
    }
    
    int HealthPX, HealthPY, HealthPHeal;
    HealthPackNum = 0;
    current_line = 0;
    health_packs = new HealthPack[PodNum];
    while (getline(SaveFile, line_str))
    {
        current_line++;
        if (line_str == "Rock") { break; }
        if (current_line == 4) {
            define_health_pack(HealthPX, HealthPY, HealthPHeal);
            current_line = 0;
            continue;
        }
        int value = stoi(line_str);
        switch (current_line)
        {
        case 1:
            HealthPX = value;
            break;
        case 2:
            HealthPY = value;
            break;
        case 3:
            HealthPHeal = value;
            break;
        }
    }

    int RockX, RockY;
    string RockEnt;
    RockNum = 0;
    current_line = 0;
    rocks = new Rock[RockNum];
    while (getline(SaveFile, line_str))
    {
        current_line++;
        if (line_str == "End") { break; }
        if (current_line == 3) {
            RockEnt = line_str;
            continue;
        }
        if (current_line == 4) {
            define_rock(RockX, RockY, RockEnt);
            current_line = 0;
            continue;
        }
        int value = stoi(line_str);
        switch (current_line)
        {
        case 1:
            RockX = value;
            break;
        case 2:
            RockY = value;
            break;
        }
    }

    refresh_board();
    cout << "Save Data has been loaded!" << endl;
    pf::Pause();
}

/* Main */

int main()
{
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);

    settings.Init();

    Row = settings.GetRow();
    Col = settings.GetCol();

    board.Init(Row, Col);
    
    GameMode = settings.GetGameMode();
    waves = settings.GetWaves();
    wave_count = 1;
    
    player.Init(Row, Col);

    PlayerX = player.getX();
    PlayerY = player.getY();

    ZombieTurn = settings.GetZombieTurn();
    PlayerTurn = settings.GetPlayerTurn();

    ZombieNum = settings.GetZombies();
    RockNum = settings.GetRocks();
    HealthPackNum = settings.GetHealthPack();
    ArrowNum = settings.GetArrow();
    PodNum = settings.GetPod();
    
    board.addEntity(player, PlayerX, PlayerY);
    define_rocks();
    define_health_packs();
    define_zombies();
    define_arrows();
    define_pod();
    
    bool GameEnd = false;

    while (!GameEnd)
    {
        for (int turn_no = 1; turn_no <= PlayerTurn;)
        {
            refresh_board();
            cin.clear();
            string movement_commands[4] = {"up", "down", "left", "right"};
            cout << "Player Turn: " << turn_no << "/" << PlayerTurn << endl
                 << "Command => ";
            cin >> cmd;
            cmd = pf::LowerCaseConvert(cmd);
            if (pf::search_array_string(movement_commands, 4, cmd))
            {
                player_movement();
                turn_no++;
            } else if (cmd == "save") {
                save();
                continue;
            } else if (cmd == "load")
            {
                load();
                continue;
            } else if (cmd == "help") {
                list();
                continue;
            } else if (cmd == "arrow") {
                change_arrow_dir();
                continue;
            } else if (cmd == "quit") {
                if (quit()) {
                    GameEnd = true;
                    cout << "Player has quit the game." << endl;
                    break;
                }
            } else {
                cout << "Invalid command" << endl;
                pf::Pause();
            }

            if (live_entities <= 1) {
                GameEnd = true;
                break;
            }
        }
        
        if (GameEnd && GameMode > 1) { GameEnd = new_wave(); continue; }
        
        if (!GameEnd)
        {
            for (int i = 0; i < ZombieNum; i++)
            {
                if (zombies[i].isDead()) { continue; }

                string type = zombies[i].getType();
                type += " ";
                type += zombies[i].getChar();

                for (int turn_no = 1; turn_no <= ZombieTurn; turn_no++)
                {
                    bool movable = zombie_movement(turn_no, i, type);
                    if (GameMode != 1 && movable)
                    {
                        zombie_attack(turn_no, i, type);
                    }
                }

                if (player.isDead()) {
                    GameEnd = true;
                    break;
                }
            }
        }
    }
    
    refresh_board();
    if (player.isDead()) {    
        cout << player.getType() << " is defeated!" << endl;
        if (GameMode == 3 && wave_count > 1) { cout << "Player managed to survive " << wave_count - 1 << " waves!" << endl; }
        else { cout << "Player Lose." << endl; }
    } else {
        cout << "There are no more zombies on the board." << endl
             << "Player Win!" << endl;
    }
}