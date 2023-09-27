/***************************************************************************
 *=====================      Copyright by novartsoft.com      ===============
 ****************************************************************************
 * Title        : EEPROME.h
 *
 * Description  : This module is responsable of EEPROM writing
 *
 * Environment  : ESP32
 *
 * Responsible  : Catalin Gyorgy
 *
 * History:
 * 12.06.2021    CatGyo  Initial revision
 */
#ifndef EEPROME_h
#define EEPROME_h

#include "Arduino.h"

enum EEPROM_enDataIDs
{
  enTimeFormat,
  enTime,
  enSpeedUnit,
  enTempFormat,
  enWiFiSSID,
  enWiFiPassword,
  enMaxEEPROM
};

// void EEPROM_ReadPhrase(uint32_t);
// void EEPROM_WritePhrase(int, String);
void EEPROM_ReadData(EEPROM_enDataIDs, byte *p_data);
void EEPROM_WriteData(EEPROM_enDataIDs, byte *p_data);
void EEPROM_Setup();
#endif