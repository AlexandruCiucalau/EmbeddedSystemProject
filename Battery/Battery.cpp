#include "Arduino.h"
#include "BatteryI.h"
#include "BatteryE.h"
#include "IndicationsE.h"
#include "CommonDataE.h"

void Battery_Setup()
{
}

void Battery_Loop()
{
    // replacement of map() function
    uint16_t u16batteryLevel = (analogRead(ADJ1) * BATTERY__PARAM_1 + BATTERY__PARAM_2) / BATTERY__PARAM_3;

    // switch to simplify the solution
    switch (u16batteryLevel)
    {
    case BAT__0:
        stBatteryData.u8BatteryLevel = BATTERY__BARGRAPH_0;
        break;
    case BAT__1:
        stBatteryData.u8BatteryLevel = BATTERY__BARGRAPH_1;
        break;
    case BAT__2:
        stBatteryData.u8BatteryLevel = BATTERY__BARGRAPH_2;
        break;
    case BAT__3:
        stBatteryData.u8BatteryLevel = BATTERY__BARGRAPH_3;
        break;
    case BAT__4:
        stBatteryData.u8BatteryLevel = BATTERY__BARGRAPH_4;
        break;
    }

    // pass data to other modules and listen for low battery indication
    CommonData_Set(CommonData_enShiftBargraphLVL, &stBatteryData);
    IND_vSetLowBatteryIndication();
}