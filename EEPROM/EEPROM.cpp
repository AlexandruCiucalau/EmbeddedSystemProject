/***************************************************************************
 *=====================      Copyright by novartsoft.com      ===============
 ****************************************************************************
 * Title        : EEPROM.cpp
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
#include "EEPROME.h"
#include "EEPROMI.h"
#include <EEPROM.h>

static byte EEPROM__Shadow[EEPROM__EEPROM_Size];

void EEPROM_Setup()
{
  EEPROM.begin(EEPROM__EEPROM_Size);
  for (byte i = 0; i < EEPROM__EEPROM_Size; i++)
  {
    EEPROM__Shadow[i] = EEPROM.read(i);
  }
}

void EEPROM_ReadData(EEPROM_enDataIDs ID, byte *p_data)
{
  memcpy(p_data, (&EEPROM__Shadow[EEPROM__EEPROM_StartAddress] + EEPROM_StartAddresses[ID]), EEPROM__Sizes[ID]);
}

void EEPROM_WriteData(EEPROM_enDataIDs ID, byte *p_data)
{
  memcpy((byte *)(&EEPROM__Shadow[EEPROM__EEPROM_StartAddress] + EEPROM_StartAddresses[ID]), p_data, EEPROM__Sizes[ID]);
  for (byte i = EEPROM_StartAddresses[ID]; i < (EEPROM_StartAddresses[ID] + EEPROM__Sizes[ID]); i++)
  {
    EEPROM.write(i,EEPROM__Shadow[i]);
  }
  EEPROM.commit();
}

// String EEPROM_ReadPhrase(uint32_t u32address)
// {
//   String strPhrase;
//   uint32_t u32iterator = u32address;
//   char chReadChar;

//   while(chReadChar != '\0')
//   {
//     chReadChar = char(EEPROM.read(u32iterator));
//     u32iterator++;
//     if(chReadChar != '\0')
//     {
//       strPhrase += chReadChar;
//     }
//   }

//   return strPhrase;
// }

// void EEPROM_WritePhrase(uint32_t u32address, String strPhrase)
// {
//   uint32_t u32strLength = strPhrase.length() + 1;

//   for (uint32_t i = u32address; i < u32strLength + u32address; i++)
//   {
//     EEPROM.write(i, strPhrase.charAt(i - u32address));
//   }

//   EEPROM.write(u32strLength + u32address, '\0');
//   EEPROM.commit();
// }