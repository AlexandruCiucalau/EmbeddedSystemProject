#include "Arduino.h"
#ifndef TempE_h
#define TempE_h
//functions for reading temp values
float TEMP_fGetCelsius();
float TEMP_fGetFahrenheit();
void TEMP_vChooseCorF(bool aux);
float TEMP_fConvertCtoF();
void TEMP_vSetup();
void TEMP_vStoreTemperature();
float TEMP_fReadCelsius();
//````````````````````````````````````````````
void i2c_start();
void loopTemp();
void i2c_stop();
void i2c_write(uint8_t data);
uint8_t i2c_read_ack();
uint8_t i2c_read_nack();
void setupTEMP();
//struct for sharing temperature data
static struct temp_stValues
{
    float stCelsius;
    float stFahrenheit;
}temp_stTempValues;
#endif