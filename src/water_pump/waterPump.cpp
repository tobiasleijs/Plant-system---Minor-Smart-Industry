#include <Arduino.h>
#include "waterPump.h"

int pumpPin;
int moistureThreshold;
bool pumpState = false;

void setupWaterPump(int pumpPinNr, int moistureThreshold)
{
    pumpPin = pumpPinNr;
    pinMode(pumpPin, OUTPUT);
}

void checkAndTogglePump(int moisture)
{
    if (moisture < moistureThreshold)
    {
        if (!pumpState) {
        Serial.println("Start pumping water");
        }
        digitalWrite(pumpPin, HIGH);
        pumpState = true;
    } else {
        if (pumpState) {
        Serial.println("Stop pumping water");
        }
        digitalWrite(pumpPin, LOW);
        pumpState = false;
    }
}