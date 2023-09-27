#include "Arduino.h"

#ifndef Battery_h
#define Battery_h

static struct Battery_stData
{
    uint8_t u8BatteryLevel;
    uint8_t u8LowBattery;   // when set on 1, flag is triggered
} stBatteryData;

void Battery_Setup();
void Battery_Loop();

#endif