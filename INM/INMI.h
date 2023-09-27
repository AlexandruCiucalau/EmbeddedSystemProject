#ifndef INMI_h
#define INMI_h
#include "MUXE.h"

#define INM_SIZE 8
#define INM_SW1 0
#define INM_SW2 1
#define INM_SW3 2
#define INM_SW4 3
#define INM_KEY1 4
#define INM_KEY2 5
#define INM_KEY3 6
#define INM_KEY4 7

static MUX_unInputs INM_unMuxValues;

bool INM__boInputState;            // the current reading from the input pin
bool INM__boLastInputState = 0;  // the previous reading from the input pin

unsigned long INM__ulDebounceDelay = 50;    // the debounce time; increase if the output flickers

#endif