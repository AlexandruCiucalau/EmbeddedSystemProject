#include <Arduino.h>
#include "GearBoxE.h"
#include "GearBoxI.h"
#include "CommonDataE.h"
#include "INME.h"
#include "SpeedE.h"

void GB__vChooseGear()
{
    static bool GB_bShouldChangeGear = true;
    INM_stInputs IND_stINMValues;
    Speed_stData GB_stSpeed;
    CommonData_Get(CommonData_enInmValues, &IND_stINMValues);
    CommonData_Get(CommonData_enSpeedData, &GB_stSpeed);
    static uint8_t GB_u8OldCounter = 20;
    static bool GB__u8oldState = false;
    if (IND_stINMValues.stKEY4!=GB__u8oldState && GB_stSpeed.u16kmh == 0)
    {
        GB_Counter++;
        GB_bShouldChangeGear = false;
        GB__u8oldState = IND_stINMValues.stKEY4;
    }else if(GB_stSpeed.u16kmh > 0)
    {
        GB_Counter = DRIVING;        //Set the driving mode to Drive 
    }else if(GB_stSpeed.u16kmh == 0 && GB_bShouldChangeGear)
    {
        GB_Counter = NEUTRAL;       //Set the driving mode to NEUTRAL when the car is not moving and just started
    }
    else if (GB_stSpeed.u16kmh > 0)
    {
        GB_Counter = DRIVING; // Set the driving mode to Drive
    }
    else if (GB_stSpeed.u16kmh == 0 && GB_bShouldChangeGear)
    {
        GB_Counter = NEUTRAL; // Set the driving mode to NEUTRAL when the car is not moving and just started
    }

    if (GB_Counter >= 10)
    {
        GB_Counter = PARKING;
    }
    if (GB_Counter >= 1 && GB_Counter < 3)
    {
        GearBoxStruct.drive = false;
        GearBoxStruct.parking = true;
        GearBoxStruct.reverse = false;
        GearBoxStruct.neutral = false;
    }
    else if (GB_Counter >= 3 && GB_Counter < 5)
    {
        GearBoxStruct.drive = false;
        GearBoxStruct.parking = false;
        GearBoxStruct.reverse = true;
        GearBoxStruct.neutral = false;
    }
    else if (GB_Counter >= 5 && GB_Counter < 7)
    {
        GearBoxStruct.drive = false;
        GearBoxStruct.parking = false;
        GearBoxStruct.reverse = false;
        GearBoxStruct.neutral = true;
    }
    else if (GB_Counter >= 7 && GB_Counter < 9)
    {
        GearBoxStruct.drive = true;
        GearBoxStruct.parking = false;
        GearBoxStruct.reverse = false;
        GearBoxStruct.neutral = false;
    }
    if (GB_Counter != GB_u8OldCounter)
    {
        GB_u8OldCounter = GB_Counter;
        CommonData_Set(CommonData_enGearBox, &GearBoxStruct);
    }
}
void GB__vSetup()
{
    GearBoxStruct.neutral = true;
    GearBoxStruct.drive = false;
    GearBoxStruct.parking = false;
    GearBoxStruct.reverse = false;
    CommonData_Set(CommonData_enGearBox, &GearBoxStruct);
}