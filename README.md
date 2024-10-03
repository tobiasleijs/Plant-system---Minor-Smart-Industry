# Automatic plant watering system

## Setup this project
To make the software work with your setup, make sure to change the port numbers in plantSystem.cpp to match the ports on your setup.
```cpp
const int LDR_PIN = 39;
const int RF_PIN = 25;
const int DHT_PIN = 32;
const int PUMP_PIN = 33;
```

Change the id of the RF transmitter in plantSystem.cpp to match the one on your KlikAanKlikUit. You can also change the threshold of when the light and pump should turn on to your liking.
```cpp
const int MOISTURE_THRESHOLD = 500;
const int LIGHT_THRESHOLD = 200;
const int TRANSMITTER_ID = 12654;
```


If your pins are correct, also make sure to add your database and wifi parameters to the dataController.cpp

```cpp
const char *WIFI_SSID = "";
const char *WIFI_PASSWORD = "";
const char *INFLUXDB_URL = "";
const char *INFLUXDB_TOKEN = "";
const char *INFLUXDB_ORG = "";
const char *INFLUXDB_BUCKET = "";
const char *API_KEY = "";
```