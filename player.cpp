#include "player.h"

Player::Player(std::string name, int maxHp)
    : name_(std::move(name)), hp_(maxHp), maxHp_(maxHp),
      hunger_(80), energy_(80), pos_{2,2} {}

void Player::move(int dx, int dy) {
    pos_.first += dx;
    pos_.second += dy;
    energy_ = std::max(0, energy_ - 5);
    hunger_ = std::max(0, hunger_ - 3);
}

void Player::rest() {
    energy_ = std::min(100, energy_ + 20);
    hunger_ = std::max(0, hunger_ - 5);
}

void Player::scavenge() {
    energy_ = std::max(0, energy_ - 8);
    hunger_ = std::max(0, hunger_ - 4);
}

void Player::changeHp(int delta) {
    hp_ = std::max(0, std::min(maxHp_, hp_ + delta));
}

void Player::changeHunger(int delta) {
    hunger_ = std::max(0, std::min(100, hunger_ + delta));
}

void Player::changeEnergy(int delta) {
    energy_ = std::max(0, std::min(100, energy_ + delta));
}

void Player::addItem(std::unique_ptr<Item> it) {
    inventory_.push_back(std::move(it));
}

bool Player::hasItems() const { return !inventory_.empty(); }

void Player::listInventory() const {
    if (inventory_.empty()) {
        std::cout << "(Инвентарь пуст)\n";
        return;
    }
    for (size_t i=0;i<inventory_.size();++i) {
        std::cout << i+1 << ") " << inventory_[i]->info() << "\n";
    }
}

bool Player::useItem(int idx) {
    if (idx<1 || idx>(int)inventory_.size()) return false;
    if (inventory_[idx-1]->use(*this)) {
        inventory_.erase(inventory_.begin() + (idx-1));
        return true;
    }
    return false;
}
