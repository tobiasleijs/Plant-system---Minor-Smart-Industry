#include <Arduino.h>
#include "lightSensitiveSwitch.h"
#include "switchKaKu.h"

int ldrPin;
int rfPin;
int transmitId;

int lightValue;
int threshold;

void setupLightSensitiveSwitch(int ldrPinNr, int rfPinNr, int lightThreshold, int transmitterId)
{
    ldrPin = ldrPinNr;
    rfPin = rfPinNr;
    threshold = lightThreshold;
    transmitId = transmitterId;
    pinMode(ldrPin, INPUT);
}

int readLightValue()
{
    return analogRead(ldrPin);
}

void checkAndToggleLight()
{
    lightValue = readLightValue();
    if (lightValue <= threshold)
    {
        switchKaku(rfPin, transmitId, 1, 1, true, 3);
        Serial.println("Switched the light on");
    }
    else
    {
        switchKaku(rfPin, transmitId, 1, 1, false, 3);
        Serial.println("Switched the light off");
    }
}
