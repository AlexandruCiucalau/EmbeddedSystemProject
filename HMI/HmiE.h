#ifndef HmiE_h
#define HmiE_h

#include "CommonDataE.h"
#include "TempE.h"
#include "TimeE.h"
void HMI_Setup(void);
void HMI_LOOP(void);
void HMI_vEvents(CommonData_enIDs ID);

#endif