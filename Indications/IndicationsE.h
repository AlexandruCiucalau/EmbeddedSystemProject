#include "Arduino.h"
#ifndef IndicationsE_h
#define IndicationsE_h
enum Indications
{
    enfalse,
    entrue
};
void IND_vSetLowBeamIndication();
void IND_vSetHighBeamIndication();
void IND_vSetFogLightsIndication();
void IND_vSetLowBatteryIndication();
void IND_vSetIndication1();
void IND_vSetIndication2();
void IND_vSetIndication3();
//``````````````````````````````````````````````````````````````````
void IND_vGetLowBeamIndication();
void IND_vGetHighBeamIndication();
void IND_vGetFogLightsIndication();
void IND_vGetLowBatteryIndication();
void IND_vGetIndication1();
void IND_vGetIndication2();
void IND_vGetIndication3();
void IND_vSetup();
#endif