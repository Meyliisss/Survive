#pragma once
#include <string>
#include <memory>
#include <iostream>

class Player; // forward declaration

class Item {
protected:
    std::string name_;
public:
    Item(std::string name="Item") : name_(std::move(name)) {}
    virtual ~Item() = default;
    std::string name() const { return name_; }
    virtual std::string info() const { return name_; }
    virtual bool use(Player &p) { return false; } // true если удаляется после использования
};

class Food : public Item {
    int restoreHunger_;
    int restoreHp_;
public:
    Food(std::string name, int h, int hp=0);
    bool use(Player &p) override;
    std::string info() const override;
};
