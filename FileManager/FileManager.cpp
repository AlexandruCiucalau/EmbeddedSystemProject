/***************************************************************************
*=====================      Copyright by novartsoft.com      ===============
****************************************************************************
* Title        : Spiffs.cpp
*
* Description  : This module is responsable of HMI Helper functions
*
* Environment  : ESP32
*
* Responsible  : Attila Gabor
* 
* History: 
* 17.06.2021    AttGab  Initial revision
*/
#include "Arduino.h"
// Partition SPIFFS
#include <FS.h>
#include "SPIFFS.h"
#include "FileManagerI.h"
#include "FileManagerE.h"

void FileManager_Setup(void)
{
    if (!SPIFFS.begin())
    {
        if (DEBUG_SPIFFS)
        {
            Serial.println("SPIFFS initialisation failed!");
        }

        while (1)
            yield(); // Stay here twiddling thumbs waiting
    }
    if (DEBUG_SPIFFS)
    {
        Serial.println("\r\nInitialisation done.");
        FileManager__listDir(SPIFFS, "/", 0); // Lists the files so you can see what is in the SPIFFS
    }
}

void FileManager__listDir(fs::FS &fs, const char *dirname, uint8_t levels)
{
    Serial.println();
    Serial.println("SPIFFS files found:");
    Serial.printf("Listing directory: %s\n", "/");
    String line = "=====================================";
    Serial.println(line);
    Serial.println("  File name               Size");
    Serial.println(line);
    fs::File root = SPIFFS.open(dirname);
    if (!root)
    {
        Serial.println("Failed to open directory");
        return;
    }
    if (!root.isDirectory())
    {
        Serial.println("Not a directory");
        return;
    }

    fs::File file = root.openNextFile();
    while (file)
    {

        if (file.isDirectory())
        {
            Serial.print("DIR : ");
            String fileName = file.name();
            Serial.print(fileName);
            if (levels)
            {
                FileManager__listDir(SPIFFS, file.name(), levels - 1);
            }
        }
        else
        {
            String fileName = file.name();
            Serial.print("  " + fileName);
            int spaces = 20 - fileName.length(); // Tabulate nicely
            while (spaces--)
                Serial.print(" ");
            String fileSize = (String)file.size();
            spaces = 10 - fileSize.length(); // Tabulate nicely
            while (spaces--)
                Serial.print(" ");
            Serial.println(fileSize + " bytes");
        }

        file = root.openNextFile();
    }
    Serial.println(line);
    Serial.println();
}
