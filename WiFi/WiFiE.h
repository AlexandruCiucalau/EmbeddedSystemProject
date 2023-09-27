#ifndef WiFiE_h
#define WiFiE_h

#include "Arduino.h"
#include "ESPAsyncWebServer.h"

static struct WiFi_BoardConfig {
    uint8_t u8TimeFormat;
    uint8_t u8TemperatureUnit;
    uint8_t u8SpeedUnit;
} WiFi_stBoardConfig;

String WiFi_ProcessRelaysButtons(const String &var);

void WiFi_Setup();


#endif