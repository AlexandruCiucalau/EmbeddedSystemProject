#include "Arduino.h"
#ifndef TimeI_h
#define TimeI_h
static uint8_t Time__Seconds=0;
static uint8_t Time__Minutes=0;
static uint8_t Time__Hours=0;
String Time__StringToDisplay;
unsigned long Time__previousMillisMinutes=0;
unsigned long Time__previousMillisHours=0;
static unsigned long Time__previousMillisSeconds=0;
static bool Time__okMinutes=1;
static bool Time__okHours=1;
#endif