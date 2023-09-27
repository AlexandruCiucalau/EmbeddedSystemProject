#include "Arduino.h"

#ifndef LightsE_h
#define LightsE_h

static struct Lights_stData
{
    uint8_t u8LowBeam = 0;
    uint8_t u8HighBeam = 0;
    uint8_t u8FogLights = 0;
} stLightsData;

void Lights_Setup();
void Lights_Loop();

#endif