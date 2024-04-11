#include <Arduino.h>
#include <list>
#include <iterator>
#include <random>

class Had
{
private:
    std::list<std::pair<int, int>> body;
    std::pair<int, int> direction;
    std::pair<int, int> head;
    std::pair<int, int> tail;
    std::pair<int, int> food;
    int width;
    bool eaten;

    std::random_device xRd;
    std::mt19937 xGen;
    std::uniform_int_distribution<int> xDistribution;

    std::random_device yRd;
    std::mt19937 yGen;
    std::uniform_int_distribution<int> yDistribution;

    bool checkBodyCollision();
    bool checkBorderCollision();
    void updateHead();
    void drawBorders();
    void GameOver();

    bool spawnedInBody();
    bool spawnedOutside();

public:
    Had(int i);

    void changeDirection(int key);
    void spawnFood();
    bool drawBody();
};