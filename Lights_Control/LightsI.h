#ifndef LightsI_h
#define LightsI_h
#include "INME.h"
#include "RELAYE.h"

#define LIGHTS__LOW_BEAM 0
#define LIGHTS__HIGH_BEAM 1
#define LIGHTS__FOG_LIGHTS 2

#define LIGHTS__LOW_BEAM_ON 1
#define LIGHTS__LOW_BEAM_OFF 0
#define LIGHTS__HIGH_BEAM_ON 1
#define LIGHTS__HIGH_BEAM_OFF 0
#define LIGHTS__FOG_LIGHTS_ON 1
#define LIGHTS__FOG_LIGHTS_OFF 0
#define LIGHTS__SIZE 3

static uint8_t Lights__u8buttonState[LIGHTS__SIZE] = {0, 0, 0};
static uint8_t Lights__u8lastButtonState[LIGHTS__SIZE] = {0, 0, 0};

INM_stInputs Lights__stGetINMValues;

#endif