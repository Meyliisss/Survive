#pragma once
#include <string>
#include "player.h"
#include "world.h"
#include "enemy.h"

class Game {
    Player player_;
    World world_;
    int turn_;
public:
    Game();
    void run();
private:
    void intro();
    void status();
    void tick();
    void encounterAtPosition();
};
