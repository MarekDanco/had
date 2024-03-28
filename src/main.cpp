#include <Arduino.h>
#include "heltec.h"
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

    void checkBodyCollision()
    {
        std::pair<int, int> targetHead;
        targetHead = std::make_pair(body.front().first + direction.first * width, body.front().second + direction.second * width);
        bool found = false;
        for (const auto &pair : body)
        {
            if (pair == targetHead)
            {
                found = true;
                break;
            }
        }
        if (found)
        {
            direction.first *= -1;
            direction.second *= -1;
        }
    }

    void updateHead()
    {
        body.pop_back();

        if ((head.first + direction.first * width) < 1 || (head.first + 2 * direction.first * width) > DISPLAY_WIDTH - 1)
        {
            direction.first = 0;
            direction.second = (head.second - 2 * width < 0) ? 1 : -1;
        }
        if ((head.second + direction.second * width) < 0 || (head.second + 2 * direction.second * width) > DISPLAY_HEIGHT)
        {
            direction.first = (head.first - 2 * width < 0) ? 1 : -1;
            direction.second = 0;
        }

        body.push_front(std::make_pair(body.front().first + direction.first * width, body.front().second + direction.second * width));
        head = body.front();
        tail = body.back();
    }
    void changeDirection()
    {
        int random_number = distribution(gen);
        if (random_number == 9)
        {
            if (direction.first == 0)
            {
                random_number = distribution(gen);
                direction.first = (random_number > 4) ? 1 : -1;
                direction.second = 0;
            }
            else
            {
                direction.first = 0;
                random_number = distribution(gen);
                direction.second = (random_number > 4) ? 1 : -1;
            }
        }
    }
    void drawBorders()
    {
        Heltec.display->drawLine(3, 0, DISPLAY_WIDTH - 3, 0);
        Heltec.display->drawLine(2, 0, 2, DISPLAY_HEIGHT);
        Heltec.display->drawLine(DISPLAY_WIDTH - 3, DISPLAY_HEIGHT - 1, 3, DISPLAY_HEIGHT - 1);
        Heltec.display->drawLine(DISPLAY_WIDTH - 3, DISPLAY_HEIGHT - 1, DISPLAY_WIDTH - 3, 0);
    }

public:
    Had(int i) : width(i), gen(rd()), distribution(0, 9)
    {
        direction = std::make_pair(-1, 0);
        for (int i = 0; i < 6; ++i)
        {
            body.push_back(std::make_pair(DISPLAY_WIDTH / 2 + i * width, DISPLAY_HEIGHT / 2 - width / 2));
        }
        head = body.front();
        tail = body.back();
    };

    void drawBody()
    {
        Heltec.display->clear();
        drawBorders();
        for (const auto &pair : body)
        {
            Heltec.display->drawRect(pair.first, pair.second, width, width);
        }
        Heltec.display->display();
        changeDirection();
        checkBodyCollision();
        updateHead();
    }
};

void setup()
{
    Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);
    Heltec.display->clear();
    Serial.begin(115200);
}

void loop()
{
    Serial.write("Type a number: "); // Type a number and press enter
    auto msg = Serial.readString();
    if (msg)
    {
        Serial.print(msg);
    }
    Serial.write("ping\n");
    // Get user input from the keyboard
    // Serial.write(msg);

    Had had(4);
    while (true)
    {
        had.drawBody();
        delay(400);
    }
}