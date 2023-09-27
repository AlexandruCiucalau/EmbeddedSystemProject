#include "Arduino.h"
#include "SpeedI.h"
#include "SpeedE.h"
#include "IndicationsE.h"
#include "CommonDataE.h"
#include "EEPROME.h"

void Speed_Setup()
{
    // uncomment to manually change the unit of speed
    // uint8_t unitTest = SPEED_UNIT_KMH;
    // EEPROM_WriteData(enSpeedUnit, &unitTest);
}

void Speed_Loop()
{
    static uint16_t prevValue = 0;
    // read value from potentiometer
    Speed__u16readValue = analogRead(SPEED__ADJ2);
    if (Speed__u16readValue < (prevValue - SPEED__DEADBAND) || Speed__u16readValue > (prevValue + SPEED__DEADBAND)) // deadband to stabilize reading
    {
        prevValue = Speed__u16readValue;
        stSpeedData.u16kmh = map(Speed__u16readValue, SPEED__IN_MIN, SPEED__IN_MAX, SPEED__OUT_MAX, SPEED__OUT_MIN);
        stSpeedData.u16mph = stSpeedData.u16kmh * SPEED__MILES_CONVERSION;
    }

    // decide whether the speed is exceeded or not
    if (((stSpeedData.u16kmh + SPEED_THRESHOLD) > SPEED_TH1) || ((stSpeedData.u16mph + SPEED_THRESHOLD) > SPEED_TH3))
    {
        stSpeedData.boBlink = true;
        CommonData_Set(CommonData_enIndication1, &stSpeedData.boBlink);
    }
    else if (((stSpeedData.u16kmh + SPEED_THRESHOLD) < SPEED_TH1) || ((stSpeedData.u16mph + SPEED_THRESHOLD) < SPEED_TH3))
    {
        stSpeedData.boBlink = false;
        CommonData_Set(CommonData_enIndication1, &stSpeedData.boBlink);
    }
    
    // pass data through common data
    CommonData_Set(CommonData_enSpeedData, &stSpeedData);
}