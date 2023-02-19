# Part 2

## Video Demo

Please provide the YouTube link to your [Video Demo](https://youtu.be/VUp5lVEKP1A).

## Minimum Requirements

### Completed

List all the features completed.

1. The ability to change the game settings when booting up
2. Generating a board depending on the size specified
3. Generating player character
4. Player Movement
5. Help Command
6. Strength, Health and other Stats
7. Rock Object Spawn
8. Player Trail
9. Health Pack Spawn and functionality
10. Arrow Spawn and functionality
11. Damage System
12. Zombie Spawn and movement
13. Pods Spawn and functionality
14. Save File

### To Do

List all the features not yet done. Remove this section if there is no incomplete requirements.

N/A

## Additional Features

- Lowercase correction
- Save File Encryption
- The ability to change settings for other objects
- Consumables can give the player a random amount of HP/ATK
- Rocks have a chance to be empty, or contain a comsumable
- Multiple Game Modes

## Contributions

### ############

1. Advanced Game Settings
2. Player Movement
3. Player Trail
4. Player Stats
5. Rocks
6. Health Pack
7. Arrows
8. Zombies
9. Damage System
10. Game Modes
11. Pods
12. Save System and Encryption

### ######

1. Board Generating
2. Demo Recording

## Problems Encountered & Solutions

- Making new entities isn't very efficient [made an entity parent class that saves time for making new entities]
- Entity generation can't go more than 4 [Originally made an array that stores all entity x and y coords, replaced it with directly checking the board]
- Random generation isn't very random [replaced srand(time(NULL)) with srand((time_t)ts.tv_nsec) to generate a random seed every nanosecond instead of every second]