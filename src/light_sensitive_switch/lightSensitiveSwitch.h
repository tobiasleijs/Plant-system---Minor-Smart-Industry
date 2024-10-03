#ifndef LIGHT_SENSITIVE_SWITCH
#define LIGHT_SENSITIVE_SWITCH

void setupLightSensitiveSwitch(int ldrPinNr, int rfPinNr, int lightThreshold, int transmitterId);
void checkAndToggleLight();
int readLightValue();

#endif
