#include <Arduino.h>

#include "temp.h"

#include "DHT.h"

DHT* dht = nullptr;

void setupTemp(int dhtPin) {
  Serial.println(F("DHT11 test!"));
  if (dht == nullptr) {
  dht = new DHT(dhtPin, DHT11);
  }
  dht->begin();
}

void printCurrentTemp() {
  float t = dht->readTemperature();
  Serial.print(F("%  Temperature: "));
  Serial.println(t);
}

float getCurrentTemp() {
  return dht->readTemperature();
}