#ifndef BatteryI_h
#define BatteryI_h

#define ADJ1 36
#define BATTERY__THRESHOLD_UP 10;
#define BATTERY__LVL_0 800;
#define BATTERY__LVL_1 1600;
#define BATTERY__LVL_2 2400;
#define BATTERY__LVL_3 3200;
#define BATTERY__LVL_4 4000;
#define BATTERY__PARAM_1 4
#define BATTERY__PARAM_2 2048
#define BATTERY__PARAM_3 4096
#define BATTERY__BARGRAPH_0 0;
#define BATTERY__BARGRAPH_1 1;
#define BATTERY__BARGRAPH_2 2;
#define BATTERY__BARGRAPH_3 3;
#define BATTERY__BARGRAPH_4 4;
#define BAT__0 0
#define BAT__1 1
#define BAT__2 2
#define BAT__3 3
#define BAT__4 4

uint16_t Battery__u16ReadValue = 0;
uint16_t Battery__u16OldReadValue = Battery__u16ReadValue;

#endif