#include "Arduino.h"
#include "DoorsE.h"
#include "IndicationsE.h"
#include "DoorsI.h"
#include "SpeedE.h"
#include "CommonDataE.h"

void Doors_Setup()
{
}

void Doors_Loop()
{
    CommonData_Get(CommonData_enInmValues, &Doors__stGetINMValues);
    stDoorsData.boFrontLeftDoor = Doors__stGetINMValues.stSW1;
    stDoorsData.boFrontRightDoor = Doors__stGetINMValues.stSW2;
    stDoorsData.boRearLeftDoor = Doors__stGetINMValues.stSW3;
    stDoorsData.boRearRightDoor = Doors__stGetINMValues.stSW4;
    CommonData_Set(CommonData_enDoorsState, &stDoorsData);
    IND_vSetIndication2();
}

bool Doors_boClosed()
{
    if(!stDoorsData.boFrontLeftDoor && !stDoorsData.boFrontRightDoor && !stDoorsData.boRearLeftDoor && !stDoorsData.boRearRightDoor)
    {
        // Serial.println("All Doors Closed");
        return true;
    }
    else
    {
        // Serial.println("One door is open");
        return false;
    }
}