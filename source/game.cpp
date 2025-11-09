#include "game.h"
#include <iostream>
#include <random>
#include <chrono>

static std::mt19937 rng((unsigned)std::chrono::high_resolution_clock::now().time_since_epoch().count());
static int rnd(int a,int b){ return std::uniform_int_distribution<int>(a,b)(rng); }

Game::Game(): player_("You",100), world_(5,5), turn_(0) {}

void Game::intro() {
    std::cout << "==== 2D Survival Game (Console, OOP) ====\n"
              << "Команды: move n/s/e/w, scavenge, rest, inventory, use <n>, status, map, quit\n\n";
}

void Game::status() {
    std::cout << "HP: " << player_.hp() << "/" << player_.maxHp() << "\n"
              << "Hunger: " << player_.hunger() << "\n"
              << "Energy: " << player_.energy() << "\n"
              << "Turn: " << turn_ << "\n";
}

void Game::tick() {
    if (player_.hunger() == 0) {
        std::cout << "Вы умираете от голода! -5 HP\n";
        player_.changeHp(-5);
    }
    if (player_.energy() == 0) {
        std::cout << "Вы обессилены! -1 HP\n";
        player_.changeHp(-1);
    }
}

void Game::encounterAtPosition() {
    auto [x,y] = player_.pos();
    if (!world_.inBounds(x,y)) return;
    int c = world_.cell(x,y);
    if (c==0) return;

    if (c==2) {
        auto item = world_.generateItem();
        std::cout << "Вы нашли предмет: " << item->info() << "\n";
        player_.addItem(std::move(item));
        world_.clearCell(x,y);
        return;
    }

    if (c==1) {
        auto enemy = world_.generateEnemy();
        std::cout << "На вас напал " << enemy->name() 
                  << " (HP " << enemy->hp() << ", DMG " << enemy->damage() << ")\n";
        while (enemy->alive() && player_.alive()) {
            std::cout << "Ваш ход (a)ttack / (r)un: ";
            std::string cmd; std::cin >> cmd;
            if (cmd=="r" || cmd=="run") {
                if (rnd(0,100) < 60) {
                    std::cout << "Вы сбежали!\n";
                    player_.changeEnergy(-10);
                    return;
                } else std::cout << "Не удалось убежать!\n";
            }
            if (cmd=="a" || cmd=="attack") {
                int dmg = rnd(6,14);
                enemy->takeDamage(dmg);
                std::cout << "Вы нанесли " << dmg << " урона.\n";
            }
            if (enemy->alive()) {
                player_.changeHp(-enemy->damage());
                std::cout << enemy->name() << " бьёт вас на " << enemy->damage() << ".\n";
            }
        }
        if (!enemy->alive()) {
            std::cout << "Вы победили!\n";
            if (rnd(0,100)<60) {
                auto loot = world_.generateItem();
                std::cout << "Вы нашли: " << loot->info() << "\n";
                player_.addItem(std::move(loot));
            }
            world_.clearCell(x,y);
        }
    }
}

void Game::run() {
    intro();
    std::string cmd;
    while (player_.alive()) {
        std::cout << "> ";
        if (!(std::cin >> cmd)) break;

        if (cmd=="quit") break;
        else if (cmd=="status") status();
        else if (cmd=="map") world_.printMiniMap(player_);
        else if (cmd=="inventory") player_.listInventory();
        else if (cmd=="use") { int i; std::cin >> i; player_.useItem(i); }
        else if (cmd=="rest") { player_.rest(); std::cout << "Вы отдохнули.\n"; }
        else if (cmd=="scavenge") {
            std::cout << "Вы обыскиваете местность...\n";
            player_.scavenge();
            if (rnd(0,100)<30) {
                auto it = world_.generateItem();
                std::cout << "Найдено: " << it->info() << "\n";
                player_.addItem(std::move(it));
            } else std::cout << "Ничего не найдено.\n";
        }
        else if (cmd=="move") {
            std::string dir; std::cin >> dir;
            int dx=0,dy=0;
            if (dir=="n") dy=-1;
            else if (dir=="s") dy=1;
            else if (dir=="e") dx=1;
            else if (dir=="w") dx=-1;
            else { std::cout << "Используйте n/s/e/w\n"; continue; }
            auto [x,y]=player_.pos();
            if (!world_.inBounds(x+dx,y+dy)) { std::cout << "Нельзя туда!\n"; continue; }
            player_.move(dx,dy);
            encounterAtPosition();
        } else {
            std::cout << "Неизвестная команда.\n";
        }

        ++turn_;
        player_.changeHunger(-1);
        if (rnd(0,100)<8) player_.changeEnergy(-5);
        tick();

        if (!player_.alive()) {
            std::cout << "Вы умерли на " << turn_ << "-м ходу.\n";
            break;
        }
    }
}
