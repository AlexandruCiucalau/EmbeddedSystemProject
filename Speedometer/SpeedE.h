#include "Arduino.h"

#ifndef SpeedE_h
#define SpeedE_h

#define SPEED_TH1 160
#define SPEED_TH2 155
#define SPEED_TH3 150
#define SPEED_THRESHOLD 5
#define SPEED_UNIT_KMH 1
#define SPEED_UNIT_MPH 2

static struct Speed_stData
{
    uint16_t u16kmh;
    uint16_t u16mph;
    bool boBlink;
} stSpeedData;

void Speed_Setup();

void Speed_Loop();

#endif