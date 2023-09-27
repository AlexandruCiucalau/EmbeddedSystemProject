#ifndef MUXE_h
#define MUXE_h

#include "Arduino.h"

void MUX_Setup();
void MUX_Loop();

// struct with bitfield for all inputs
struct MUX_stInputs {
    uint8_t stMenuButtonLeft : 1;
    uint8_t stMenuButtonRight : 1;
    uint8_t stMenuButtonUp : 1;
    uint8_t stMenuButtonOk : 1;
    uint8_t stMenuButtonDown : 1;
    uint8_t stSwitchKey1 : 1;
    uint8_t stSwitchKey2 : 1;
    uint8_t stSwitchKey3 : 1;
    uint8_t stSwitchKey4 : 1;
    uint8_t stKey1 : 1;
    uint8_t stKey2 : 1;
    uint8_t stKey3 : 1;
    uint8_t stKey4 : 1;
    uint8_t stJumper2 : 1;
    uint8_t stJumper1 : 1;
    uint8_t stJumper3 : 1;
};

// union to store the inputs & the control var. at the same location in memory
union MUX_unInputs {
    MUX_stInputs stMuxInputs;
    uint16_t u16input;  // variable for control
};

#endif