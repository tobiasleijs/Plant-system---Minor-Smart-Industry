#ifndef PUMP
#define PUMP

void setupWaterPump(int dhtPin, int moistureThreshold);
void checkAndTogglePump(int moisture);

#endif