#include "Arduino.h"
#include "IndicationsE.h"
#include "CommonDataE.h"
#include "RELAYE.h"
#include "IndicationsI.h"
#include "DoorsE.h"
#include "SpeedE.h"
#include "INME.h"
#include "LightsE.h"
#include "ShiftE.h"
void IND_vSetup()
{
    bool IND__bTurnOffIndications = 0;
    CommonData_Set(CommonData_enLowBeam, &IND__bTurnOffIndications);
    CommonData_Set(CommonData_enHighBeam, &IND__bTurnOffIndications);
    CommonData_Set(CommonData_enFogLights, &IND__bTurnOffIndications);
    CommonData_Set(CommonData_enLowBattery, &IND__bTurnOffIndications);
    CommonData_Set(CommonData_enIndication1, &IND__bTurnOffIndications);
    CommonData_Set(CommonData_enIndication2, &IND__bTurnOffIndications);
    CommonData_Set(CommonData_enIndication3, &IND__bTurnOffIndications);
}
void IND_vSetLowBeamIndication()
{
    // CommonData_Get(CommonData_enRelayData, &stCopyRelay);
    CommonData_Get(CommonData_enLightsData, &stCopyLights);
    Indications IND__iLowBeam;
    static Indications IND__iExLowBeam = enfalse;
    if (stCopyLights.u8LowBeam)
    {
        IND__iLowBeam = entrue;
    }
    else
    {
        IND__iLowBeam = enfalse;
    }
    if (IND__iLowBeam != IND__iExLowBeam)
    {
        IND__iExLowBeam = IND__iLowBeam;
        CommonData_Set(CommonData_enLowBeam, &IND__iLowBeam);
    }
}
void IND_vSetHighBeamIndication()
{
    // CommonData_Get(CommonData_enRelayData, &stCopyRelay);
    CommonData_Get(CommonData_enLightsData, &stCopyLights);
    Indications IND__iHighBeam;
    static Indications IND__iExHighBeam = enfalse;
    if (stCopyLights.u8HighBeam)
    {
        IND__iHighBeam = entrue;
    }
    else
    {
        IND__iHighBeam = enfalse;
    }
    if (IND__iHighBeam != IND__iExHighBeam)
    {
        IND__iExHighBeam = IND__iHighBeam;
        CommonData_Set(CommonData_enHighBeam, &IND__iHighBeam);
    }
}

void IND_vSetFogLightsIndication()
{
    // de la nagy
    CommonData_Get(CommonData_enLightsData, &stCopyLights);
    static Indications IND__iExFogLights = enfalse;
    Indications IND__iFogLights;
    if (stCopyLights.u8FogLights)
    {
        IND__iFogLights = entrue;
    }
    else
    {
        IND__iFogLights = enfalse;
    }
    if (stCopyLights.u8FogLights != IND__iExFogLights)
    {

        IND__iExFogLights = IND__iFogLights;
        CommonData_Set(CommonData_enFogLights, &IND__iFogLights);
    }
}

void IND_vSetLowBatteryIndication()
{
    uint8_t IND__u8BargraphLevel;
    CommonData_Get(CommonData_enShiftBargraphLVL, &IND__u8BargraphLevel);
    Indications IND__iLowBattery;
    static Indications IND__iExLowBattery = enfalse;
    if (IND__u8BargraphLevel == 0)
    {
        IND__iLowBattery = entrue;
    }
    else
    {
        IND__iLowBattery = enfalse;
    }
    if (IND__iLowBattery != IND__iExLowBattery)
    {
        IND__iExLowBattery = IND__iLowBattery;
        CommonData_Set(CommonData_enLowBattery, &IND__iLowBattery);
    }
}
void IND_vSetIndication1()
{
    Speed_stData IND__stGetSpeedData;
    CommonData_Get(CommonData_enSpeedData, &IND__stGetSpeedData);
    Indications IND__iHighSpeed;
    static Indications IND__iExHighSpeed = enfalse;
    if (IND__stGetSpeedData.boBlink)
    {
        IND__iHighSpeed = entrue;
    }
    else
    {
        IND__iHighSpeed = enfalse;
    }
    if (IND__iHighSpeed != IND__iExHighSpeed)
    {
        IND__iExHighSpeed = IND__iHighSpeed;
        CommonData_Set(CommonData_enIndication1, &IND__iHighSpeed);
    }
}
void IND_vSetIndication2()
{
    Doors_stData IND__stGetDoorsData;
    Speed_stData IND__stGetSpeedDataDoors;
    Indications IND__iDoorOpen;
    static Indications IND__iExDoorOpen = enfalse;
    CommonData_Get(CommonData_enSpeedData, &IND__stGetSpeedDataDoors);
    CommonData_Get(CommonData_enDoorsState, &IND__stGetDoorsData);
    if ((IND__stGetDoorsData.boFrontLeftDoor || IND__stGetDoorsData.boFrontRightDoor || IND__stGetDoorsData.boRearLeftDoor || IND__stGetDoorsData.boRearRightDoor) && (IND__stGetSpeedDataDoors.u16kmh > 3))
    {
        IND__iDoorOpen = entrue;
    }
    else
    {
        IND__iDoorOpen = enfalse;
    }
    if (IND__iDoorOpen != IND__iExDoorOpen)
    {
        IND__iExDoorOpen = IND__iDoorOpen;
        CommonData_Set(CommonData_enIndication2, &IND__iDoorOpen);
    }
}
void IND_vSetIndication3()
{
    INM_stInputs IND_stINMValues;
    static Indications IND__iHorn;
    // CommonData_Get(CommonData_enInmValues, &IND_stINMValues);
    if (IND_stINMValues.stKEY4)
    {
        IND__iHorn = entrue;
    }
    else
    {
        IND__iHorn = enfalse;
    }
    // CommonData_Set(CommonData_enIndication3, &IND__iHorn);
}
void IND_vGetLowBeamIndication()
{
}
void IND_vGetHighBeamIndication()
{
}
void IND_vGetFogLightsIndication()
{
}
void IND_vGetLowBatteryIndication()
{
    bool IND__bLowBattery;
    static bool IND__bLowBatteryOld = 0;
    unsigned long IND__ulCurrentMillis = millis();
    CommonData_Get(CommonData_enLowBattery, &IND__bLowBattery);
    if (IND__bLowBattery && (IND__bLowBattery != IND__bLowBatteryOld))
    {
        IND__bLowBatteryOld = IND__bLowBattery;
        CommonData_Set(CommonData_enBuzzerA, &IND__bLowBattery);
    }
    else if (IND__bLowBattery == 0 && (IND__bLowBattery != IND__bLowBatteryOld))
    {
        IND__bLowBatteryOld = IND__bLowBattery;
    }
    else if (IND__bLowBattery && (IND__bLowBattery == IND__bLowBatteryOld) && (IND__ulCurrentMillis - IND__ulRepeatIndication >= 45000))
    {
        CommonData_Set(CommonData_enBuzzerA, &IND__bLowBattery);
        IND__ulRepeatIndication = IND__ulCurrentMillis;
    }
}
void IND_vGetIndication1()
{
    bool IND__bHighSpeed;
    static bool IND__bHighSpeedOld = 0;
    unsigned long IND__ulCurrentMillisSpeed = millis();
    CommonData_Get(CommonData_enIndication1, &IND__bHighSpeed);
    if (IND__bHighSpeed && (IND__bHighSpeed != IND__bHighSpeedOld))
    {
        IND__bHighSpeedOld = IND__bHighSpeed;
        CommonData_Set(CommonData_enBuzzerB, &IND__bHighSpeed);
    }
    else if (IND__bHighSpeed == 0 && (IND__bHighSpeed != IND__bHighSpeedOld))
    {
        IND__bHighSpeedOld = IND__bHighSpeed;
    }
    else if (IND__bHighSpeed && (IND__bHighSpeed == IND__bHighSpeedOld) && (IND__ulCurrentMillisSpeed - IND__ulRepeatIndicationSpeed >= 45000))
    {
        CommonData_Set(CommonData_enBuzzerB, &IND__bHighSpeed);
        IND__ulRepeatIndicationSpeed = IND__ulCurrentMillisSpeed;
    }
}
void IND_vGetIndication2()
{
    bool IND__bSpeedAndDoors;
    static bool IND__bSpeedAndDoorsOld = 0;
    unsigned long IND__ulCurrentMillisDoors = millis();
    CommonData_Get(CommonData_enIndication2, &IND__bSpeedAndDoors);
    if (IND__bSpeedAndDoors && (IND__bSpeedAndDoors != IND__bSpeedAndDoorsOld))
    {
        IND__bSpeedAndDoorsOld = IND__bSpeedAndDoors;
        CommonData_Set(CommonData_enBuzzerC, &IND__bSpeedAndDoors);
    }
    else if (!IND__bSpeedAndDoors && (IND__bSpeedAndDoors != IND__bSpeedAndDoorsOld))
    {
        IND__bSpeedAndDoorsOld = IND__bSpeedAndDoors;
    }
    else if (IND__bSpeedAndDoors && (IND__bSpeedAndDoors == IND__bSpeedAndDoorsOld) && (IND__ulCurrentMillisDoors - IND__ulRepeatIndicationDoor >= 45000))
    {
        CommonData_Set(CommonData_enBuzzerC, &IND__bSpeedAndDoors);
        IND__ulRepeatIndicationDoor = IND__ulCurrentMillisDoors;
    }
}
void IND_vGetIndication3()
{
    bool IND__bIndication3;
    static bool IND__bIndication3Old = 0;
    CommonData_Get(CommonData_enIndication3, &IND__bIndication3);
    if (IND__bIndication3 && (IND__bIndication3 != IND__bIndication3Old))
    {
        IND__bIndication3Old = IND__bIndication3;
        // CommonData_Set(CommonData_enShiftBuzzer, &IND__bIndication3);
    }
    else if (!IND__bIndication3 && (IND__bIndication3 != IND__bIndication3Old))
    {
        IND__bIndication3Old = IND__bIndication3;
        // CommonData_Set(CommonData_enShiftBuzzer, &IND__bIndication3);
    }
}