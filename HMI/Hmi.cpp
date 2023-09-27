#include "Arduino.h"
// tft display
#include <SPI.h>
#include <TFT_eSPI.h>
#include "HmiI.h"
#include "HmiE.h"
#include "Helper.h"
#include "TempE.h"
#include "GearBoxE.h"
#include "SoundE.h"
#include "StateMachineE.h"
#include "ShiftE.h"
#include "SpeedE.h"
#include "EEPROME.h"
#include "TimeE.h"
#include "RELAYE.h"
#include "DoorsE.h"

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library
HMI_Helper HMI__Helper = HMI_Helper();
temp_stValues hmi_stTempValues;
Speed_stData HMI__stGetSpeedData;
uint8_t HMI__u8SpeedUnit;
Relay_stData HMI_stGetRelayData;
Doors_stData HMI__stGetDoorsData;
uint8_t HMI__u8TimeFormat;
uint8_t HMI__u8TempFormat;
Time_Details HMI__stTimeDetails;
stGearBox HMI__stGearBox;
static stSendTime HMI_stTimeValues;

void HMI_Setup(void)
{
  tft.begin();
  tft.setRotation(HELPER_TFT_ORIENTATION);
  tft.fillScreen(HELPER_COLOR_BACKGROUND);
}

void HMI_LOOP(void)
{
  STM_States enCurrentMachineState;
  CommonData_Get(CommonData_enStateMachineStatus, &enCurrentMachineState);
  HMI__vDrawSkeleton(enCurrentMachineState);
  HMI__vDrawCyclically(enCurrentMachineState);
}

void print(float val)
{
  Serial.println(val);
}
void print2(int32_t val)
{
  Serial.println(val);
}

void HMI__vDrawSkeleton(STM_States enCurrentMachineState)
{
  static STM_States enCurrentMachineStatePrev;

  if (enCurrentMachineStatePrev != enCurrentMachineState)
  {

    switch (enCurrentMachineState)
    {
    case enWelcomeScreen:
      HMI__Helper.drawImage(tft, "/screens/welcome.jpg", 0, 0);
      break;
    case enHomeScreen:
      HMI__Helper.drawImage(tft, "/screens/background.jpg", 0, 0);
      tft.fillRect(0, 210, TFT_WIDTH, 2, TFT_WHITE);
      tft.fillRect(0, 260, TFT_WIDTH, 2, TFT_WHITE);
      HMI__Helper.drawImage(tft, "/bargraph/charging-station.jpg", 22, 275);
      tft.setTextColor(TFT_WHITE, HELPER_COLOR_BACKGROUND);
      tft.drawString("E", 74, 275, 2);
      tft.setTextColor(TFT_WHITE, HELPER_COLOR_BACKGROUND);
      tft.drawString("F", 215, 275, 2);
      // Time_vSendTimeToHMI();
      CommonData_Get(CommonData_enTimeDetails, &HMI__stTimeDetails);
      EEPROM_ReadData(enTimeFormat, &HMI__timeFormat);
      if (HMI__timeFormat == 12)
      {
        tft.drawString(HMI__stTimeDetails.strTimeStringSmall, 50, 70, 6);
      }
      else
      {
        tft.drawString(HMI__stTimeDetails.strTimeString, 50, 70, 6);
      }
      // tft.drawString(HMI__stTimeDetails.strTimeString, 60, 70, 6);
      break;
    case enDoorsScreen:
      HMI__Helper.drawImage(tft, "/screens/background.jpg", 0, 0);
      HMI__vDisplayDoorsSkeleton();
      tft.fillRect(0, 210, TFT_WIDTH, 2, TFT_WHITE);
      tft.fillRect(0, 260, TFT_WIDTH, 2, TFT_WHITE);
      HMI__Helper.drawImage(tft, "/bargraph/charging-station.jpg", 22, 275);
      tft.setTextColor(TFT_WHITE, HELPER_COLOR_BACKGROUND);
      tft.drawString("E", 74, 275, 2);
      tft.setTextColor(TFT_WHITE, HELPER_COLOR_BACKGROUND);
      tft.drawString("F", 215, 275, 2);
      CommonData_Get(CommonData_enTemperature, &hmi_stTempValues);
      tft.drawString(String(hmi_stTempValues.stCelsius, HMI__TEMP_ONE_DECIMAL), 187, 5, 2);
      tft.drawCircle(222, 10, 2.5, TFT_WHITE);
      tft.drawString("C", 227, 5, 2);
      break;
    case enSpeedScreen:
      HMI__Helper.drawImage(tft, "/screens/background.jpg", 0, 0);
      tft.fillRect(0, 210, TFT_WIDTH, 2, TFT_WHITE);
      tft.fillRect(0, 260, TFT_WIDTH, 2, TFT_WHITE);
      HMI__Helper.drawImage(tft, "/bargraph/charging-station.jpg", 22, 275);
      tft.setTextColor(TFT_WHITE, HELPER_COLOR_BACKGROUND);
      tft.drawString("E", 74, 275, 2);
      tft.setTextColor(TFT_WHITE, HELPER_COLOR_BACKGROUND);
      tft.drawString("F", 215, 275, 2);
      break;
    case enInit:
      break;
    case enIndicationScreen:
      bool HMI_bind2;
      HMI__Helper.drawImage(tft, "/screens/background.jpg", 0, 0);
      CommonData_Get(CommonData_enIndication2, &HMI_bind2);
      if (HMI_bind2)
      {
        HMI__vDisplayDoorsSkeleton();
      }
      tft.fillRect(0, 210, TFT_WIDTH, 2, TFT_WHITE);
      tft.fillRect(0, 260, TFT_WIDTH, 2, TFT_WHITE);
      HMI__Helper.drawImage(tft, "/bargraph/charging-station.jpg", 22, 275);
      tft.setTextColor(TFT_WHITE, HELPER_COLOR_BACKGROUND);
      tft.drawString("E", 74, 275, 2);
      tft.setTextColor(TFT_WHITE, HELPER_COLOR_BACKGROUND);
      tft.drawString("F", 215, 275, 2);
      CommonData_Get(CommonData_enTemperature, &hmi_stTempValues);
      tft.drawString(String(hmi_stTempValues.stCelsius, HMI__TEMP_ONE_DECIMAL), 187, 5, 2);
      tft.drawCircle(222, 10, 2.5, TFT_WHITE);
      tft.drawString("C", 227, 5, 2);
      break;
    default:
      break;
    }
    enCurrentMachineStatePrev = enCurrentMachineState;
  }
}

void HMI__vDrawCyclically(STM_States enCurrentMachineState)
{
  switch (enCurrentMachineState)
  {
  case enWelcomeScreen:
    break;
  case enHomeScreen:
    HMI__vControlBarGraph();
    HMI__vControlIndications();
    HMI__vHomeScreenTemp();
    HMI__vTimeBigFont();
    HMI__vChangeGear();
    break;
  case enDoorsScreen:
    HMI__vDisplayDoorsState();
    HMI__vDisplayTemperature();
    HMI__vControlBarGraph();
    HMI__vTimeSmallFont();
    HMI__vControlIndications();
    break;
  case enSpeedScreen:
    HMI_vDrawSpeedGauge();
    HMI__vDisplayTemperature();
    HMI__vControlBarGraph();
    HMI__vTimeSmallFont();
    HMI__vControlIndications();
    HMI__vChangeGear();
    HMI__vDisplaySpeedGear();
    break;
  case enIndicationScreen:
    HMI__vControlBarGraph();
    HMI__vControlIndications();
    HMI__vDisplayLowBatteryIndication();
    HMI__vTimeSmallFont();
    HMI__vDisplayTemperature();
    HMI_vDrawIndications();
    break;
  default:
    // do nothing
    break;
  }
}

void HMI_vEvents(CommonData_enIDs ID)
{
  switch (ID)
  {
  default:
    break;
  }
}

void HMI__vDisplayTemperature()
{
  static unsigned long HMI__prevMillis = 0;
  CommonData_Get(CommonData_enTemperature, &hmi_stTempValues);
  EEPROM_ReadData(enTempFormat, &HMI__u8TempFormat);
  switch (HMI__u8TempFormat)
  {
  case 1:
    if (millis() - HMI__prevMillis >= 2000 && (hmi_stTempValues.stCelsius > 25 && hmi_stTempValues.stCelsius <= 28.5)) // Blinking feature ON
    {
      HMI__prevMillis = millis();
      tft.drawString(String(hmi_stTempValues.stCelsius, HMI__TEMP_ONE_DECIMAL), 187, 5, 2);
      tft.drawCircle(222, 10, 2.5, TFT_WHITE);
      tft.drawString("C", 227, 5, 2);
    }
    else if (millis() - HMI__prevMillis >= 1000 && (hmi_stTempValues.stCelsius > 28.5 && hmi_stTempValues.stCelsius <= 34)) // Blinking feature ON
    {
      HMI__prevMillis = millis();
      tft.drawString(String(hmi_stTempValues.stCelsius, HMI__TEMP_ONE_DECIMAL), 187, 5, 2);
      tft.drawCircle(222, 10, 2.5, TFT_WHITE);
      tft.drawString("C", 227, 5, 2);
    }
    else if (hmi_stTempValues.stCelsius < 25 || hmi_stTempValues.stCelsius > 34) // Blinking feature OFF
    {

      HMI__prevMillis = millis();
      tft.drawString(String(hmi_stTempValues.stCelsius, HMI__TEMP_ONE_DECIMAL), 187, 5, 2);
      tft.drawCircle(222, 10, 2.5, TFT_WHITE);
      tft.drawString("C", 227, 5, 2);
    }
    else
    {
      tft.drawString("          ", 187, 5, 2);
    }

    break;
  case 2:
    if (millis() - HMI__prevMillis >= 2000 && (hmi_stTempValues.stCelsius > 25 && hmi_stTempValues.stCelsius <= 28.5)) // Blinking feature ON
    {
      HMI__prevMillis = millis();
      tft.drawString(String(hmi_stTempValues.stFahrenheit, HMI__TEMP_ONE_DECIMAL), 187, 5, 2);
      tft.drawCircle(222, 10, 2.5, TFT_WHITE);
      tft.drawString("F", 227, 5, 2);
    }
    else if (millis() - HMI__prevMillis >= 1000 && (hmi_stTempValues.stCelsius > 28.5 && hmi_stTempValues.stCelsius <= 34)) // Blinking feature ON
    {
      HMI__prevMillis = millis();
      tft.drawString(String(hmi_stTempValues.stFahrenheit, HMI__TEMP_ONE_DECIMAL), 187, 5, 2);
      tft.drawCircle(222, 10, 2.5, TFT_WHITE);
      tft.drawString("F", 227, 5, 2);
    }
    else if (hmi_stTempValues.stCelsius < 25 || hmi_stTempValues.stCelsius > 34) // Blinking feature OFF
    {

      HMI__prevMillis = millis();
      tft.drawString(String(hmi_stTempValues.stFahrenheit, HMI__TEMP_ONE_DECIMAL), 187, 5, 2);
      tft.drawCircle(222, 10, 2.5, TFT_WHITE);
      tft.drawString("F", 227, 5, 2);
    }
    else
    {
      tft.drawString("          ", 187, 5, 2);
    }

    break;
  default:
    break;
  }
}

void HMI__vControlBarGraph()
{
  uint8_t HMI__u8fuelLevel;
  CommonData_Get(CommonData_enShiftBargraphLVL, &HMI__u8fuelLevel);

  const char *battery_state = (HMI__u8fuelLevel >= 1) ? "/bargraph/battery_on.jpg" : "/bargraph/battery_off.jpg";

  for (uint16_t i = 0; i < HMI__BARGRAPH_LEVELS; i++)
  {
    if (i < HMI__u8fuelLevel)
    {
      HMI__Helper.drawImage(tft, battery_state, 73 + (i * 40), 295);
    }
    else
    {
      HMI__Helper.drawImage(tft, "/bargraph/battery_off.jpg", 73 + (i * 40), 295);
    }
  }
}

void HMI__vControlIndications()
{
  bool HMI_boStash;
  CommonData_Get(CommonData_enLowBeam, &HMI_boStash);
  if (HMI_boStash)
  {
    HMI__Helper.drawImage(tft, "/telltales/low_beam_on.jpg", 22, 216);
  }
  else if (HMI_boStash == 0)
  {
    HMI__Helper.drawImage(tft, "/telltales/empty_icon.jpg", 22, 216);
  }

  bool HMI_boHighBeam;
  CommonData_Get(CommonData_enHighBeam, &HMI_boHighBeam);

  if (HMI_boHighBeam)
  {
    HMI__Helper.drawImage(tft, "/telltales/high_beam_on.jpg", 77, 216);
  }
  else if (HMI_boHighBeam == 0)
  {
    HMI__Helper.drawImage(tft, "/telltales/empty_icon.jpg", 77, 216);
  }

  bool HMI__boFogLights;
  CommonData_Get(CommonData_enFogLights, &HMI__boFogLights);

  if (HMI__boFogLights)
  {
    HMI__Helper.drawImage(tft, "/telltales/fog_lights_on.jpg", 132, 216);
  }
  else if (!HMI__boFogLights)
  {
    HMI__Helper.drawImage(tft, "/telltales/empty_icon.jpg", 132, 216);
  }
}

void HMI__vDisplayDoorsSkeleton()
{
  CommonData_Get(CommonData_enDoorsState, &HMI__stGetDoorsData);
  if (!HMI__stGetDoorsData.boFrontLeftDoor)
  {
    HMI__Helper.drawImage(tft, "/doorstates/LFdoorclosed.jpg", 60, 24);
  }
  else
  {
    HMI__Helper.drawImage(tft, "/doorstates/LFdooropen.jpg", 60, 24);
  }

  if (!HMI__stGetDoorsData.boFrontRightDoor)
  {
    HMI__Helper.drawImage(tft, "/doorstates/RFdoorclosed.jpg", 120, 24);
  }
  else
  {
    HMI__Helper.drawImage(tft, "/doorstates/RFdooropen.jpg", 120, 24);
  }

  if (!HMI__stGetDoorsData.boRearLeftDoor)
  {
    HMI__Helper.drawImage(tft, "/doorstates/LBdoorclosed.jpg", 60, 116);
  }
  else
  {
    HMI__Helper.drawImage(tft, "/doorstates/LBdooropen.jpg", 60, 116);
  }

  if (!HMI__stGetDoorsData.boRearRightDoor)
  {
    HMI__Helper.drawImage(tft, "/doorstates/RBdoorclosed.jpg", 120, 116);
  }
  else
  {
    HMI__Helper.drawImage(tft, "/doorstates/RBdooropen.jpg", 120, 116);
  }
}

void HMI__vDisplayDoorsState()
{
  CommonData_Get(CommonData_enDoorsState, &HMI__stGetDoorsData);
  if (!HMI__stGetDoorsData.boFrontLeftDoor && (HMI__stGetDoorsData.boFrontLeftDoor != HMI__boDoorsPreviousValue[HMI__DOORS_FRONT_LEFT]))
  {
    HMI__Helper.drawImage(tft, "/doorstates/LFdoorclosed.jpg", 60, 24);
    HMI__boDoorsPreviousValue[HMI__DOORS_FRONT_LEFT] = HMI__stGetDoorsData.boFrontLeftDoor;
  }
  else if (HMI__stGetDoorsData.boFrontLeftDoor && (HMI__stGetDoorsData.boFrontLeftDoor != HMI__boDoorsPreviousValue[HMI__DOORS_FRONT_LEFT]))
  {
    HMI__Helper.drawImage(tft, "/doorstates/LFdooropen.jpg", 60, 24);
    HMI__boDoorsPreviousValue[HMI__DOORS_FRONT_LEFT] = HMI__stGetDoorsData.boFrontLeftDoor;
  }

  if (!HMI__stGetDoorsData.boFrontRightDoor && (HMI__stGetDoorsData.boFrontRightDoor != HMI__boDoorsPreviousValue[HMI__DOORS_FRONT_RIGHT]))
  {
    HMI__Helper.drawImage(tft, "/doorstates/RFdoorclosed.jpg", 120, 24);
    HMI__boDoorsPreviousValue[HMI__DOORS_FRONT_RIGHT] = HMI__stGetDoorsData.boFrontRightDoor;
  }
  else if (HMI__stGetDoorsData.boFrontRightDoor && (HMI__stGetDoorsData.boFrontRightDoor != HMI__boDoorsPreviousValue[HMI__DOORS_FRONT_RIGHT]))
  {
    HMI__Helper.drawImage(tft, "/doorstates/RFdooropen.jpg", 120, 24);
    HMI__boDoorsPreviousValue[HMI__DOORS_FRONT_RIGHT] = HMI__stGetDoorsData.boFrontRightDoor;
  }

  if (!HMI__stGetDoorsData.boRearLeftDoor && (HMI__stGetDoorsData.boRearLeftDoor != HMI__boDoorsPreviousValue[HMI__DOORS_REAR_LEFT]))
  {
    HMI__Helper.drawImage(tft, "/doorstates/LBdoorclosed.jpg", 60, 116);
    HMI__boDoorsPreviousValue[HMI__DOORS_REAR_LEFT] = HMI__stGetDoorsData.boRearLeftDoor;
  }
  else if (HMI__stGetDoorsData.boRearLeftDoor && (HMI__stGetDoorsData.boRearLeftDoor != HMI__boDoorsPreviousValue[HMI__DOORS_REAR_LEFT]))
  {
    HMI__Helper.drawImage(tft, "/doorstates/LBdooropen.jpg", 60, 116);
    HMI__boDoorsPreviousValue[HMI__DOORS_REAR_LEFT] = HMI__stGetDoorsData.boRearLeftDoor;
  }

  if (!HMI__stGetDoorsData.boRearRightDoor && (HMI__stGetDoorsData.boRearRightDoor != HMI__boDoorsPreviousValue[HMI__DOORS_REAR_RIGHT]))
  {
    HMI__Helper.drawImage(tft, "/doorstates/RBdoorclosed.jpg", 120, 116);
    HMI__boDoorsPreviousValue[HMI__DOORS_REAR_RIGHT] = HMI__stGetDoorsData.boRearRightDoor;
  }
  else if (HMI__stGetDoorsData.boRearRightDoor && (HMI__stGetDoorsData.boRearRightDoor != HMI__boDoorsPreviousValue[HMI__DOORS_REAR_RIGHT]))
  {
    HMI__Helper.drawImage(tft, "/doorstates/RBdooropen.jpg", 120, 116);
    HMI__boDoorsPreviousValue[HMI__DOORS_REAR_RIGHT] = HMI__stGetDoorsData.boRearRightDoor;
  }
}

// function to display the time with a bigger font
void HMI__vTimeBigFont()
{
  stSendTime HMI__stTime;
  // Time_vSendTimeToHMI();
  static uint8_t HMI__u8TimeStringOldMinutes = 61;
  static uint8_t HMI__u8OldFormat = 25;
  uint8_t HMI__u8TimeFormat;
  CommonData_Get(CommonData_enTimeDetails, &HMI__stTimeDetails);
  EEPROM_ReadData(enTimeFormat, &HMI__u8TimeFormat);
  EEPROM_ReadData(enTime, (byte *)&HMI__stTime);

  if ((HMI__u8OldFormat != HMI__u8TimeFormat) || (HMI__stTime.minutes != HMI__u8TimeStringOldMinutes))
  {
    HMI__u8TimeStringOldMinutes = HMI__stTime.minutes;
    HMI__u8OldFormat = HMI__u8TimeFormat;
    switch (HMI__u8TimeFormat)
    {
    case 12:
      tft.drawString(HMI__stTimeDetails.strTimeStringSmall, 50, 70, 6);
      break;
    case 24:
      tft.drawString(HMI__stTimeDetails.strTimeString, 50, 70, 6);
      break;
    default:
      break;
    }
  }
}

// function to display the time with a smaller font
void HMI__vTimeSmallFont()
{
  // Time_vSendTimeToHMI();
  EEPROM_ReadData(enTimeFormat, (byte *)&HMI__timeFormat);
  EEPROM_ReadData(enTime, (byte *)&HMI_stTimeValues);
  CommonData_Get(CommonData_enTimeDetails, &HMI__stTimeDetails);
  switch (HMI__timeFormat)
  {
  case HMI__TIME_FORMAT_1:
    tft.drawString(HMI__stTimeDetails.strTimeStringSmall, 6, 5, 2);
    if (HMI_stTimeValues.hours > 12)
    {
      tft.drawString("PM", 60, 5, 2);
    }
    else if (HMI_stTimeValues.hours < 12)
    {
      tft.drawString("AM", 60, 5, 2);
    }
    break;
  case HMI__TIME_FORMAT_2:
    tft.fillRect(60, 5, 20, 20, HELPER_COLOR_BACKGROUND); // erase AM / PM
    tft.drawString(HMI__stTimeDetails.strTimeString, 6, 5, 2);
    break;
  default:
    break;
  }
}

// function to diplay the temperature with a bigger font
void HMI__vHomeScreenTemp()
{
  static unsigned long HMI__prevMillis = 0;
  CommonData_Get(CommonData_enTemperature, &hmi_stTempValues);
  EEPROM_ReadData(enTempFormat, (byte *)&HMI__u8TempFormat);
  switch (HMI__u8TempFormat)
  {
  case 1:
    if (millis() - HMI__prevMillis >= 2000 && (hmi_stTempValues.stCelsius > 25 && hmi_stTempValues.stCelsius <= 28.5)) // Blinking feature ON
    {
      HMI__prevMillis = millis();
      tft.drawString(String(hmi_stTempValues.stCelsius, HMI__TEMP_ONE_DECIMAL), 83, 120, 4);
      tft.drawString("o", 138, 116, 2);
      tft.drawString("C", 146, 120, 4);
    }
    else if (millis() - HMI__prevMillis >= 1000 && (hmi_stTempValues.stCelsius > 28.5 && hmi_stTempValues.stCelsius <= 34)) // Blinking feature ON
    {
      HMI__prevMillis = millis();
      tft.drawString(String(hmi_stTempValues.stCelsius, HMI__TEMP_ONE_DECIMAL), 83, 120, 4);
      tft.drawString("o", 138, 116, 2);
      tft.drawString("C", 146, 120, 4);
    }
    else if (hmi_stTempValues.stCelsius < 25 || hmi_stTempValues.stCelsius > 34) // Blinking feature OFF
    {
      HMI__prevMillis = millis();
      tft.drawString(String(hmi_stTempValues.stCelsius, HMI__TEMP_ONE_DECIMAL), 83, 120, 4);
      tft.drawString("o", 138, 116, 2);
      tft.drawString("C", 146, 120, 4);
    }
    else
    {
      tft.drawString("                         ", 83, 120, 4);
    }

    break;
  case 2:
    if (millis() - HMI__prevMillis >= 2000 && (hmi_stTempValues.stCelsius > 25 && hmi_stTempValues.stCelsius <= 28.5)) // Blinking feature ON
    {
      HMI__prevMillis = millis();
      tft.drawString(String(hmi_stTempValues.stFahrenheit, HMI__TEMP_ONE_DECIMAL), 83, 120, 4);
      tft.drawString("o", 138, 116, 2);
      tft.drawString("F  ", 146, 120, 4);
    }
    else if (millis() - HMI__prevMillis >= 1000 && (hmi_stTempValues.stCelsius > 28.5 && hmi_stTempValues.stCelsius <= 31)) // Blinking feature ON
    {
      HMI__prevMillis = millis();
      tft.drawString(String(hmi_stTempValues.stFahrenheit, HMI__TEMP_ONE_DECIMAL), 83, 120, 4);
      tft.drawString("o", 138, 116, 2);
      tft.drawString("F  ", 146, 120, 4);
    }
    else if (hmi_stTempValues.stCelsius < 25 || hmi_stTempValues.stCelsius > 31) // Blinking feature OFF
    {
      HMI__prevMillis = millis();
      tft.drawString(String(hmi_stTempValues.stFahrenheit, HMI__TEMP_ONE_DECIMAL), 83, 120, 4);
      tft.drawString("o", 138, 116, 2);
      tft.drawString("F  ", 146, 120, 4);
    }
    else
    {
      tft.drawString("                         ", 83, 120, 4);
    }

  default:
    break;
  }
}
void HMI__vDisplayLowBatteryIndication()
{
  bool HMI__bLowBattery;
  static bool HMI__bLowBatteryOld = 0;
  CommonData_Get(CommonData_enLowBattery, &HMI__bLowBattery);
  if (HMI__bLowBattery && (HMI__bLowBattery != HMI__bLowBatteryOld))
  {
    HMI__Helper.drawImage(tft, "/telltales/low_battery_on.jpg", 187, 216);
    HMI__bLowBatteryOld = HMI__bLowBattery;
  }
  else if (!HMI__bLowBattery && (HMI__bLowBattery != HMI__bLowBatteryOld))
  {
    HMI__Helper.drawImage(tft, "/telltales/empty_icon.jpg", 187, 216);
    HMI__bLowBatteryOld = HMI__bLowBattery;
  }
}
void HMI__vDisplayHighSpeedIndication()
{
  bool HMI__bHighSpeed;
  static bool HMI__bHighSpeedOld = 0;
  CommonData_Get(CommonData_enIndication1, &HMI__bHighSpeed);
  if (HMI__bHighSpeed && (HMI__bHighSpeed != HMI__bHighSpeedOld))
  {
    tft.setTextColor(TFT_WHITE, HELPER_COLOR_BACKGROUND);
    tft.drawString(HMI__SPEED_WARNING, 65, 170);
    HMI__bHighSpeedOld = HMI__bHighSpeed;
  }
  else if (!HMI__bHighSpeed && (HMI__bHighSpeed != HMI__bHighSpeedOld))
  {
    tft.drawString("                    ", 65, 170);
    HMI__bHighSpeedOld = HMI__bHighSpeed;
  }
}
void HMI__vDisplayDoorOpenWhileSpeeding()
{
  bool HMI__bSpeedAndDoors;
  static bool HMI__bSpeedAndDoorsOld = 0;
  CommonData_Get(CommonData_enIndication2, &HMI__bSpeedAndDoors);
  if (HMI__bSpeedAndDoors && (HMI__bSpeedAndDoors != HMI__bSpeedAndDoorsOld))
  {
        HMI__vDisplayDoorsSkeleton();
   // HMI__vDisplayDoorsState();
    tft.drawRect(90, 90, 65, 65, 0xF800);
    tft.fillRect(90, 90, 65, 65, 0xF800);
    tft.drawString("INCHIDE", 100, 120);
    tft.drawString("USA", 110, 130);
    HMI__bSpeedAndDoorsOld = HMI__bSpeedAndDoors;
  }
  else if (!HMI__bSpeedAndDoors && (HMI__bSpeedAndDoors != HMI__bSpeedAndDoorsOld))
  {
    HMI__vDisplayDoorsState();
    HMI__bSpeedAndDoorsOld = HMI__bSpeedAndDoors;
    HMI__vDisplayDoorsSkeleton();
  }
}

void HMI__vChangeGear()
{
  CommonData_Get(CommonData_enGearBox, &HMI__stGearBox);
  if (!HMI__stGearBox.neutral && !HMI__stGearBox.drive && !HMI__stGearBox.parking && !HMI__stGearBox.reverse)
  {
    HMI__stGearBox.neutral = true;
  }

  if (HMI__stGearBox.parking)
  {
    tft.setTextColor(HELPER_COLOR_BACKGROUND, TFT_WHITE);
    tft.drawString("P", 75, 183, 4);
    tft.setTextColor(TFT_WHITE, HELPER_COLOR_BACKGROUND);
    tft.drawString("R", 100, 183, 4);
    tft.drawString("N", 125, 183, 4);
    tft.drawString("D", 150, 183, 4);
  }
  else if (HMI__stGearBox.reverse)
  {
    tft.setTextColor(TFT_WHITE, HELPER_COLOR_BACKGROUND);
    tft.drawString("P", 75, 183, 4);
    tft.setTextColor(HELPER_COLOR_BACKGROUND, TFT_WHITE);
    tft.drawString("R", 100, 183, 4);
    tft.setTextColor(TFT_WHITE, HELPER_COLOR_BACKGROUND);
    tft.drawString("N", 125, 183, 4);
    tft.drawString("D", 150, 183, 4);
  }
  else if (HMI__stGearBox.neutral)
  {
    tft.setTextColor(TFT_WHITE, HELPER_COLOR_BACKGROUND);
    tft.drawString("P", 75, 183, 4);
    tft.drawString("R", 100, 183, 4);
    tft.setTextColor(HELPER_COLOR_BACKGROUND, TFT_WHITE);
    tft.drawString("N", 125, 183, 4);
    tft.setTextColor(TFT_WHITE, HELPER_COLOR_BACKGROUND);
    tft.drawString("D", 150, 183, 4);
  }
  else if (HMI__stGearBox.drive)
  {
    tft.setTextColor(TFT_WHITE, HELPER_COLOR_BACKGROUND);
    tft.drawString("P", 75, 183, 4);
    tft.drawString("R", 100, 183, 4);
    tft.drawString("N", 125, 183, 4);
    tft.setTextColor(HELPER_COLOR_BACKGROUND, TFT_WHITE);
    tft.drawString("D", 150, 183, 4);
    tft.setTextColor(TFT_WHITE, HELPER_COLOR_BACKGROUND);
  }
}
void HMI__vDisplaySpeedGear()
{
  CommonData_Get(CommonData_enSpeedData, &HMI__stGetSpeedData);

  if (HMI__stGetSpeedData.u16kmh > 0 && HMI__stGetSpeedData.u16kmh <= 20)
  {
    tft.drawString("1", 170, 183, 2);
  }
  else if (HMI__stGetSpeedData.u16kmh > 20 && HMI__stGetSpeedData.u16kmh <= 40)
  {
    tft.drawString("2", 170, 183, 2);
  }
  else if (HMI__stGetSpeedData.u16kmh > 40 && HMI__stGetSpeedData.u16kmh <= 70)
  {
    tft.drawString("3", 170, 183, 2);
  }
  else if (HMI__stGetSpeedData.u16kmh > 70 && HMI__stGetSpeedData.u16kmh <= 110)
  {
    tft.drawString("4", 170, 183, 2);
  }
  else if (HMI__stGetSpeedData.u16kmh > 110 && HMI__stGetSpeedData.u16kmh <= 150)
  {
    tft.drawString("5", 170, 183, 2);
  }
  else if (HMI__stGetSpeedData.u16kmh > 150)
  {
    tft.drawString("6", 170, 183, 2);
  }

  if (HMI__stGetSpeedData.u16kmh > 180)
  {
    tft.setTextColor(HELPER_COLOR_BACKGROUND, TFT_RED);
    tft.drawString("S", 180, 183, 4);
    tft.setTextColor(TFT_WHITE, HELPER_COLOR_BACKGROUND);
  }
  else
  {
    tft.drawString("    ", 180, 183, 4);
  }
}

unsigned int rainbow(byte value)
{
  // Value is expected to be in range 0-127
  // The value is converted to a spectrum colour from 0 = blue through to 127 = red

  byte red = 0;   // Red is the top 5 bits of a 16 bit colour value
  byte green = 0; // Green is the middle 6 bits
  byte blue = 0;  // Blue is the bottom 5 bits

  byte quadrant = value / 32;

  if (quadrant == 0)
  {
    blue = 31;
    green = 2 * (value % 32);
    red = 0;
  }
  if (quadrant == 1)
  {
    blue = 31 - (value % 32);
    green = 63;
    red = 0;
  }
  if (quadrant == 2)
  {
    blue = 0;
    green = 63;
    red = value % 32;
  }
  if (quadrant == 3)
  {
    blue = 0;
    green = 63 - 2 * (value % 32);
    red = 31;
  }
  return (red << 11) + (green << 5) + blue;
}

// #########################################################################
//  Draw the meter on the screen, returns x coord of righthand side
// #########################################################################
int ringMeter(int value, int vmin, int vmax, int x, int y, int r, char const *units, byte scheme)
{
  // Minimum value of r is about 52 before value text intrudes on ring
  // drawing the text first is an option

  x += r;
  y += r; // Calculate coords of centre of ring

  int w = r / 3.9; // Width of outer ring

  int angle = 150; // Half the sweep angle of meter (300 degrees)

  int text_colour = 0; // To hold the text colour

  int v = map(value, vmin, vmax, -angle, angle); // Map the value to an angle v

  byte seg = 5;  // Segments are 5 degrees wide = 60 segments for 300 degrees
  byte inc = 15; // Draw segments every 5 degrees, increase to 10 for segmented ring

  // Draw colour blocks every inc degrees
  for (int i = -angle; i < angle; i += inc)
  {

    // Choose colour from scheme
    int colour = 0;
    switch (scheme)
    {
    case 0:
      colour = ILI9341_RED;
      break; // Fixed colour
    case 1:
      colour = ILI9341_GREEN;
      break; // Fixed colour
    case 2:
      colour = ILI9341_BLUE;
      break; // Fixed colour
    case 3:
      colour = rainbow(map(i, -angle, angle, 0, 127));
      break; // Full spectrum blue to red
    case 4:
      colour = rainbow(map(i, -angle, angle, 63, 127));
      break; // Green to red (high temperature etc)
    case 5:
      colour = rainbow(map(i, -angle, angle, 127, 63));
      break; // Red to green (low battery etc)
    case 6:
      colour = rainbow(map(i, -angle, angle, 63, 0));
      break; // Green to blue
    case 7:
      colour = rainbow(map(i, -angle, angle, 0, 48));
      break; // Blue to light blue
    default:
      colour = ILI9341_BLUE;
      break; // Fixed colour
    }

    // Calculate pair of coordinates for segment start
    float sx = cos((i - 90) * 0.0174532925);
    float sy = sin((i - 90) * 0.0174532925);
    uint16_t x0 = sx * (r - w) + x;
    uint16_t y0 = sy * (r - w) + y;
    uint16_t x1 = sx * r + x;
    uint16_t y1 = sy * r + y;

    // Calculate pair of coordinates for segment end
    float sx2 = cos((i + seg - 90) * 0.0174532925);
    float sy2 = sin((i + seg - 90) * 0.0174532925);
    int x2 = sx2 * (r - w) + x;
    int y2 = sy2 * (r - w) + y;
    int x3 = sx2 * r + x;
    int y3 = sy2 * r + y;

    if (i < v)
    { // Fill in coloured segments with 2 triangles
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, colour);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, colour);
      text_colour = colour; // Save the last colour drawn
    }
    else // Fill in blank segments
    {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, HELPER_COLOR_SPEED_GAUGE);
      tft.fillTriangle(x1, y1, x2, y2, x3, y3, HELPER_COLOR_SPEED_GAUGE);
    }
  }

  // Convert value to a string
  // char buf[10];
  // byte len = 4; if (value > 999) len = 5;
  // dtostrf(value, len, 0, buf);

  // const char *name = "hello";
  // const char *extension = ".txt";

  // char *name_with_extension;
  // name_with_extension = malloc(strlen(name) + 1 + 4); /* make space for the new string (should check the return value ...) */
  // strcpy(name_with_extension, name);                  /* copy name into the new var */
  // strcat(name_with_extension, extension);             /* add the extension */
  // ... free(name_with_extension);

  // Set the text colour to default
  tft.setTextColor(TFT_WHITE, HELPER_COLOR_BACKGROUND);
  // Uncomment next line to set the text colour to the last segment value!
  // tft.setTextColor(text_colour, ILI9341_BLACK);

  // // Print value, if the meter is large then use big font 6, othewise use 4
  // if (r > 84) tft.drawCentreString(String(value), x - 5, y - 20, 6); // Value in middle
  // else tft.drawString(String(value) + " ", x - 8, y - 20, 4); // Value in middle
  tft.drawCentreString(" " + String(value) + " ", x, y - 20, 6);

  // Print units, if the meter is large then use big font 4, othewise use 2
  tft.setTextColor(TFT_WHITE, HELPER_COLOR_BACKGROUND);
  if (r > 84)
    tft.drawCentreString(units, x, y + 50, 4); // Units display
  else
    tft.drawCentreString(units, x + 3, y + 22, 2); // Units display

  // Calculate and return right hand side x coordinate
  return x + r;
}

// #########################################################################
// Return a value in range -1 to +1 for a given phase angle in degrees
// #########################################################################
float sineWave(int phase)
{
  return sin(phase * 0.0174532925);
}

void HMI_vDrawSpeedGauge()
{
  // Set the the position, gap between meters, and inner radius of the meters
  uint8_t xpos = HMI__SPEED_GAUGE_X, ypos = HMI__SPEED_GAUGE_Y,
          gap = HMI__SPEED_GAUGE_GAP, radius = HMI__SPEED_GAUGE_RADIUS;
  static uint16_t u16previousSpeed = 0;
  static unsigned long HMI__ulSpeedPreviousTime = millis();
  static bool HMI__boSpeedFlag = !HMI__boSpeedFlag;
  EEPROM_ReadData(enSpeedUnit, (byte *)&HMI__u8SpeedUnit);
  CommonData_Get(CommonData_enSpeedData, &HMI__stGetSpeedData);

  // tft.drawCircle(120, 99, 53, HELPER_COLOR_SPEED_GAUGE);

  switch (HMI__u8SpeedUnit)
  {
  case HMI__SPEED_UNIT_1:
    if (HMI__stGetSpeedData.boBlink != true && HMI__stGetSpeedData.u16kmh != u16previousSpeed)
    {
      ringMeter(HMI__stGetSpeedData.u16kmh, 0, HMI__SPEED_MAX_KMH, xpos, ypos, radius, " km/h ", BLUE2LIGHTBLUE); // Draw analogue meter
      u16previousSpeed = HMI__stGetSpeedData.u16kmh;
    }

    else if (HMI__stGetSpeedData.boBlink == true)
    {
      if (millis() - HMI__ulSpeedPreviousTime > HMI__SPEED_BLINK)
      {
        HMI__ulSpeedPreviousTime = millis();
        HMI__boSpeedFlag = !HMI__boSpeedFlag;
      }
      if (HMI__boSpeedFlag)
      {
        ringMeter(HMI__stGetSpeedData.u16kmh, 0, HMI__SPEED_MAX_KMH, xpos, ypos, radius, " km/h ", BLUE2LIGHTBLUE); // Draw analogue meter
      }
      else
      {
        ringMeter(HMI__stGetSpeedData.u16kmh, 0, HMI__SPEED_MAX_KMH, xpos, ypos, radius, " km/h ", RED2RED); // Draw analogue meter
      }
    }
    break;
  case HMI__SPEED_UNIT_2:
    if (HMI__stGetSpeedData.boBlink != true && HMI__stGetSpeedData.u16mph != u16previousSpeed)
    {
      ringMeter(HMI__stGetSpeedData.u16mph, 0, HMI__SPEED_MAX_MPH, xpos, ypos, radius, " m/h ", BLUE2LIGHTBLUE); // Draw analogue meter
      u16previousSpeed = HMI__stGetSpeedData.u16mph;
    }

    else if (HMI__stGetSpeedData.boBlink == true)
    {
      if (millis() - HMI__ulSpeedPreviousTime > HMI__SPEED_BLINK)
      {
        HMI__ulSpeedPreviousTime = millis();
        HMI__boSpeedFlag = !HMI__boSpeedFlag;
      }
      if (HMI__boSpeedFlag)
      {
        ringMeter(HMI__stGetSpeedData.u16mph, 0, HMI__SPEED_MAX_MPH, xpos, ypos, radius, " m/h ", BLUE2LIGHTBLUE); // Draw analogue meter
      }
      else
      {
        ringMeter(HMI__stGetSpeedData.u16mph, 0, HMI__SPEED_MAX_MPH, xpos, ypos, radius, " m/h ", RED2RED); // Draw analogue meter
      }
    }
    break;
  default:
    // do nothing
    break;
  }
}
void HMI_vDrawIndications()
{
  bool HMI__bLowBat;
  bool HMI__bInd1;
  bool HMI__bInd2;
  CommonData_Get(CommonData_enLowBattery, &HMI__bLowBat);
  CommonData_Get(CommonData_enIndication1, &HMI__bInd1);
  CommonData_Get(CommonData_enIndication2, &HMI__bInd2);
  CommonData_Get(CommonData_enDoorsState, &HMI__stGetDoorsData);
  if (HMI__bLowBat)
  {
    HMI__Helper.drawImage(tft, "/telltales/low_battery_on.jpg", 100, 100);
  }
  else
  {
    HMI__Helper.drawImage(tft, "/telltales/empty_icon.jpg", 120, 160);
  }

  if (HMI__bInd1 && !HMI__bLowBat && !HMI__bInd2)
  {
    HMI__vDisplaySpeedGear();
    HMI__vChangeGear();
    HMI_vDrawSpeedGauge();
  }
  if(HMI__bInd2)
  {
    HMI__vDisplayDoorOpenWhileSpeeding();
  }
}