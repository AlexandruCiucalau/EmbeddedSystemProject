#ifndef StateMachineI_h
#define StateMachineI_h

#include "Arduino.h"
#include "StateMachineE.h"
#include "SpeedE.h"
#include "DoorsE.h"

#define STM__nWELCOME_SCREEN_TIME 30 // 70 * 100ms = 7000 ms

#define STM__nStoMS 1000
#define STM__nCycleTime 100
#define STM__SPEED_LOWER_LIMIT 3

Speed_stData stGetSpeedData;

#endif