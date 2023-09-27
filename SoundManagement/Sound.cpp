#include "Arduino.h"
#include "ShiftE.h"
#include "SoundE.h"
#include "SoundI.h"
#include "CommonDataE.h"
#include "TempE.h"
void Sound_vsetBuzzerA()
{
    bool bStatusA;
    bool SND_bLowBat;
    CommonData_Get(CommonData_enBuzzerA, &bStatusA);
    CommonData_Get(CommonData_enLowBattery, &SND_bLowBat);
    if(SND_bLowBat)
    {
    if(SND__u8CounterA == 2)
        {
            SND__u8CounterA = 0;
        }
        unsigned long currentMillisA = millis();
        if (millis() - SND__previousMillisA >= 1500)
        {
            SND__previousMillisA = millis();
          //  SHIFT__vSetBuzz(bStatusA);
            SHIFT__vSetHWTT1(bStatusA);
            bStatusA = !bStatusA;
            SND__u8CounterA++;
        }
        if(SND__u8CounterA <= 1 && SND__u8CounterA != 0)
        {
            CommonData_Set(CommonData_enBuzzerA, &bStatusA);
        }
        if(SND__u8CounterA == 0)
        {
            SHIFT__vSetBuzz(false);
            SHIFT__vSetHWTT1(false);
        }
    }else
    {
        SHIFT__vSetBuzz(false);
        SHIFT__vSetHWTT1(false);
        SND__u8CounterA = 0;
    }
}

void Sound_vsetBuzzerB()
{
    bool bStatusB;
    bool SND__Indication;
    CommonData_Get(CommonData_enBuzzerB, &bStatusB);
    CommonData_Get(CommonData_enIndication1, &SND__Indication);
    if(SND__Indication)
    {
    if(SND__u8CounterB == 6)
        {
            SND__u8CounterB = 0;
        }
        if(millis() - SND__previousMillisB >= 3000)
        {
            SND__previousMillisB = millis();
           // SHIFT__vSetBuzz(bStatusB);
            SHIFT__vSetHWTT2(bStatusB);
            bStatusB = !bStatusB;
            SND__u8CounterB++;
        }
        if(SND__u8CounterB <= 5 && SND__u8CounterB != 0)
        {
            CommonData_Set(CommonData_enBuzzerB, &bStatusB);
        }
        if(SND__u8CounterB == 0)
        {
            SHIFT__vSetBuzz(false);
            SHIFT__vSetHWTT2(false);
        }
    }else
    {
        SHIFT__vSetBuzz(false);
        SHIFT__vSetHWTT2(false);
        SND__u8CounterB = 0;
    }
}
void Sound_vsetBuzzerC()
{
    bool bStatusC;
    bool SND__bIndication;
    CommonData_Get(CommonData_enBuzzerC, &bStatusC);
    CommonData_Get(CommonData_enIndication2, &SND__bIndication);
    if(SND__bIndication)
    {
    if(SND__u8CounterC == 6)
        {
            SND__u8CounterC = 0;
        }
        if(millis()-SND__previousMillisC >= 1500)
        {
            SND__previousMillisC = millis();
           // SHIFT__vSetBuzz(bStatusC);
            SHIFT__vSetHWTT3(bStatusC);
            bStatusC = !bStatusC;
            SND__u8CounterC++;
        }
        if(SND__u8CounterC<=5 && SND__u8CounterC != 0)
        {
            CommonData_Set(CommonData_enBuzzerC, &bStatusC);
        }
        if(SND__u8CounterC == 0)
        {
            SHIFT__vSetBuzz(false);
            SHIFT__vSetHWTT3(false);
        }
    }else
    {
       SHIFT__vSetBuzz(false); 
       SHIFT__vSetHWTT3(false);
       SND__u8CounterC = 0;
    }
}
void Sound_vsetBuzzerD()
{
  // SHIFT__vSetBuzz(1);
  // wait(2000);
  // SHIFT__vSetBuzz(0);
  //     wait(2000);
  // SHIFT__vSetBuzz(1);
  //     wait(2000);
  // SHIFT__vSetBuzz(0);
  //     wait(2000);
  // SHIFT__vSetBuzz(1);
  //     wait(2000);
  // SHIFT__vSetBuzz(0);

   // CommonData_Set(CommonData_enBuzzerD, &flagD);
}
