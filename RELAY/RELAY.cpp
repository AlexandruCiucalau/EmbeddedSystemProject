#include "Arduino.h"
#include "RELAYE.h"
#include "RELAYI.h"
#include "CommonDataE.h"

void RELAY_Setup()
{
  pinMode(RELAY__PIN1, OUTPUT);
  pinMode(RELAY__PIN2, OUTPUT);

  digitalWrite(RELAY__PIN1, HIGH);
  digitalWrite(RELAY__PIN2, HIGH);
}

// functions to trigger the relays on and off
void RELAY1_TriggerON()
{
  digitalWrite(RELAY__PIN1, LOW);
  stRelayData.boRelay1State = true;
}

void RELAY2_TriggerON()
{
  digitalWrite(RELAY__PIN2, LOW);
  stRelayData.boRelay2State = true;
}

void RELAY1_TriggerOFF()
{
  digitalWrite(RELAY__PIN1, HIGH);
  stRelayData.boRelay1State = false;
}

void RELAY2_TriggerOFF()
{
  digitalWrite(RELAY__PIN2, HIGH);
  stRelayData.boRelay2State = false;
}

// function to set the state of first relay
void RELAY1_SetState(bool state)
{
  if (state == true)
  {
    RELAY1_TriggerON();
    stRelayData.boRelay1State = true;
  }
  else
  {
    RELAY1_TriggerOFF();
    stRelayData.boRelay1State = false;
  }
  CommonData_Set(CommonData_enRelayData, &stRelayData);
}

// function to set the state of second relay
void RELAY2_SetState(bool state)
{
  if (state == true)
  {
    RELAY2_TriggerON();
    stRelayData.boRelay2State = true;
  }
  else
  {
    RELAY2_TriggerOFF();
    stRelayData.boRelay2State = false;
  }
  CommonData_Set(CommonData_enRelayData, &stRelayData);
}

// function to blink the first relay
// for a given frequency
void RELAY1_Blink(unsigned long freq)
{
  stRelayData.ulFreq = freq;
  RELAY__ulDuration = freq / 2; // on duration, off duration
#ifdef RELAY_DEBUG
  Serial.println(stRelayData.ulFreq);
#endif
  if (millis() - RELAY__ulRemembertime >= RELAY__ulDuration)
  {
    RELAY__ulRemembertime = millis(); // save previous time
    RELAY__boFlag = !RELAY__boFlag;   // inverse the flag

#ifdef RELAY_DEBUG
    Serial.print("Current Time : ");
    Serial.println(millis());
    Serial.print("Remember Time : ");
    Serial.println(RELAY__ulRemembertime);
#endif
  }

  if (RELAY__boFlag)
  {
    // x seconds on
    RELAY1_TriggerON();
    stRelayData.boRelay1State = true;
  }
  else
  {
    // x seconds off
    RELAY1_TriggerOFF();
    stRelayData.boRelay1State = false;
  }
}