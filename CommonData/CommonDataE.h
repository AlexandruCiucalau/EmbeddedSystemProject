/***************************************************************************
 *=====================      Copyright by novartsoft.com      ===============
 ****************************************************************************
 * Title        : CommonDataE.h
 *
 * Description  : This module is responsable of data used commonly in more than one
 *                module
 *
 * Environment  : ESP32
 *
 * Responsible  : Catalin Gyorgy
 *
 * History:
 * 10.06.2021    CatGyo  Initial revision
 */
#ifndef CommonDataE_h
#define CommonDataE_h

#include <Arduino.h>

enum CommonData_enIDs
{
  CommonData_enStateMachineStatus = 0,
  CommonData_enTemperature,
  CommonData_enTemperatureFormat,
  CommonData_enShiftHWTT1,
  CommonData_enShiftHWTT2,
  CommonData_enShiftHWTT3,
  CommonData_enShiftBargraphLVL,
  CommonData_enShiftBuzzer,
  CommonData_enRelayData,
  CommonData_enMuxValues,
  CommonData_enInmValues,
  CommonData_enSpeedData,
  CommonData_enBuzzerA,
  CommonData_enBuzzerB,
  CommonData_enBuzzerC,
  CommonData_enBuzzerD,
  CommonData_enLowBeam,
  CommonData_enHighBeam,
  CommonData_enFogLights,
  CommonData_enLowBattery,
  CommonData_enIndication1,
  CommonData_enIndication2,
  CommonData_enIndication3,
  CommonData_enDoorsState,
  CommonData_enLightsData,
  CommonData_enWiFiIPAddress,
  CommonData_enTimeDetails,
  CommonData_enGearBox,
  CommonData_enMaxIDs
};

void CommonData_Setup();
void CommonData_ReadQueues();
void CommonData_Get(CommonData_enIDs, void *const pvBuffer); // id ce memorie acceseaza
void CommonData_Set(CommonData_enIDs, const void *const);
#endif