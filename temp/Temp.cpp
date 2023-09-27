#include "Arduino.h"
#include "TempI.h"
#include "TempE.h"
#include "Temperature_LM75_Derived.h"
#include "CommonDataE.h"
#include "EEPROME.h"
#include <stdint.h>
#include "pins_arduino.h"

Generic_LM75 temperature;
void TEMP_vSetup()
{
  // Wire.begin();
}
void TEMP_vChooseCorF(bool TEMP__bCelsiusOrFahrenheit)
{
    if (TEMP__bCelsiusOrFahrenheit)
    {
        EEPROM_WriteData(enTempFormat, (byte *)&TEMP_Celsius);
    }
    else
    {
        EEPROM_WriteData(enTempFormat, (byte *)&TEMP_Fahrenheit);
    }
}
float TEMP_fReadCelsius()
{
    Wire.beginTransmission(DEFAULT_I2C_ADDRESSS);
    Wire.write(LM75_TEMP_REGISTER);
    Wire.endTransmission(false);
    Wire.requestFrom(0x48, 2);

    while (Wire.available() < 2)
    {
    }

    int16_t temperature = (Wire.read() << 8) | Wire.read();
    float celsius = temperature / 256.0;
    return celsius;
}
float TEMP_fGetCelsius()
{
    temp_stTempValues.stCelsius = TEMP_fReadCelsius();
    return TEMP_fReadCelsius();
}

float TEMP_fGetFahrenheit()
{
    temp_stTempValues.stFahrenheit = TEMP_fConvertCtoF();
    return TEMP_fConvertCtoF();
}

float TEMP_fConvertCtoF()
{
    return TEMP_fReadCelsius() * 1.8 + 32;
}

void TEMP_vStoreTemperature()
{
    static float TEMP__fOldTemperature = 0;
    temp_stTempValues.stCelsius = TEMP_fReadCelsius();
    temp_stTempValues.stFahrenheit = TEMP_fConvertCtoF();
    if (temp_stTempValues.stCelsius != TEMP__fOldTemperature)
    {
        CommonData_Set(CommonData_enTemperature, &temp_stTempValues);
        TEMP__fOldTemperature = temp_stTempValues.stCelsius;
    }
}
void wait(unsigned long microseconds)
{
    unsigned long currentmillis = millis();
    while(millis()-currentmillis > microseconds)
    {
        
    }
}
//``````````````````````````````````````````````````````````````````````````````````````````````````````
void setupTEMP()
{
    pinMode(SDA, OUTPUT);
    pinMode(SCL, OUTPUT);
    digitalWrite(SDA, HIGH);
    digitalWrite(SCL, HIGH);
}

void i2c_start()
{
    digitalWrite(SDA, HIGH);
    digitalWrite(SCL, HIGH);
    digitalWrite(SDA, LOW);
    digitalWrite(SCL, LOW);
}

void i2c_stop()
{
    digitalWrite(SDA, LOW);
    digitalWrite(SCL, HIGH);
    digitalWrite(SDA, HIGH);
}

void i2c_write(uint8_t data)
{
    for (uint8_t mask = 0x80; mask > 0; mask >>= 1)
    {
        digitalWrite(SDA, (data & mask) != 0);

        digitalWrite(SCL, HIGH);
        digitalWrite(SCL, LOW);
    }

    digitalWrite(SDA, HIGH);
    digitalWrite(SCL, HIGH);
    digitalWrite(SCL, LOW);
}

uint8_t i2c_read_ack()
{
    uint8_t data = 0;

    pinMode(SDA, INPUT);

    for (uint8_t mask = 0x80; mask > 0; mask >>= 1)
    {
        digitalWrite(SCL, HIGH);
        digitalWrite(SCL, LOW);

        if (digitalRead(SDA))
        {
            data |= mask;
        }
        else
        {
            data |= 0;
        }
    }

    pinMode(SDA, OUTPUT);
    digitalWrite(SCL, HIGH);
    digitalWrite(SCL, LOW);

    return data;
}
uint8_t i2c_read_nack()
{
    uint8_t data = 0;

    pinMode(SDA, INPUT);

    for (uint8_t mask = 0x80; mask > 0; mask >>= 1)
    {
        digitalWrite(SCL, HIGH);
        digitalWrite(SCL, LOW);

        if (digitalRead(SDA))
        {
            data |= mask;
        }
        else
        {
            data |= 0;
        }
    }
    pinMode(SDA, OUTPUT);

    digitalWrite(SDA, HIGH);

    digitalWrite(SCL, HIGH);
    digitalWrite(SCL, LOW);

    return data;
}

void loopTemp()
{
    i2c_start();

    i2c_write(DEFAULT_I2C_ADDRESSS << 1);
    i2c_write(LM75_TEMP_REGISTER);

    i2c_start();

    i2c_write((DEFAULT_I2C_ADDRESSS << 1) | 0x01);

    uint8_t temp_msb = i2c_read_nack();
    uint8_t temp_lsb = i2c_read_ack();

    i2c_stop();

    int16_t temp_raw = (temp_msb << 8) | temp_lsb;
    float temperature = (temp_raw / (256.0));

    static float TEMP__fOldTemperature = 0;
    temp_stTempValues.stCelsius = temperature;
    temp_stTempValues.stFahrenheit = temperature * 1.8 + 32; 
    if (temp_stTempValues.stCelsius != TEMP__fOldTemperature && (temp_stTempValues.stCelsius > 20 && temp_stTempValues.stCelsius < 40))
    {
        CommonData_Set(CommonData_enTemperature, &temp_stTempValues);
        TEMP__fOldTemperature = temp_stTempValues.stCelsius;
    }
}