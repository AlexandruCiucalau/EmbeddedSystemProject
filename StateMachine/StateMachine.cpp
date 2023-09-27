#include "StateMachineI.h"
#include "StateMachineE.h"
#include "CommonDataE.h"
#include "EEPROME.h"

void STM_Setup()
{
  STM_States enCurrentState = enInit;
  STM_setNextState(enCurrentState);
}

void STM_LOOP()
{
  CommonData_Get(CommonData_enSpeedData, &stGetSpeedData);
  static uint8_t u8Counter = 0;
  static STM_States enPreviousState = enInit;
  static STM_States enCurrentState = enInit;
  bool STM__bInd1;
  bool STM__bInd2;
  bool STM__bLowBattery;
  bool STM__bIndicationScreen;
  static unsigned long STM__ulTimeSpentIndications = 0;
  static bool okTime = true;
  CommonData_Get(CommonData_enIndication1, &STM__bInd1);
  CommonData_Get(CommonData_enLowBattery, &STM__bLowBattery);
  CommonData_Get(CommonData_enIndication2, &STM__bInd2);
  STM__bIndicationScreen = STM__bInd1 || STM__bInd2 || STM__bLowBattery;
  if (!STM__bIndicationScreen)
  {
    STM__ulTimeSpentIndications = millis();
  }
  
  if (u8Counter <= STM__nWELCOME_SCREEN_TIME)
  {
    u8Counter++;
    enCurrentState = enWelcomeScreen;
  }
  else if (STM__bIndicationScreen && millis() - STM__ulTimeSpentIndications >= 5000)
  {
    enCurrentState = enIndicationScreen;
  }
  else if (stGetSpeedData.u16kmh >= STM__SPEED_LOWER_LIMIT && Doors_boClosed() && enCurrentState != enWelcomeScreen)
  {
    enCurrentState = enSpeedScreen;
  }
  else if (!Doors_boClosed() && enCurrentState != enSpeedScreen)
  {
    enCurrentState = enDoorsScreen;
  }
  else
  {
    enCurrentState = enHomeScreen;
  }

  if (enPreviousState != enCurrentState)
  {
    enPreviousState = enCurrentState;
    STM_setNextState(enCurrentState);
  }
}

void STM_setNextState(STM_States newState)
{
  STM_States enCurrentState;
  CommonData_Get(CommonData_enStateMachineStatus, (void *)&enCurrentState);
  switch (enCurrentState)
  {
  default:
    CommonData_Set(CommonData_enStateMachineStatus, (void *)&newState);
    break;
  }
}