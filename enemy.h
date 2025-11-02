#pragma once
#include <string>
#include <algorithm>

class Enemy {
    std::string name_;
    int hp_, damage_;
public:
    Enemy(std::string name, int hp, int dmg)
        : name_(std::move(name)), hp_(hp), damage_(dmg) {}

    std::string name() const { return name_; }
    int hp() const { return hp_; }
    int damage() const { return damage_; }
    bool alive() const { return hp_ > 0; }
    void takeDamage(int d) { hp_ = std::max(0, hp_ - d); }
};
