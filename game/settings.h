#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
using namespace std;

class Settings
{
private:
    int rows;
    int columns;
    int zombies;
    int pods;
    int rocks;
    int arrows;
    int health_pack;
    int player_turn;
    int zombie_turn;
    int game_mode;
    int waves;

    void Display(int type = 0);
    void ChangeSettings();
    void command_process(int cmd);
public:
    void Init();
    int RandomBoard();
    int RandomWaves();
    int RandomZombies();
    int RandomConsumables();
    int GetRow();
    int GetCol();
    int GetZombies();
    int GetRocks();
    int GetHealthPack();
    int GetArrow();
    int GetZombieTurn();
    int GetPlayerTurn();
    int GetGameMode();
    int GetWaves();
    int GetPod();
};

#endif