#include "Arduino.h"
#include "ShiftI.h"
#include "ShiftE.h"
#include "CommonDataE.h"
 enShiftReg enShiftRegister; 
//`````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````
void SHIFT_vSetupp()
{
   pinMode(SHIFT__LATCHPIN, OUTPUT);
   pinMode(SHIFT__CLOCKPIN, OUTPUT);
   pinMode(SHIFT__DATAPINN, OUTPUT);
   pinMode(SHIFT__OEPIN, OUTPUT);
   digitalWrite(SHIFT__OEPIN, LOW);
}
//````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````
void SHIFT_vShiftOut(uint8_t dPin, uint8_t cPin, uint8_t bOrder, uint8_t valSHIFT_auxForShiftValue)
{
   uint8_t i;
   digitalWrite(SHIFT__LATCHPIN, LOW);
   for (i = 0; i < 8; i++)
   {
      if (bOrder == LSBFIRST)
         digitalWrite(dPin, !!(valSHIFT_auxForShiftValue & (1 << i)));
      else
         digitalWrite(dPin, !!(valSHIFT_auxForShiftValue & (1 << (7 - i))));

      digitalWrite(cPin, HIGH);
      digitalWrite(cPin, LOW);
   }
   digitalWrite(SHIFT__LATCHPIN, HIGH);
}
//````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````
void SHIFT__vSetHWTT1(bool SHIFT__isHWTTon)
{
   CommonData_Set(CommonData_enShiftHWTT1, &SHIFT__isHWTTon);
}
void SHIFT__vSetHWTT2(bool SHIFT__isHWTTon)
{
   CommonData_Set(CommonData_enShiftHWTT2, &SHIFT__isHWTTon);
}
void SHIFT__vSetHWTT3(bool SHIFT__isHWTTon)
{
   CommonData_Set(CommonData_enShiftHWTT3, &SHIFT__isHWTTon);
}
void SHIFT__vSetBarGraphLVL(uint8_t SHIFT__lvl)
{
   CommonData_Set(CommonData_enShiftBargraphLVL, &SHIFT__lvl);
}
void SHIFT__vSetBuzz(bool isBuzzerOn)
{
   CommonData_Set(CommonData_enShiftBuzzer, &isBuzzerOn);
}
//`````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````
bool SHIFT__vGetHWTT3()
{
   bool SHIFT__isHWTT3on;
   CommonData_Get(CommonData_enShiftHWTT3, &SHIFT__isHWTT3on);
   return SHIFT__isHWTT3on;
}
bool SHIFT__vGetHWTT2()
{
   bool SHIFT__isHWTT2on;
   CommonData_Get(CommonData_enShiftHWTT2, &SHIFT__isHWTT2on);
   return SHIFT__isHWTT2on;
}
bool SHIFT__vGetHWTT1()
{
   bool SHIFT__isHWTT1on;
   CommonData_Get(CommonData_enShiftHWTT1, &SHIFT__isHWTT1on);
   return SHIFT__isHWTT1on;
}
uint8_t SHIFT__vGetBarGraphLVL()
{
   uint8_t SHIFT__lvlGet;
   CommonData_Get(CommonData_enShiftBargraphLVL, &SHIFT__lvlGet);
   return SHIFT__lvlGet;
}
bool SHIFT__vGetBuzzBit()
{
   uint8_t SHIFT__BuzzBit;
   CommonData_Get(CommonData_enShiftBuzzer, &SHIFT__BuzzBit);
   return SHIFT__BuzzBit;
}
//````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````
void SHIFT_vUpdateShiftRegister()
{
   uint8_t SHIFT_BarGraphLVL;
   uint8_t SHIFT_auxForShiftValue;
   uint8_t SHIFT_auxForHWTT;
   uint8_t SHIFT_auxForBuzzer;
   static uint8_t u8ShiftRegValueOld = 1;

   CommonData_Get(CommonData_enShiftHWTT1, &SHIFT_auxForHWTT);
   if(SHIFT_auxForHWTT)
   {
      SHIFT_auxForShiftValue |= enHWTT_1;
   }else
   {
      SHIFT_auxForShiftValue &= 199; // 199 = 1011.1111
   }
   CommonData_Get(CommonData_enShiftHWTT2, &SHIFT_auxForHWTT);
   if(SHIFT_auxForHWTT)
   {
      SHIFT_auxForShiftValue |= enHWTT_2;
   }else
   {
      SHIFT_auxForShiftValue &= 223; // 223 = 1101.1111
   }
   CommonData_Get(CommonData_enShiftHWTT3, &SHIFT_auxForHWTT);
   if(SHIFT_auxForHWTT)
   {
      SHIFT_auxForShiftValue |= enHWTT_3;
   }else
   {
      SHIFT_auxForShiftValue &= 239; // 239 = 1110.1111
   } 
   CommonData_Get(CommonData_enShiftBuzzer, &SHIFT_auxForBuzzer);
   if(SHIFT_auxForBuzzer)
   {
      SHIFT_auxForShiftValue |= enBuzzer;
   }else
   {
      SHIFT_auxForShiftValue &= 127; // 127 = 0111.1111
   } 

   CommonData_Get(CommonData_enShiftBargraphLVL, &SHIFT_BarGraphLVL);

   switch (SHIFT_BarGraphLVL)
   {
   case 1: //lvl0
      SHIFT_auxForShiftValue = SHIFT_auxForShiftValue | 8; // 8 = 0000.1000
      break;
   case 2:
      SHIFT_auxForShiftValue = SHIFT_auxForShiftValue | 12; // 12 = 0000.1100
      break;
   case 3:
      SHIFT_auxForShiftValue = SHIFT_auxForShiftValue | 14; // 14 = 0000.1110 
      break;
   case 4:
      SHIFT_auxForShiftValue = SHIFT_auxForShiftValue | 15; // 15 = 0000.1111
      break;
   default:
      SHIFT_auxForShiftValue = SHIFT_auxForShiftValue & 240; // 240 = 1111.0000
      break;
   }

   SHIFT__u8ShiftRegValue = SHIFT_auxForShiftValue;

   if(SHIFT__u8ShiftRegValue != u8ShiftRegValueOld)
   {
      u8ShiftRegValueOld = SHIFT__u8ShiftRegValue;
      SHIFT_vShiftOut(SHIFT__DATAPINN, SHIFT__CLOCKPIN, LSBFIRST, SHIFT__u8ShiftRegValue);
   }
}
