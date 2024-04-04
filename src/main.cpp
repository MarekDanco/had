#include <Arduino.h>
#include "heltec.h"
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

    bool released = true;
    Had had(4);
    while (true)
    {
        had.drawBody();
        delay(500);

        auto msg = Serial.read();
        if (msg == -1)
        {
            continue;
        }
        Serial.print(msg);
        if (released && msg == 'w')
        {
            released = false;
            Serial.println("Pressed");
        }
        else if (msg == 'm')
        {
            released = true;
            Serial.println("Released");
        }
        // delay(400);
    }
}