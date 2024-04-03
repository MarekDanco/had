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
    Serial.write("ping");

    String msg;

    Had had(4);
    while (true)
    {
        msg = Serial.readString();
        if (msg != "")
        {
            delay(400);
            Serial.print(msg);
        }
        had.drawBody();
        // delay(400);
    }
}