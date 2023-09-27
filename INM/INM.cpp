#include "Arduino.h"
#include "INMI.h"
#include "INME.h"
#include "MUXE.h"
#include "CommonDataE.h"

unsigned char INM_u8lastButtonState[INM_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned char INM_u8ButtonState[INM_SIZE];
unsigned long INM__ulLastDebounceTime[INM_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0};

void INM_Debounce(uint8_t u8currenState, uint8_t u8MuxValue)
{
    uint8_t reading = u8MuxValue;
    // check if the state changed
    if (reading != INM_u8lastButtonState[u8currenState])
    {
        // reset the timer
        INM__ulLastDebounceTime[u8currenState] = millis();
    }

    if ((millis() - INM__ulLastDebounceTime[u8currenState]) > INM__ulDebounceDelay) // wait 50ms
    {
        if (reading != INM_u8ButtonState[u8currenState])
        {
            INM_u8ButtonState[u8currenState] = reading;
        }
    }

    INM_u8lastButtonState[u8currenState] = reading;
    return;
}

void INM_Loop()
{
    CommonData_Get(CommonData_enMuxValues, &INM_unMuxValues);

    INM_Debounce(INM_SW1, INM_unMuxValues.stMuxInputs.stSwitchKey1);
    stInmValues.stSW1 = INM_u8ButtonState[INM_SW1];

    INM_Debounce(INM_SW2, INM_unMuxValues.stMuxInputs.stSwitchKey2);
    stInmValues.stSW2 = INM_u8ButtonState[INM_SW2];

    INM_Debounce(INM_SW3, INM_unMuxValues.stMuxInputs.stSwitchKey3);
    stInmValues.stSW3 = INM_u8ButtonState[INM_SW3];

    INM_Debounce(INM_SW4, INM_unMuxValues.stMuxInputs.stSwitchKey4);
    stInmValues.stSW4 = INM_u8ButtonState[INM_SW4];

    INM_Debounce(INM_KEY1, INM_unMuxValues.stMuxInputs.stKey1);
    stInmValues.stKEY1 = INM_u8ButtonState[INM_KEY1];

    INM_Debounce(INM_KEY2, INM_unMuxValues.stMuxInputs.stKey2);
    stInmValues.stKEY2 = INM_u8ButtonState[INM_KEY2];

    INM_Debounce(INM_KEY3, INM_unMuxValues.stMuxInputs.stKey3);
    stInmValues.stKEY3 = INM_u8ButtonState[INM_KEY3];

    INM_Debounce(INM_KEY4, INM_unMuxValues.stMuxInputs.stKey4);
    stInmValues.stKEY4 = INM_u8ButtonState[INM_KEY4];

    CommonData_Set(CommonData_enInmValues, &stInmValues);
}