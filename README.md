## Video Demo

https://youtu.be/VUp5lVEKP1A

## Minimum Requirements

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

## Additional Features

- Lowercase correction
- Save File Encryption
- The ability to change settings for other objects
- Consumables can give the player a random amount of HP/ATK
- Rocks have a chance to be empty, or contain a comsumable
- Multiple Game Modes

## Problems Encountered & Solutions

- Making new entities isn't very efficient [made an entity parent class that saves time for making new entities]
- Entity generation can't go more than 4 [Originally made an array that stores all entity x and y coords, replaced it with directly checking the board]
- Random generation isn't very random [replaced srand(time(NULL)) with srand((time_t)ts.tv_nsec) to generate a random seed every nanosecond instead of every second]
