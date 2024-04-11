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