#include "had.h"
#include <Arduino.h>
#include <list>
#include <iterator>
#include <random>
#include "heltec.h"
#include <set>
#include <utility> // for std::pair
#include <ctime>   // for std::time

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

void Had::drawBorders()
{
    Heltec.display->drawLine(3, 0, DISPLAY_WIDTH - 3, 0);
    Heltec.display->drawLine(2, 0, 2, DISPLAY_HEIGHT);
    Heltec.display->drawLine(DISPLAY_WIDTH - 3, DISPLAY_HEIGHT - 1, 3, DISPLAY_HEIGHT - 1);
    Heltec.display->drawLine(DISPLAY_WIDTH - 3, DISPLAY_HEIGHT - 1, DISPLAY_WIDTH - 3, 0);
}

void Had::GameOver()
{
    int headx = head.first + width / 2;
    int heady = head.second + width / 2;
    for (int16_t i = 3; i < DISPLAY_WIDTH - 3; i += 4)
    {
        Heltec.display->drawLine(headx, heady, i, 0);
        Heltec.display->display();
        delay(30);
    }
    for (int16_t i = 0; i < DISPLAY_HEIGHT - 1; i += 4)
    {
        Heltec.display->drawLine(headx, heady, DISPLAY_WIDTH - 3, i);
        Heltec.display->display();
        delay(30);
    }
    for (int16_t i = 0; i < DISPLAY_WIDTH - 6; i += 4)
    {
        Heltec.display->drawLine(headx, heady, DISPLAY_WIDTH - 3 - i, DISPLAY_HEIGHT - 1);
        Heltec.display->display();
        delay(30);
    }
    for (int16_t i = 0; i < DISPLAY_HEIGHT - 2; i += 4)
    {
        Heltec.display->drawLine(headx, heady, 3, DISPLAY_HEIGHT - 1 - i);
        Heltec.display->display();
        delay(30);
    }
}

Had::Had(int i) : width(i)
{
    direction = std::make_pair(-1, 0);
    for (int i = 0; i < 6; ++i)
    {
        body.push_back(std::make_pair(DISPLAY_WIDTH / 2 + i * width, DISPLAY_HEIGHT / 2 - width / 2));
    }
    head = body.front();
    tail = body.back();
    eaten = false;
    spawnFood();
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

bool Had::spawnedInBody()
{
    for (const auto &pair : body)
    {
        if (pair == food)
        {
            return true;
        }
    }
    return false;
}

bool Had::spawnedOutside()
{
    if (food.first < 3 || food.first + width > DISPLAY_WIDTH - 3)
    {
        return true;
    }
    if (food.second < 1 || food.second + width > DISPLAY_HEIGHT - 1)
    {
        return true;
    }
    return false;
}

void Had::spawnFood()
{
    food.first = DISPLAY_WIDTH / 2 + random(-DISPLAY_WIDTH / width, DISPLAY_WIDTH / width) * width;
    food.second = DISPLAY_HEIGHT / 2 - width / 2 + random(-DISPLAY_HEIGHT / width, DISPLAY_HEIGHT / width) * width;

    while (spawnedInBody() || spawnedOutside())
    {
        food.first = DISPLAY_WIDTH / 2 + random(-DISPLAY_WIDTH / width, DISPLAY_WIDTH / width) * width;
        food.second = DISPLAY_HEIGHT / 2 - width / 2 + random(-DISPLAY_HEIGHT / width, DISPLAY_HEIGHT / width) * width;
    }
}

bool Had::drawBody()
{
    Heltec.display->clear();
    drawBorders();

    Heltec.display->drawRect(food.first, food.second, width, width); // draw food

    for (const auto &pair : body)
    {
        Heltec.display->drawRect(pair.first, pair.second, width, width);
    }
    Heltec.display->display();
    if (checkBodyCollision() || checkBorderCollision())
    {
        GameOver();
        return true;
    }
    updateHead();
    return false;
}