#ifndef RELAYI_h
#define RELAYI_h
//#define RELAY_DEBUG

/* Defining RELAYS Control Pins */
#define RELAY__PIN1 19
#define RELAY__PIN2 18
#define RELAY__INTERVAL 1000

static bool RELAY__boFlag = false;

unsigned long RELAY__ulDuration;
unsigned long RELAY__ulRemembertime = 0;

#endif