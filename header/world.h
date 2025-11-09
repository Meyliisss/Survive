#pragma once
#include <vector>
#include <memory>
#include <random>
#include <chrono>
#include <iostream>
#include "enemy.h"
#include "item.h"
#include "player.h"

class World {
    int w_, h_;
    std::vector<std::vector<int>> cells_; // 0 пусто, 1 enemy, 2 item
    mutable std::mt19937 rng_;
public:
    World(int w=5, int h=5);
    bool inBounds(int x,int y) const;
    int cell(int x,int y) const;
    void clearCell(int x,int y);
    std::unique_ptr<Enemy> generateEnemy() const;
    std::unique_ptr<Item> generateItem() const;
    void printMiniMap(const Player &p) const;
};
