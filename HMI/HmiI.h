#ifndef HmiI_h
#define HmiI_h

#include "StateMachineE.h"
#include "ShiftE.h"
#define HMI__MAX_CIRCLE_INTERIOR_TEXT_WIDTH "0000.00."
#define HMI__ONE_SECOND 1000
#define HMI__SPEED_UNIT_KMH "km/h"
#define HMI__SPEED_UNIT_MPH "mph"
#define HMI__SPEED_UNIT_1 1
#define HMI__SPEED_UNIT_2 2
#define HMI__SPEED_MAX_KMH 300
#define HMI__SPEED_MAX_MPH 186
#define HMI__SPEED_EXCEEDED 180
#define HMI__SPEED_BLINK 750
#define HMI__SPEED_GAUGE_X 45
#define HMI__SPEED_GAUGE_Y 25
#define HMI__SPEED_GAUGE_GAP 4
#define HMI__SPEED_GAUGE_RADIUS 75
#define HMI__SPEED_WARNING "ATI DEPASIT VITEZA!"
#define HMI__DOORS_NO_OF_DOORS 4
#define HMI__DOORS_FRONT_LEFT 0
#define HMI__DOORS_FRONT_RIGHT 1
#define HMI__DOORS_REAR_LEFT 2
#define HMI__DOORS_REAR_RIGHT 3
#define HMI__TEMP_ONE_DECIMAL 1
#define HMI__TIME_FORMAT_1 12
#define HMI__TIME_FORMAT_2 24
#define HMI__TEMP_FORMAT_C 1
#define HMI__TEMP_FORMAT_F 2
#define HMI__BARGRAPH_LEVELS 4

// Meter colour schemes
#define RED2RED 0
#define GREEN2GREEN 1
#define BLUE2BLUE 2
#define BLUE2RED 3
#define GREEN2RED 4
#define RED2GREEN 5
#define GREEN2BLUE 6
#define BLUE2LIGHTBLUE 7
#define ILI9341_GREY 0x2104 // Dark grey 16 bit colour

// *************** DESIGN MACROS *************** //
//? SIZES
#define HMI__LOGO_SIZE 45
#define HMI__LOGO_POSITION_Y 88
#define HMI__LOGO_POSITION_X (HELPER_WIDTH_IMAGE_CENTER(HMI__LOGO_SIZE))
#define HMI__CIRCLE_INTERIOR_TEXT_PX (TFT_WIDTH - ((HELPER_DESIGN_RADIUS_PX * 2)))
#define HMI__ADMIN_PANEL_ICONS_SIZE_S 16
#define HMI__ADMIN_PANEL_ICONS_SIZE_M 45
#define HMI__ADMIN_PANEL_ICONS_SIZE_L 90

unsigned long HMI__previousMillisSeconds = 0;
static bool HMI__okMinutes = 1;
static bool HMI_okHours = 1;
uint8_t HMI__timeFormat;
unsigned long HMI_previousMillis = 0;
static bool HMI__okBattery = 0;
bool HMI__boDoorsPreviousValue[HMI__DOORS_NO_OF_DOORS] = {0, 0, 0, 0};
static int i = 0;

static uint32_t runTime = -99999;       // time for next update
static int reading = 0; // Value to be displayed
static int d = 0; // Variable used for the sinewave test waveform

enum HMI__enZoneVariants
{
  enOneLine = 0,
  enTwoLine,
  enThreeLine,
};
enShiftReg HMI_enumclone;

// *************** MACROS *************** //

// *************** CLASSES *************** //

// *************** FUNCTIONS *************** //
void HMI__vDrawSkeleton(STM_States enCurrentMachineState);
void HMI__vDrawCyclically(STM_States enCurrentMachineState);
void HMI__vDisplayTemperature();
void HMI__vControlBarGraph();
void HMI__vControlIndications();
void HMI__vDisplayDoorsState();
void HMI__vTimeBigFont();
void HMI__vTimeSmallFont();
void HMI__vHomeScreenClockSetup();
void HMI__vHomeScreenTemp();
void HMI__vDisplayLowBatteryIndication();
void HMI__vDisplayHighSpeedIndication();
void HMI__vDisplayDoorOpenWhileSpeeding();
void HMI__vDisplayDoorsSkeleton();
void HMI__vChangeGear();
void HMI__vDisplaySpeedGear();
unsigned int rainbow(byte value);
int ringMeter(int value, int vmin, int vmax, int x, int y, int r, char const *units, byte scheme);
void HMI_vDrawSpeedGauge();
void HMI_vDrawIndications();
#endif