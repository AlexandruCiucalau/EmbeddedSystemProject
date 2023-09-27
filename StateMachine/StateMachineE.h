#ifndef StateMachineE_h
#define StateMachineE_h

#include "Arduino.h"

enum STM_States
{
  enInit = 0,
  enWelcomeScreen,
  enHomeScreen,
  enDoorsScreen,
  enSpeedScreen,
  enIndicationScreen,
  enMaxID
};

const String STM_StateHumanNames[enMaxID] =
    {
        "Init",
        "Loading",
        "HomeScreen",
        "DoorsScreen",
        "SpeedScreen"};

void STM_Setup();
void STM_LOOP();
void STM_setReadingCreditState(bool);
void STM_setNextState(STM_States);

#endif