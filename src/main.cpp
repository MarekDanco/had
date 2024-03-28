#include <Arduino.h>
#include "heltec.h"
#include <list>
#include <iterator>
#include <random>
#include "had.h"

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