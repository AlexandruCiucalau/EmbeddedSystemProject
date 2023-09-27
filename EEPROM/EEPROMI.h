/***************************************************************************
 *=====================      Copyright by novartsoft.com      ===============
 ****************************************************************************
 * Title        : EEPROMI.h
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
#ifndef EEPROMI_h
#define EEPROMI_h
#include "TimeE.h"
#include "WiFiE.h"

#define EEPROM_MAX_WIFI_SSID 4
#define EEPROM_MAX_WIFI_PASS 4

const int EEPROM__Sizes[enMaxEEPROM] = {sizeof(uint8_t), sizeof(stSendTime), sizeof(uint8_t),
                                        sizeof(uint8_t), EEPROM_MAX_WIFI_SSID, EEPROM_MAX_WIFI_PASS};

const int EEPROM_StartAddresses[enMaxEEPROM] = {0x01, 0x02, 0x05, 0x06, 0x07, 0x11}; // uint8_t -> 1 byte

#define EEPROM__EEPROM_Size 60
#define EEPROM__EEPROM_StartAddress 0x00

#endif