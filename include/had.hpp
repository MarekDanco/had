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
    int width;

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<int> distribution;

    void checkBodyCollision();
    void updateHead();
    void changeDirection();
    void drawBorders();

public:
    Had(int i);

    void drawBody();
};