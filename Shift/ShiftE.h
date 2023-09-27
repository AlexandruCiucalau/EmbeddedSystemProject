#ifndef ShiftE_h
#define ShiftE_h
void SHIFT_vShiftOut(uint8_t dPin, uint8_t cPin, uint8_t bOrder, uint8_t valAux );
void SHIFT_vUpdateShiftRegister();
void SHIFT_vSetupp();
enum enShiftReg {
   enLVL_3 = 1,
   enLVL_2 = 2,
   enLVL_1 = 4,
   enLVL_0 = 8,
   enHWTT_3 =16,
   enHWTT_2 = 32,
   enHWTT_1 = 64,
   enBuzzer = 128
};
//Functions to set value for shift register
void SHIFT__vSetBarGraphLVL(uint8_t SHIFT__lvl);
void SHIFT__vSetHWTT1(bool SHIFT__isHWTTon);
void SHIFT__vSetHWTT2(bool SHIFT__isHWTTon);
void SHIFT__vSetHWTT3(bool SHIFT__isHWTTon);
void SHIFT__vSetBuzz(bool isBuzzerOn);
//Functions to get value for shift register
bool SHIFT__vGetHWTT1();
bool SHIFT__vGetHWTT2();
bool SHIFT__vGetHWTT3();
uint8_t SHIFT__vGetBarGraphLVL();
bool SHIFT__vGetBuzzBit();
#endif