#include "world.h"

World::World(int w, int h)
    : w_(w), h_(h),
      cells_(h, std::vector<int>(w,0)),
      rng_((unsigned)std::chrono::high_resolution_clock::now().time_since_epoch().count())
{
    std::uniform_int_distribution<int> dist(0,100);
    for (int y=0;y<h_;++y)
        for (int x=0;x<w_;++x) {
            int r = dist(rng_);
            if (r < 12) cells_[y][x] = 1;
            else if (r < 30) cells_[y][x] = 2;
            else cells_[y][x] = 0;
        }
    cells_[h_/2][w_/2] = 0;
}

bool World::inBounds(int x,int y) const {
    return x>=0 && x<w_ && y>=0 && y<h_;
}

int World::cell(int x,int y) const {
    return cells_[y][x];
}

void World::clearCell(int x,int y) {
    cells_[y][x] = 0;
}

std::unique_ptr<Enemy> World::generateEnemy() const {
    std::uniform_int_distribution<int> d(1,3);
    int t = d(rng_);
    if (t==1) return std::make_unique<Enemy>("Wolf", 20, 6);
    if (t==2) return std::make_unique<Enemy>("Boar", 25, 5);
    return std::make_unique<Enemy>("Raider", 30, 8);
}

std::unique_ptr<Item> World::generateItem() const {
    std::uniform_int_distribution<int> d(1,3);
    int t = d(rng_);
    if (t==1) return std::make_unique<Food>("Apple", 20, 0);
    if (t==2) return std::make_unique<Food>("Canned Food", 40, 5);
    return std::make_unique<Food>("Herbs", 15, 10);
}

void World::printMiniMap(const Player &p) const {
    auto [px, py] = p.pos();
    std::cout << "Map:\n";
    for (int y=0;y<h_;++y) {
        for (int x=0;x<w_;++x) {
            if (x==px && y==py) std::cout << 'P';
            else {
                int c = cells_[y][x];
                if (c==0) std::cout << '.';
                else if (c==1) std::cout << 'E';
                else if (c==2) std::cout << 'I';
            }
            std::cout << ' ';
        }
        std::cout << '\n';
    }
}
