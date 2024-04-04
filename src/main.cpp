#include <Arduino.h>
#include "heltec.h"
#include "had.h"

Had had(4);
int incomingByte = 0; // for incoming serial data
bool released = true;

void setup()
{
    Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);
    Heltec.display->clear();
    Serial.begin(115200);
}

void loop()
{
    // reply only when you receive data:
    if (Serial.available() > 0)
    {
        // read the incoming byte:
        incomingByte = Serial.read();
        if (released && incomingByte == 119)
        {
            released = false;
            Serial.println("Pressed");
        }
        else if (!released && incomingByte == 109)
        {
            released = true;
            Serial.println("Released");
        }
    }
    had.drawBody();
    delay(500);
}