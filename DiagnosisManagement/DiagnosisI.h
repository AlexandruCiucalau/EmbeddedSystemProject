#include "Arduino.h"
#ifndef DiagnosisI_h
#define DiagnosisI_h

#define DIAG__USER_DELAY 150000

uint8_t DIAG__u8CelsiusOption = 1;
uint8_t DIAG__u8FahrenheitOption = 2;
uint8_t DIAG__u8FullDay = 24;
uint8_t DIAG__u8HalfDay = 12;
uint8_t DIAG__u8Kmh = 1;
uint8_t DIAG__u8Mph = 2;
//````````````````````````````````````````````````````````````````````````````
static byte DIAG__byCounter = 0;
boolean DIAG__bNewData = false;
char DIAG__cEndMarker = '\n';
char DIAG__cUserInput;
const byte DIAG__byNumChars = 32;
//````````````````````````````````````````````````````````````````````````````
unsigned long DIAG__ulPreviousMillis = 0;
#endif