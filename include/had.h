#include <Arduino.h>
#include <list>
#include <iterator>
#include <random>

class Had
{
private:
    std::list<std::pair<int, int>> body;
    std::list<std::pair<int, int>> guts;
    std::pair<int, int> direction;
    std::pair<int, int> head;
    std::pair<int, int> tail;
    std::pair<int, int> food;
    int width;

    bool checkBodyCollision();
    bool checkBorderCollision();
    void updateHead();
    void drawBorders();
    void GameOver();

    bool spawnedInBody();
    bool spawnedOutside();
    void spawnFood();
    void eat();
    bool digest();

public:
    Had(int i);

    void changeDirection(int key);
    bool drawBody();
};