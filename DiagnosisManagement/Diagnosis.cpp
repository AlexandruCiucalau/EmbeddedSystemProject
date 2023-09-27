#include "Arduino.h"
#include "DiagnosisE.h"
#include "DiagnosisI.h"
#include "EEPROME.h"
char DIAG__cReceivedChars[DIAG__byNumChars];
/*this function works as follow:
0101->Change TEMP to CELSIUS
0102->Change TEMP to FAHRENHEIT
0201->Change TIME to 24h
0202->Change TIME to 12h
0301->Change SPEED to KM/H
0302->Change SPEED to MP/h
*/
void DIAG_vPrintNewData()
{
    if (DIAG__bNewData == true && millis() < DIAG__USER_DELAY)
    {
        Serial.print(DIAG__cReceivedChars);
        DIAG__bNewData = false;
        if (DIAG__cReceivedChars[0]=='0' && DIAG__cReceivedChars[1]=='1' && DIAG__cReceivedChars[2] == '0' && DIAG__cReceivedChars[3]== '1')
        {
            EEPROM_WriteData(enTempFormat, (byte *)&DIAG__u8CelsiusOption);
        }
        else if (DIAG__cReceivedChars[0]=='0' && DIAG__cReceivedChars[1]=='1' && DIAG__cReceivedChars[2] == '0' && DIAG__cReceivedChars[3]== '2')
        {
            EEPROM_WriteData(enTempFormat, (byte *)&DIAG__u8FahrenheitOption);
        }
        else if (DIAG__cReceivedChars[0]=='0' && DIAG__cReceivedChars[1]=='2' && DIAG__cReceivedChars[2] == '0' && DIAG__cReceivedChars[3]== '1')
        {
            EEPROM_WriteData(enTimeFormat, (byte *)&DIAG__u8FullDay);
        }
        else if (DIAG__cReceivedChars[0]=='0' && DIAG__cReceivedChars[1]=='2' && DIAG__cReceivedChars[2] == '0' && DIAG__cReceivedChars[3]== '2')
        {
            EEPROM_WriteData(enTimeFormat, (byte *)&DIAG__u8HalfDay);
        }
        else if (DIAG__cReceivedChars[0]=='0' && DIAG__cReceivedChars[1]=='3' && DIAG__cReceivedChars[2] == '0' && DIAG__cReceivedChars[3]== '1')
        {
            EEPROM_WriteData(enSpeedUnit, (byte *)&DIAG__u8Kmh);
        }
        else if (DIAG__cReceivedChars[0]=='0' && DIAG__cReceivedChars[1]=='3' && DIAG__cReceivedChars[2] == '0' && DIAG__cReceivedChars[3]== '2')
        {
            EEPROM_WriteData(enSpeedUnit, (byte *)&DIAG__u8Mph);
        }
    }
}
void DIAG_vCreateMenu()
{
    if(Serial.available()>0 && DIAG__bNewData == false)
    {
        DIAG__cUserInput = Serial.read();

        if(DIAG__cUserInput != DIAG__cEndMarker)
        {
            DIAG__cReceivedChars[DIAG__byCounter] = DIAG__cUserInput;
            DIAG__byCounter++;
            if(DIAG__byCounter >= DIAG__byNumChars)
            {
                DIAG__byCounter = DIAG__byNumChars - 1;
            }
        }else
        {
            DIAG__cReceivedChars[DIAG__byCounter]= '\0';
            DIAG__byCounter = 0;
            DIAG__bNewData = true;
        }
    } 
}