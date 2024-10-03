#include <Arduino.h>
#include "moistureSensor.h"

int moistSensPin = 36;
int moistValue = 0;

int readMoistureValue() {
  return analogRead(moistSensPin);
}