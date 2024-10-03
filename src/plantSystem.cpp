#include <Arduino.h>
#include "temp/temp.h"
#include "moisture_sensor/moistureSensor.h"
#include "data_controller/dataController.h"
#include "light_sensitive_switch/lightSensitiveSwitch.h"
#include "water_pump/waterPump.h"

const int CYCLE_DURATION = 3000;

// Pins
const int LDR_PIN = 39;
const int RF_PIN = 25;
const int DHT_PIN = 32;
const int PUMP_PIN = 33;

// Plant system important vars
const int MOISTURE_THRESHOLD = 500;
const int LIGHT_THRESHOLD = 200;
const int TRANSMITTER_ID = 12654;

void setup()
{
    Serial.begin(9600);
    setupTemp(DHT_PIN);
    setupLightSensitiveSwitch(LDR_PIN, RF_PIN, LIGHT_THRESHOLD, TRANSMITTER_ID);
    setupWaterPump(PUMP_PIN, MOISTURE_THRESHOLD);
    setupDataController();
}

void loop()
{
    // Collect data
    float temperature = getCurrentTemp();
    int moisture = readMoistureValue();
    int light = readLightValue();

    // Provide light and water to the plant
    checkAndToggleLight();
    checkAndTogglePump(moisture);

    // Write data to DB
    writeTemp(temperature);
    writeMoisture(moisture);
    writeLight(light);

    Serial.print("Waiting ");
    Serial.print(CYCLE_DURATION / 1000.0, 2);
    Serial.println(" seconds...\n\n\n");
    delay(CYCLE_DURATION);
}
