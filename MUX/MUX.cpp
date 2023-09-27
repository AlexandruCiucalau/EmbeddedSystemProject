#include "Arduino.h"
#include "MUXE.h"
#include "MUXI.h"
#include "CommonDataE.h"
#include "RELAYE.h"
// #define MUX_DEBUG

void MUX_Setup()
{
  pinMode(MUX__COM, INPUT);
  pinMode(MUX__EN, OUTPUT);
  pinMode(MUX__S0, OUTPUT);
  pinMode(MUX__S1, OUTPUT);
  pinMode(MUX__S2, OUTPUT);
  pinMode(MUX__S3, OUTPUT);

  digitalWrite(MUX__EN, LOW);
  digitalWrite(MUX__S0, LOW);
  digitalWrite(MUX__S1, LOW);
  digitalWrite(MUX__S2, LOW);
  digitalWrite(MUX__S3, LOW);
}

void MUX_Loop()
{
  // initialize the control variable on 0 for correct functionality
  unMuxInputs.u16input = 0;
  // control variable copy to not suffocate common data
  // static uint16_t u16oldValue = 0;
  // loop through all the channels
  for (uint8_t u8Ch = 0; u8Ch < MUX__LENGTH; u8Ch++)
  {
    digitalWrite(MUX__S0, u8Ch & MUX__MASK0);
    digitalWrite(MUX__S1, u8Ch & MUX__MASK1);
    digitalWrite(MUX__S2, u8Ch & MUX__MASK2);
    digitalWrite(MUX__S3, u8Ch & MUX__MASK3);

    // read & store the input
    unMuxInputs.u16input |= (!digitalRead(MUX__COM) << u8Ch);
  }

  CommonData_Set(CommonData_enMuxValues, &unMuxInputs);
  // send new readings only if a change occurs
  // if (unMuxInputs.u16input != u16oldValue)
  // {
  //   CommonData_Set(CommonData_enMuxValues, &unMuxInputs);
  //   u16oldValue = unMuxInputs.u16input;
  // }
#ifdef MUX_DEBUG
  Serial.println(unMuxInputs.u16input);
  Serial.print(unMuxInputs.stMuxInputs.stSwitchKey1);
  Serial.print(unMuxInputs.stMuxInputs.stSwitchKey2);
  Serial.print(unMuxInputs.stMuxInputs.stSwitchKey3);
  Serial.print(unMuxInputs.stMuxInputs.stSwitchKey4);
  Serial.print(unMuxInputs.stMuxInputs.stKey1);
  Serial.print(unMuxInputs.stMuxInputs.stKey2);
  Serial.print(unMuxInputs.stMuxInputs.stKey3);
  Serial.println(unMuxInputs.stMuxInputs.stKey4);
  vTaskDelay(MUX__DELAY / portTICK_PERIOD_MS);
#endif
}

/*  INPUTS channel mapping:
MUX0: Menu Button LEFT
MUX1: Menu Button RIGHT
MUX2: Menu Button OK
MUX3: Menu Button DOWN
MUX4: Menu Button UP
MUX5: SW1 (used for DOORS)
MUX6: SW2 (used for DOORS)
MUX7: SW3 (used for DOORS)
MUX8: SW4 (used for DOORS)
MUX9: KEY1 (used to activate Low Beam)
MUX10: KEY2 (used to activate High Beam)
MUX11: KEY3 (used to activate Fog Lights)
MUX12: KEY4 (used to navigate in HMI/Menu)
MUX13: JMP2 (used to activate Indication 2)
MUX14: JMP1 (used to activate Indication 1)
MUX15: JMP3 (used to activate Indication 3) */
