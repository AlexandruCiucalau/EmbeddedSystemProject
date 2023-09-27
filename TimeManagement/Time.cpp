#include "Arduino.h"
#include "TimeE.h"
#include "TimeI.h"
#include "EEPROME.h"
#include "CommonDataE.h"

void Time_vSetup()
{
}
uint8_t Time_vGetMinutes()
{
    EEPROM_ReadData(enTime, (byte *)&timeStclock);
    return timeStclock.minutes;
}
uint8_t Time_vGetSeconds()
{
    EEPROM_ReadData(enTime, (byte *)&timeStclock);
    return timeStclock.seconds;
}
uint8_t Time_vGetHours()
{
    EEPROM_ReadData(enTime, (byte *)&timeStclock);
    return timeStclock.hours;
}

// depending on the parameter "format", 1-means 24h, 2-means12h
void Time_vChangeUnit(bool format)
{
    uint8_t Time__u8Format;
    if (format)
    {
        Time__u8Format = 24;
        EEPROM_WriteData(enTimeFormat, &Time__u8Format);
    }
    else
    {
        Time__u8Format = 12;
        EEPROM_WriteData(enTimeFormat, &Time__u8Format);
    }
}

void Time_vSendTimeToHMI()
{
    uint8_t flag = 0;
    uint8_t timeFormat;
    String Time__secunde = "";
    String Time__minute = "";
    String Time__oreDouazeciSiPatru = "";
    String Time__oreDoiSpreZece = "";
    String Time__ExtraZero = "0";
    EEPROM_ReadData(enTime, (byte *)&timeStclock);
    EEPROM_ReadData(enTimeFormat, (byte *)&timeFormat);
    if (millis() >= Time__previousMillisSeconds)
    {
        timeStclock.seconds++;
        Time__previousMillisSeconds += 1000;
    }
    timeStclock.seconds %= 60;

    if (timeStclock.seconds == 0 && Time__okMinutes)
    {
        timeStclock.minutes++;
        Time__okMinutes = 0;
    }
    timeStclock.minutes %= 60;

    if (timeStclock.seconds == 1)
    {
        Time__okMinutes = 1;
    }
    if (timeStclock.minutes % 60 == 0 && Time__okHours)
    {
        timeStclock.hours++;
        Time__okHours = 0;
        flag += 1;
    }
    timeStclock.hours %= 24;
    if (timeStclock.minutes == 2)
    {
        Time__okHours = 1;
    }
    //````````````````````````````````````````````````````````````````````
    if (timeStclock.seconds < 10)
    {
        Time__secunde += Time__ExtraZero;
        Time__secunde += timeStclock.seconds;
    }
    else
    {
        Time__secunde += timeStclock.seconds;
    }
    if (timeStclock.minutes < 10)
    {
        Time__minute += Time__ExtraZero;
        Time__minute += timeStclock.minutes;
    }
    else
    {
        Time__minute += timeStclock.minutes;
    }
    if (timeStclock.hours % 12 < 10)
    {
        Time__oreDoiSpreZece += Time__ExtraZero;
        Time__oreDoiSpreZece += timeStclock.hours % 12;
    }
    else
    {
        Time__oreDoiSpreZece += timeStclock.hours % 12;
    }

    if (timeStclock.hours % 24 < 10)
    {
        Time__oreDouazeciSiPatru += Time__ExtraZero;
        Time__oreDouazeciSiPatru += timeStclock.hours % 24;
    }
    else
    {
        Time__oreDouazeciSiPatru += timeStclock.hours % 24;
    }
    // form the string for HMI
    stTimeDetails.strTimeString = "";
    stTimeDetails.strTimeString += Time__oreDouazeciSiPatru;
    stTimeDetails.strTimeString += " ";
    stTimeDetails.strTimeString += ":";
    stTimeDetails.strTimeString += " ";
    stTimeDetails.strTimeString += Time__minute;
    // secondary string for smaller font in HMI
    stTimeDetails.strTimeStringSmall = "";
    stTimeDetails.strTimeStringSmall += Time__oreDoiSpreZece;
    stTimeDetails.strTimeStringSmall += " ";
    stTimeDetails.strTimeStringSmall += ":";
    stTimeDetails.strTimeStringSmall += " ";
    stTimeDetails.strTimeStringSmall += Time__minute;
    // store in EEPROM last hours, minutes & seconds
    EEPROM_WriteData(enTime, (byte *)&timeStclock);
    // pass the string through common data
    CommonData_Set(CommonData_enTimeDetails, &stTimeDetails);
}