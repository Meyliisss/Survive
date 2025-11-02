#include "item.h"
#include "player.h"

Food::Food(std::string name, int h, int hp)
    : Item(std::move(name)), restoreHunger_(h), restoreHp_(hp) {}

bool Food::use(Player &p) {
    p.changeHunger(restoreHunger_);
    if (restoreHp_ != 0) p.changeHp(restoreHp_);
    std::cout << "Вы употребили " << name_ 
              << " (+Hunger " << restoreHunger_ << ", +HP " << restoreHp_ << ")\n";
    return true;
}

std::string Food::info() const {
    return name_ + " (Food: +" + std::to_string(restoreHunger_) +
           " hunger, +" + std::to_string(restoreHp_) + " hp)";
}