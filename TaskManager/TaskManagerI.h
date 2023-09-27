/***************************************************************************
 *=====================      Copyright by novartsoft.com      ===============
 ****************************************************************************
 * Title        : TaskManagerE.h
 *
 * Description  : This module is responsable of scheduling
 *                the tasks on the FreeRTOS system
 *
 * Environment  : ESP32
 *
 * Responsible  : Catalin Gyorgy
 *
 * History:
 * 10.06.2021    CatGyo  Initial revision
 */
#ifndef TaskManagerI_h
#define TaskManagerI_h

#include "main.h"
#include "HmiE.h"
#include "StateMachineE.h"
#include "FileManagerE.h"
#include "ShiftE.h"
#include "tempE.h"
#include "MUXE.h"
#include "RELAYE.h"
#include "TimeE.h"
#include "DiagnosisE.h"
#include "SoundE.h"
#include "INME.h"
#include "SpeedE.h"
#include "IndicationsE.h"
#include "EEPROME.h"
#include "CommonDataE.h"
#include "BatteryE.h"
#include "DoorsE.h"
#include "LightsE.h"
#include "WiFiE.h"
#include "GearBoxE.h"

#define TaskManager__Delay1 1
#define TaskManager__Delay5 5
#define TaskManager__Delay10 10
#define TaskManager__Delay25 25
#define TaskManager__Delay50 50
#define TaskManager__Delay100 100

void TaskManager__DisplayTask(void *parameter);
void TaskManager__UART(void *parameter);
void TaskManager__ReadQueue(void *parameter);
void TaskManager__Task10ms(void *parameter);
void TaskManager__Task50ms(void *parameter);
void TaskManager__Task100ms(void *parameter);

/************************************************
 * Init containers
 ************************************************/

/* Init Display Container */
#define TaskManager__InitDisplay \
  HMI_Setup();                   \
  FileManager_Setup();
/* Init Read Queue Container */
#define TaskManager__InitReadQueue \
  CommonData_Setup();

/* Init 50ms Container */
#define TaskManager__Init50ms \
  MUX_Setup();                

/* Init 100ms Container */
#define TaskManager__Init100ms \
  STM_Setup();                 \
  SHIFT_vSetupp();             \
  setupTEMP();               \
  RELAY_Setup();               \
  Speed_Setup();               \
  IND_vSetup();                \
  WiFi_Setup();                 \
  Time_vSetup();               \
  GB__vSetup();              \
  TEMP_vSetup();
  
 

/************************************************
 *  Cyclic containers
 ************************************************/

/* Cyclic Display Container */
#define TaskManager__DisplayContainer \
  HMI_LOOP();

/* Cyclic Read Queue Container */
#define TaskManager__ReadQueueContainer \
  CommonData_ReadQueues();

/* Cyclic 10ms Container */
#define TaskManager__10msContainer \
  Time_vSendTimeToHMI();           \
  DIAG_vCreateMenu();              \
  DIAG_vPrintNewData();

/* Cyclic 50ms Container */
#define TaskManager__50msContainer \
  MUX_Loop();                      \
  Battery_Loop();                  \
  Doors_Loop();                    \
  Lights_Loop();                   \
  IND_vGetLowBatteryIndication(); \
  IND_vGetIndication1();          \
  IND_vGetIndication2();          \
  IND_vSetIndication3();           \
  IND_vGetIndication3();           \
  GB__vChooseGear(); 
  

/* Cyclic 100ms Container */
#define TaskManager__100msContainer \
  STM_LOOP();                       \
  SHIFT_vUpdateShiftRegister();     \
  INM_Loop();                       \
  loopTemp();     \
  IND_vSetLowBeamIndication();      \
  IND_vSetHighBeamIndication();     \
  IND_vSetFogLightsIndication();    \
  Speed_Loop();\
      Sound_vsetBuzzerD();
 //  loopTemp(); TEMP_vStoreTemperature(); 
#endif