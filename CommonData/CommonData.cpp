/***************************************************************************
 *=====================      Copyright by novartsoft.com      ===============
 ****************************************************************************
 * Title        : CommonData.cpp
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

#include "CommonDataI.h"
#include <Arduino.h>
// #define CD__DEBUG

void CommonData_Setup()
{
  for (int i = 0; i < CommonData_enMaxIDs; i++)
  {
    CommonData__Queues[i] = xQueueCreate(3, CommonData__Sizes[i]);
    vTaskDelay(15 / portTICK_PERIOD_MS);
    if (CommonData__Queues[i] == NULL)
    {
      Serial.print("Error creating the queue ");
      Serial.println(i);
    }
  }
  
  CommonData__Addresses[CommonData_enStateMachineStatus] = (int *)&CommonData__StateMachineStatus;
  CommonData__Addresses[CommonData_enTemperature] = (int *)&CommonData__Temperature;
  CommonData__Addresses[CommonData_enTemperatureFormat] = (int *)&CommonData__TempFormat;
  CommonData__Addresses[CommonData_enShiftHWTT1] = (int *)&CommonData__ShiftHWTT1;
  CommonData__Addresses[CommonData_enShiftHWTT2] = (int *)&CommonData__ShiftHWTT2;
  CommonData__Addresses[CommonData_enShiftHWTT3] = (int *)&CommonData__ShiftHWTT3;
  CommonData__Addresses[CommonData_enShiftBargraphLVL] = (int *)&CommonData__ShiftBarGraphLVL;
  CommonData__Addresses[CommonData_enShiftBuzzer] = (int *)&CommonData__ShiftBuzzer;
  CommonData__Addresses[CommonData_enRelayData] = (int *)&CommonData__RelayData;
  CommonData__Addresses[CommonData_enMuxValues] = (int *)&CommonData__MuxValues;
  CommonData__Addresses[CommonData_enInmValues] = (int *)&CommonData__InmValues;
  CommonData__Addresses[CommonData_enSpeedData] = (int *)&CommonData__SpeedData;
  CommonData__Addresses[CommonData_enBuzzerA] = (int *)&CommonData__BuzzerA;
  CommonData__Addresses[CommonData_enBuzzerB] = (int *)&CommonData__BuzzerB;
  CommonData__Addresses[CommonData_enBuzzerC] = (int *)&CommonData__BuzzerC;
  CommonData__Addresses[CommonData_enBuzzerD] = (int *)&CommonData__BuzzerD;
  CommonData__Addresses[CommonData_enLowBeam] = (int *)&CommonData__LowBeam;
  CommonData__Addresses[CommonData_enHighBeam] = (int *)&CommonData__HighBeam;
  CommonData__Addresses[CommonData_enFogLights] = (int *)&CommonData__FogLights;
  CommonData__Addresses[CommonData_enLowBattery] = (int *)&CommonData__LowBattery;
  CommonData__Addresses[CommonData_enIndication1] = (int *)&CommonData__Indication1;
  CommonData__Addresses[CommonData_enIndication2] = (int *)&CommonData__Indication2;
  CommonData__Addresses[CommonData_enIndication3] = (int *)&CommonData__Indication3;
  CommonData__Addresses[CommonData_enDoorsState] = (int *)&CommonData__DoorsState;
  CommonData__Addresses[CommonData_enLightsData] = (int *)&CommonData__LightsData;
  CommonData__Addresses[CommonData_enWiFiIPAddress] = (int *)&CommonData__WiFiIPAddress;
  CommonData__Addresses[CommonData_enTimeDetails] = (int *)&CommonData__TimeDetails;
  CommonData__Addresses[CommonData_enGearBox] = (int *)&CommonData__GearBox;
}

void CommonData_ReadQueues()
{
  for (int i = 0; i < CommonData_enMaxIDs; i++)
  {
    if (xQueueReceive(CommonData__Queues[i], (void *)CommonData__Addresses[i], 0) == pdTRUE)
    {
      CommonData__Events[i]((CommonData_enIDs)i);
    }
  }
}

void CommonData_Get(CommonData_enIDs ID, void *const pvBuffer)
{
  if ((pvBuffer != NULL) && (CommonData__Addresses[ID] != NULL))
  {
    memcpy(pvBuffer, CommonData__Addresses[ID], CommonData__Sizes[ID]);
  }
}

void CommonData_Set(CommonData_enIDs ID, const void *const pvItemToQueue)
{
  if ((pvItemToQueue != NULL) && (CommonData__Queues[ID] != NULL))
  {
    (void)xQueueSend(CommonData__Queues[ID], pvItemToQueue, 10);
  }
}

/* functions for events */
void CommonData__Events_StateMachineStatus(CommonData_enIDs ID)
{
}

void CommonData__Events_ButtonsStates(CommonData_enIDs ID)
{
}

void CommonData__Events_TemperatureState(CommonData_enIDs ID)
{
  // HMI_vEvents(ID);
}
void CommonData__Events_TemperatureFormat(CommonData_enIDs ID)
{
}

void CommonData__Events_ShiftHWTT1(CommonData_enIDs ID)
{
}
void CommonData__Events_ShiftHWTT2(CommonData_enIDs ID)
{
}

void CommonData__Events_ShiftHWTT3(CommonData_enIDs ID)
{
}

void CommonData__Events_ShiftBarGraphLevel(CommonData_enIDs ID)
{
}

void CommonData__Events_ShiftBuzzer(CommonData_enIDs ID)
{
}

void CommonData__Events_RelayData(CommonData_enIDs ID)
{
}

void CommonData__Events_MuxValues(CommonData_enIDs ID)
{
}

void CommonData__Events_Shift_GetLVL(CommonData_enIDs ID)
{
}

void CommonData__Events_BuzzerA(CommonData_enIDs ID)
{
  Sound_vsetBuzzerA();
}

void CommonData__Events_BuzzerB(CommonData_enIDs ID)
{
  Sound_vsetBuzzerB();
}

void CommonData__Events_BuzzerC(CommonData_enIDs ID)
{
  Sound_vsetBuzzerC();
}

void CommonData__Events_BuzzerD(CommonData_enIDs ID)
{
  Sound_vsetBuzzerD();
}
void CommonData__Events_LowBeam(CommonData_enIDs ID)
{
}

void CommonData__Events_HighBeam(CommonData_enIDs ID)
{
}

void CommonData__Events_FogLights(CommonData_enIDs ID)
{
}

void CommonData__Events_LowBattery(CommonData_enIDs ID)
{
}

void CommonData__Events_Indication1(CommonData_enIDs ID)
{
}

void CommonData__Events_Indication2(CommonData_enIDs ID)
{
}

void CommonData__Events_Indication3(CommonData_enIDs ID)
{
}

void CommonData__Events_InmValues(CommonData_enIDs ID)
{
}

void CommonData__Events_SpeedData(CommonData_enIDs ID)
{
}

void CommonData__Events_DoorsState(CommonData_enIDs ID)
{
}

void CommonData__Events_LightsData(CommonData_enIDs ID)
{
}

void CommonData__Events_WiFiIPAddress(CommonData_enIDs ID)
{
}

void CommonData__Events_TimeDetails(CommonData_enIDs ID)
{
}

  void CommonData__Events_GearBox(CommonData_enIDs ID)
  {}
