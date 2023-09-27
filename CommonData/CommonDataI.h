/***************************************************************************
 *=====================      Copyright by novartsoft.com      ===============
 ****************************************************************************
 * Title        : CommonDataI.h
 *
 * Description  : This module is responsable of data used commonly in more than one
 *                module
 *
 * Environment  : ESP32
 *
 * Responsible  : Catalin Gyorgy
 *
 * History:
 * 10.06.2021    CatGyo  Initial revision
 */
#ifndef CommonDataI_h
#define CommonDataI_h

#include "CommonDataE.h"
#include "main.h"
#include "HmiE.h"
#include "StateMachineE.h"
#include "TempE.h"
#include "SoundE.h"
#include "ShiftE.h"
#include "GearBoxE.h"
#include "RELAYE.h"
#include "MUXE.h"
#include "INME.h"
#include "SpeedE.h"
#include "DoorsE.h"
#include "LightsE.h"
#include "WiFi.h"

STM_States CommonData__StateMachineStatus;
temp_stValues CommonData__Temperature;
int CommonData__TempFormat;
//ESPCLUSTER CommonData__Shift;
int CommonData__ShiftHWTT1;
int CommonData__ShiftHWTT2;
int CommonData__ShiftHWTT3;
enShiftReg CommonData__ShiftBarGraphLVL;
int CommonData__ShiftBuzzer;
Relay_stData CommonData__RelayData;
MUX_unInputs CommonData__MuxValues;
INM_stInputs CommonData__InmValues;
Speed_stData CommonData__SpeedData;
bool CommonData__BuzzerA;
bool CommonData__BuzzerB;
bool CommonData__BuzzerC;
bool CommonData__BuzzerD;
bool CommonData__LowBeam;
bool CommonData__HighBeam;
bool CommonData__FogLights;
bool CommonData__LowBattery;
bool CommonData__Indication1;
bool CommonData__Indication2;
bool CommonData__Indication3;
static bool ok = 0;
Doors_stData CommonData__DoorsState;
Lights_stData CommonData__LightsData;
IPAddress CommonData__WiFiIPAddress;
Time_Details CommonData__TimeDetails;
stGearBox CommonData__GearBox;

static QueueHandle_t CommonData__Queues[CommonData_enMaxIDs];

const int CommonData__Sizes[CommonData_enMaxIDs] =
    {sizeof(STM_States),
     sizeof(temp_stValues),
     sizeof(int),
     sizeof(int),
     sizeof(int),
     sizeof(int),
     sizeof(enShiftReg),
     sizeof(int),
     sizeof(Relay_stData),
     sizeof(MUX_unInputs),
     sizeof(INM_stInputs),
     sizeof(Speed_stData),
     sizeof(bool),
     sizeof(bool),
     sizeof(bool),
     sizeof(bool),
     sizeof(bool),
     sizeof(bool),
     sizeof(bool),
     sizeof(bool),
     sizeof(bool),
     sizeof(bool),
     sizeof(bool),
     sizeof(Doors_stData),
     sizeof(Lights_stData),
     sizeof(IPAddress),
     sizeof(Time_Details),
     sizeof(stGearBox)
    };

static int *CommonData__Addresses[CommonData_enMaxIDs];

/* functions for events */
void CommonData__Events_StateMachineStatus(CommonData_enIDs);
void CommonData__Events_TemperatureState(CommonData_enIDs);
void CommonData__Events_TemperatureFormat(CommonData_enIDs);
void CommonData__Events_ShiftHWTT1(CommonData_enIDs);
void CommonData__Events_ShiftHWTT2(CommonData_enIDs);
void CommonData__Events_ShiftHWTT3(CommonData_enIDs);
void CommonData__Events_ShiftBarGraphLevel(CommonData_enIDs);
void CommonData__Events_ShiftBuzzer(CommonData_enIDs);
void CommonData__Events_RelayData(CommonData_enIDs);
void CommonData__Events_MuxValues(CommonData_enIDs);
void CommonData__Events_Shift_GetLVL(CommonData_enIDs);
void CommonData__Events_InmValues(CommonData_enIDs);
void CommonData__Events_SpeedData(CommonData_enIDs);
void CommonData__Events_BuzzerA(CommonData_enIDs);
void CommonData__Events_BuzzerB(CommonData_enIDs);
void CommonData__Events_BuzzerC(CommonData_enIDs);
void CommonData__Events_BuzzerD(CommonData_enIDs); 
void CommonData__Events_LowBeam(CommonData_enIDs);
void CommonData__Events_HighBeam(CommonData_enIDs);
void CommonData__Events_FogLights(CommonData_enIDs);
void CommonData__Events_LowBattery(CommonData_enIDs);
void CommonData__Events_Indication1(CommonData_enIDs);
void CommonData__Events_Indication2(CommonData_enIDs);
void CommonData__Events_Indication3(CommonData_enIDs);
void CommonData__Events_DoorsState(CommonData_enIDs);
void CommonData__Events_LightsData(CommonData_enIDs);
void CommonData__Events_WiFiIPAddress(CommonData_enIDs);
void CommonData__Events_TimeDetails(CommonData_enIDs);
void CommonData__Events_GearBox(CommonData_enIDs);

static void (*CommonData__Events[CommonData_enMaxIDs])(CommonData_enIDs) =
    {
        &CommonData__Events_StateMachineStatus,
        &CommonData__Events_TemperatureState,
        &CommonData__Events_TemperatureFormat,
        &CommonData__Events_ShiftHWTT1,
        &CommonData__Events_ShiftHWTT2,
        &CommonData__Events_ShiftHWTT3,
        &CommonData__Events_ShiftBarGraphLevel,
        &CommonData__Events_ShiftBuzzer,
        &CommonData__Events_RelayData,
        &CommonData__Events_MuxValues,
        &CommonData__Events_InmValues,
        &CommonData__Events_SpeedData,
        &CommonData__Events_BuzzerA,
        &CommonData__Events_BuzzerB,
        &CommonData__Events_BuzzerC,
        &CommonData__Events_BuzzerD,
        &CommonData__Events_LowBeam,
        &CommonData__Events_HighBeam,
        &CommonData__Events_FogLights,
        &CommonData__Events_LowBattery,
        &CommonData__Events_Indication1,
        &CommonData__Events_Indication2,
        &CommonData__Events_Indication3,
        &CommonData__Events_DoorsState,
        &CommonData__Events_LightsData,
        &CommonData__Events_WiFiIPAddress,
        &CommonData__Events_TimeDetails,
        &CommonData__Events_GearBox
        };
#endif

