#include <WiFiMulti.h>
#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>
#include "dataController.h"


const char *DEVICE = "ESP_TOBIAS";
const char *DEVICE_LOCATION = "Living Room";

// Wi-Fi and Influx settings
WiFiMulti wifiMulti;

const char *WIFI_SSID = "";
const char *WIFI_PASSWORD = "";
const char *INFLUXDB_URL = "";
const char *INFLUXDB_TOKEN = "";
const char *INFLUXDB_ORG = "";
const char *INFLUXDB_BUCKET = "";
const char *API_KEY = "";

// Set timezone so your data will actually have a correct date and time
const char *TZ_INFO = "CET-1CEST,M3.5.0,M10.5.0/3";

// InfluxDB client instance with preconfigured InfluxCloud certificate
InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);

// Point object called deviceStatus with measurment name "devices"
Point deviceStatus("devices");

Point tempPoint("temperature");
Point moisturePoint("moisture");
Point lightPoint("light");

void setupDataController()
{
    // Setup wifi
    WiFi.mode(WIFI_STA);
    wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Connecting to wifi...");
    while (wifiMulti.run() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(100);
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    // This line sets the options for the Influx client. It means that it will send data in batches of size 1 and it will send the data immediately (flushInterval 0)
    client.setWriteOptions(WriteOptions().batchSize(1).flushInterval(0));

    // Here you can add tags as you please.
    deviceStatus.addTag("device", DEVICE);
    deviceStatus.addTag("location", DEVICE_LOCATION);
    deviceStatus.addTag("SSID", WiFi.SSID());

    // Sync time for proper connection and data points
    timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");

    // Check server connection
    if (client.validateConnection())
    {
        Serial.print("Connected to InfluxDB: ");
        Serial.println(client.getServerUrl());
    }
    else
    {
        Serial.print("InfluxDB connection failed: ");
        Serial.println(client.getLastErrorMessage());
    }
}

void writePoint(Point &point) {
    if (!client.writePoint(point))
    {
        Serial.print("InfluxDB write failed: ");
        Serial.println(client.getLastErrorMessage());
    }
}

template<typename T>
void clearAndWritePoint(Point &point, String fieldName, T value) {
    point.clearFields();
    point.addField(fieldName, value);
    Serial.println("Writing " + fieldName + " to database with value:" + value);
    if (!client.writePoint(point))
    {
        Serial.print("InfluxDB write failed: ");
        Serial.println(client.getLastErrorMessage());
    }
}

void writeTemp(float temp) {
    clearAndWritePoint(tempPoint, "room_temp", temp);
}

void writeMoisture(int moist) {
    clearAndWritePoint(moisturePoint, "soil_moisture", moist);
}

void writeLight(int light) {
    clearAndWritePoint(lightPoint, "light_intensity", light);
}


void checkWifiConnection() {
    // Check Wi-Fi connection and reconnect if needed
    if (wifiMulti.run() != WL_CONNECTED)
    {
        Serial.println("Wifi connection lost");
    }
}