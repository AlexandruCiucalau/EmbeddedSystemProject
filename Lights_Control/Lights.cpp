#include "Arduino.h"
#include "LightsE.h"
#include "LightsI.h"
#include "CommonDataE.h"

void Lights_Setup()
{
    
}

void Lights_Loop()
{
    CommonData_Get(CommonData_enInmValues, &Lights__stGetINMValues);
    Lights__u8buttonState[LIGHTS__LOW_BEAM] = Lights__stGetINMValues.stKEY1;
    Lights__u8buttonState[LIGHTS__HIGH_BEAM] = Lights__stGetINMValues.stKEY2;
    Lights__u8buttonState[LIGHTS__FOG_LIGHTS] = Lights__stGetINMValues.stKEY3;

    for (uint8_t u8it = 0; u8it < LIGHTS__SIZE; u8it++)
    {
        if (Lights__u8lastButtonState[u8it] == 0 && Lights__u8buttonState[u8it] == 1)
        {
            if (u8it == LIGHTS__LOW_BEAM && stLightsData.u8LowBeam == 0)
            {
                RELAY1_SetState(LIGHTS__LOW_BEAM_ON);
                stLightsData.u8LowBeam = 1;
            }
            else if (u8it == LIGHTS__LOW_BEAM && stLightsData.u8LowBeam == 1)
            {
                RELAY1_SetState(LIGHTS__LOW_BEAM_OFF);
                stLightsData.u8LowBeam = 0;
            }
            else if (u8it == LIGHTS__HIGH_BEAM && stLightsData.u8HighBeam == 0)
            {
                RELAY2_SetState(LIGHTS__HIGH_BEAM_ON);
                stLightsData.u8HighBeam = 1;
            }
            else if (u8it == LIGHTS__HIGH_BEAM && stLightsData.u8HighBeam == 1)
            {
                RELAY2_SetState(LIGHTS__HIGH_BEAM_OFF);
                stLightsData.u8HighBeam = 0;
            }
            else if (u8it == LIGHTS__FOG_LIGHTS)
            {
                stLightsData.u8FogLights = !stLightsData.u8FogLights;
            }

            CommonData_Set(CommonData_enLightsData, &stLightsData);
        }

        Lights__u8lastButtonState[u8it] = Lights__u8buttonState[u8it];
    }
}
