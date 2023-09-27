#include "Arduino.h"

#ifndef INME_h
#define INME_h

static struct INM_stInputs {
    bool stSW1;
    bool stSW2;
    bool stSW3;
    bool stSW4;
    bool stKEY1;
    bool stKEY2;
    bool stKEY3;
    bool stKEY4;
    bool stJMP2;
    bool stJMP1;
    bool stJMP3;
} stInmValues;

void INM_Debounce(uint8_t, uint8_t);
void INM_Loop();

#endif