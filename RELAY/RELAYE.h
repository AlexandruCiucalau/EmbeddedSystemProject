#ifndef RELAYE_h
#define RELAYE_h

#include "Arduino.h"

static struct Relay_stData {
    bool boRelay1State;
    bool boRelay2State;
    unsigned long ulTimer;
    unsigned long ulFreq;
} stRelayData;

void RELAY_Setup();
void RELAY1_TriggerON();
void RELAY2_TriggerON();
void RELAY1_TriggerOFF();
void RELAY2_TriggerOFF();
void RELAY1_SetState(bool);
void RELAY2_SetState(bool);
void RELAY1_Blink(unsigned long);

#endif