#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "item.h"

class Player {
    std::string name_;
    int hp_, maxHp_;
    int hunger_, energy_;
    std::pair<int,int> pos_;
    std::vector<std::unique_ptr<Item>> inventory_;
public:
    Player(std::string name="Survivor", int maxHp=100);
    int hp() const { return hp_; }
    int maxHp() const { return maxHp_; }
    int hunger() const { return hunger_; }
    int energy() const { return energy_; }
    std::pair<int,int> pos() const { return pos_; }
    bool alive() const { return hp_ > 0; }

    void move(int dx, int dy);
    void rest();
    void scavenge();

    void changeHp(int delta);
    void changeHunger(int delta);
    void changeEnergy(int delta);

    void addItem(std::unique_ptr<Item> it);
    bool hasItems() const;
    void listInventory() const;
    bool useItem(int idx);
};
