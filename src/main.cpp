#include <Arduino.h>
#include "heltec.h"
#include "had.h"

Had had(4);
int incomingByte = 0; // for incoming serial data

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
        Serial.print("Pressed ");
        Serial.println(incomingByte, DEC);
        had.changeDirection(incomingByte);
    }

    had.drawBody();
    delay(500);
}