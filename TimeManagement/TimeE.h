#include "Arduino.h"
#ifndef TimeE_h
#define TimeE_h

static struct stSendTime
{
    uint8_t seconds : 6;
    uint8_t minutes : 6;
    uint8_t hours : 5;
} timeStclock;

static struct Time_Details
{
    String strTimeString = "";
    String strTimeStringSmall = "";
} stTimeDetails;

void Time_vSetup();
uint8_t Time_vGetSeconds();
uint8_t Time_vGetMinutes();
uint8_t Time_vGetHours();
void Time_vChangeUnit(bool format);
void Time_vSendTimeToHMI();

#endif