#include "Arduino.h"

#ifndef DoorsE_h
#define DoorsE_h

static struct Doors_stData {
    bool boFrontLeftDoor = 0;
    bool boFrontRightDoor = 0;
    bool boRearLeftDoor = 0;
    bool boRearRightDoor = 0;
} stDoorsData;

void Doors_Setup();
void Doors_Loop();
bool Doors_boClosed();

#endif