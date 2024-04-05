#include "had.h"
#include <Arduino.h>
#include <list>
#include <iterator>
#include <random>
#include "heltec.h"
#include <set>
#include <utility> // for std::pair

bool Had::checkBodyCollision()
{
    std::pair<int, int> targetHead;
    targetHead = std::make_pair(body.front().first + direction.first * width, body.front().second + direction.second * width);
    for (const auto &pair : body)
    {
        if (pair == targetHead)
        {
            return true;
        }
    }
    return false;
}

bool Had::checkBorderCollision()
{
    if ((head.first + direction.first * width) < 3 || (head.first + 2 * direction.first * width) > DISPLAY_WIDTH - 3)
    {
        return true;
    }
    if ((head.second + direction.second * width) < 0 || (head.second + 2 * direction.second * width) > DISPLAY_HEIGHT - 1)
    {
        return true;
    }
    return false;
}

void Had::updateHead()
{
    body.pop_back();
    body.push_front(std::make_pair(body.front().first + direction.first * width, body.front().second + direction.second * width));
    head = body.front();
    tail = body.back();
}

void Had::randomDirection()
{
    int random_number = distribution(gen);
    std::pair<int, int> old_dir = direction;
    if (checkBodyCollision() or checkBorderCollision() or random_number == 5)
    {
        if (direction.first == 0)
        {
            direction.second = 0;
            random_number = distribution(gen);
            direction.first = (random_number > 3) ? 1 : -1;
            if (checkBodyCollision() or checkBorderCollision())
            {
                direction.first *= -1;
            }
            if (checkBodyCollision() or checkBorderCollision())
            {
                direction = old_dir;
            }
        }
        else
        {
            direction.first = 0;
            random_number = distribution(gen);
            direction.second = (random_number > 3) ? 1 : -1;
            if (checkBodyCollision() or checkBorderCollision())
            {
                direction.second *= -1;
            }
            if (checkBodyCollision() or checkBorderCollision())
            {
                direction = old_dir;
            }
        }
    }
}

void Had::drawBorders()
{
    Heltec.display->drawLine(3, 0, DISPLAY_WIDTH - 3, 0);
    Heltec.display->drawLine(2, 0, 2, DISPLAY_HEIGHT);
    Heltec.display->drawLine(DISPLAY_WIDTH - 3, DISPLAY_HEIGHT - 1, 3, DISPLAY_HEIGHT - 1);
    Heltec.display->drawLine(DISPLAY_WIDTH - 3, DISPLAY_HEIGHT - 1, DISPLAY_WIDTH - 3, 0);
}

Had::Had(int i) : width(i), gen(rd()), distribution(0, 5)
{
    direction = std::make_pair(-1, 0);
    for (int i = 0; i < 6; ++i)
    {
        body.push_back(std::make_pair(DISPLAY_WIDTH / 2 + i * width, DISPLAY_HEIGHT / 2 - width / 2));
    }
    head = body.front();
    tail = body.back();
};

void Had::changeDirection(int key)
{
    if (key == 121)
    {
        std::set<std::pair<int, int>> possibleDirs = {
            {1, 0},
            {-1, 0}};

        if (possibleDirs.find(direction) != possibleDirs.end())
        {
            direction.first = 0;
            direction.second = -1;
        }
    }
    if (key == 106)
    {
        std::set<std::pair<int, int>> possibleDirs = {
            {0, 1},
            {0, -1}};

        if (possibleDirs.find(direction) != possibleDirs.end())
        {
            direction.first = 1;
            direction.second = 0;
        }
    }
    if (key == 104)
    {
        std::set<std::pair<int, int>> possibleDirs = {
            {1, 0},
            {-1, 0}};

        if (possibleDirs.find(direction) != possibleDirs.end())
        {
            direction.first = 0;
            direction.second = 1;
        }
    }
    if (key == 103)
    {
        std::set<std::pair<int, int>> possibleDirs = {
            {0, 1},
            {0, -1}};

        if (possibleDirs.find(direction) != possibleDirs.end())
        {
            direction.first = -1;
            direction.second = 0;
        }
    }
}

void Had::drawBody()
{
    Heltec.display->clear();
    drawBorders();
    for (const auto &pair : body)
    {
        Heltec.display->drawRect(pair.first, pair.second, width, width);
    }
    Heltec.display->display();
    // randomDirection();
    updateHead();
}