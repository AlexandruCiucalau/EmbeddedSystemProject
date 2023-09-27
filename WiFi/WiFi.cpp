#include "Arduino.h"
#include "WiFiI.h"
#include "WiFiE.h"
#include "CommonDataE.h"
#include "EEPROME.h"
#include "LightsE.h"

// new object of type AsyncWebServer for the server
AsyncWebServer WiFi_awsServer(WIFI__SERVER_PORT);

String outputState(uint8_t u8output)
{
  if (u8output)
  {
    return "checked";
  }
  else
  {
    return "";
  }
}

// function to replace placeholders in web page
String WiFi_HTML_Processor(const String &placeholder)
{
  // get current state of modules when page is loaded
  EEPROM_ReadData(enSpeedUnit, (byte *)&WiFi_stBoardConfig.u8SpeedUnit);
  EEPROM_ReadData(enTimeFormat, (byte *)&WiFi_stBoardConfig.u8TimeFormat);
  EEPROM_ReadData(enTempFormat, (byte *)&WiFi_stBoardConfig.u8TemperatureUnit);
  CommonData_Get(CommonData_enLightsData, &WiFi__stLightsData);
#ifdef WIFI_DEBUG
  Serial.print("Setup Spded Unit: ");
  Serial.println(WiFi_stBoardConfig.u8SpeedUnit);
  Serial.print("Setup Temperature Unit: ");
  Serial.println(WiFi_stBoardConfig.u8TemperatureUnit);
  Serial.print("Setup Time Format: ");
  Serial.println(WiFi_stBoardConfig.u8TimeFormat);
#endif
  if (placeholder == "RELAYSPLACEHOLDER")
  {
    String buttons = "";
    buttons += "<h4>Relay 1 - Low Beam</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"1\" " + outputState(WiFi__stLightsData.u8LowBeam) + "><span class=\"slider yellow\"></span></label>";
    buttons += "<h4>Relay 2 - High Beam</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"2\" " + outputState(WiFi__stLightsData.u8HighBeam) + "><span class=\"slider blue\"></span></label>";
    return buttons;
  }
  else if (placeholder == "SPEEDUNITPLACEHOLDER")
  {
    if (WiFi_stBoardConfig.u8SpeedUnit == 1)
    {
      return "km/h";
    }
    else
    {
      return "m/h";
    }
    // return String(WiFi_stBoardConfig.u8SpeedUnit);
  }
  else if (placeholder == "TEMPUNITPLACEHOLDER")
  {
    if (WiFi_stBoardConfig.u8TemperatureUnit == 1)
    {
      return "Celsius";
    }
    else
    {
      return "Fahrenheit";
    }
    // return String(WiFi_stBoardConfig.u8TemperatureUnit);
  }
  else if (placeholder == "TIMEFORMATPLACEHOLDER")
  {
    return String(WiFi_stBoardConfig.u8TimeFormat) + "h";
  }
  return String();
}

void WiFi_Setup()
{
#ifdef WIFI_DEBUG
  Serial.println("Setting up the board as AP");
#endif
// Write on EEPROM the credidentials for AP mode setup
 EEPROM_WriteData(enWiFiSSID, (byte *)&WiFi__cSSID);
 EEPROM_WriteData(enWiFiPassword, (byte *)&WiFi__cPassword);
#ifdef WIFI_DEBUG
  Serial.print("Size of ssid ");
  Serial.println(sizeof(WiFi__cSSID));
  Serial.print("Size of pass ");
  Serial.println(sizeof(WiFi__cPassword));
#endif
  // Read data from EEPROM for AP mode
  EEPROM_ReadData(enWiFiSSID, (byte *)&WiFi__cGetSSID);
  EEPROM_ReadData(enWiFiPassword, (byte *)&WiFi__cGetPassword);
  // Setting the board as an AP
  WiFi.softAP(WiFi__cGetSSID, WiFi__cGetPassword);
  // Getting the IP Address
  IPAddress WiFi_IPAddress = WiFi.softAPIP();
  CommonData_Set(CommonData_enWiFiIPAddress, &WiFi_IPAddress);
#ifdef WIFI_DIAG_DEBUG
  /*  TO DO : Move this in diag module  */
  Serial.print("Local network IP Address : ");
  Serial.println(WiFi_IPAddress);
#endif
  // listen on incoming http requests
  WiFi_awsServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
                    { request->send_P(WIFI__SERVER_CODE, "text/html", WiFi__cIndexHtml, WiFi_HTML_Processor); });

  WiFi_awsServer.on("/", HTTP_POST, [](AsyncWebServerRequest *request)
                    {
    uint8_t params = request->params();
    for(uint8_t i = 0; i < params; i++){
      AsyncWebParameter* p = request->getParam(i);
      if(p->isPost()){
        // HTTP POST input1 value (speed-unit)
        if (p->name() == WiFi__cParamSpeedUnit) {
          WiFi_stBoardConfig.u8SpeedUnit = p->value().toInt();
          EEPROM_WriteData(enSpeedUnit, (byte*)&WiFi_stBoardConfig.u8SpeedUnit);
#ifdef WIFI_DEBUG
          Serial.print("Speed unit set to: ");
          Serial.println(WiFi_stBoardConfig.u8SpeedUnit);
#endif
        }
        // HTTP POST input2 value (temp-unit)
        if (p->name() == WiFi__cParamTempUnit) {
          WiFi_stBoardConfig.u8TemperatureUnit = p->value().toInt();
          EEPROM_WriteData(enTempFormat, (byte*)&WiFi_stBoardConfig.u8TemperatureUnit);
#ifdef WIFI_DEBUG
          Serial.print("Temp unit set to: ");
          Serial.println(WiFi_stBoardConfig.u8TemperatureUnit);
#endif
        }
        // HTTP POST input3 value (time-format)
        if (p->name() == WiFi__cParamTimeFormat) {
          WiFi_stBoardConfig.u8TimeFormat = p->value().toInt();
          EEPROM_WriteData(enTimeFormat, (byte*)&WiFi_stBoardConfig.u8TimeFormat);
#ifdef WIFI_DEBUG
          Serial.print("Time format set to: ");
          Serial.println(WiFi_stBoardConfig.u8TimeFormat);
#endif
        }
      }
    }
    request->send_P(WIFI__SERVER_CODE, "text/html", WiFi__cIndexHtml, WiFi_HTML_Processor); });

  // Send a GET request to <ESP_IP>/update?relay=<u8firstMessage>&state=<u8secondMessage>
  WiFi_awsServer.on("/update", HTTP_GET, [](AsyncWebServerRequest *request)
                    {
    uint8_t u8firstMessage;
    uint8_t u8secondMessage;
    // GET input1 value on <ESP_IP>/update?relay=<u8firstMessage>&state=<u8secondMessage>
    if (request->hasParam(WiFi__cParamRelay) && request->hasParam(WiFi__cParamRelayState)) {
      u8firstMessage = request->getParam(WiFi__cParamRelay)->value().toInt();
      u8secondMessage = request->getParam(WiFi__cParamRelayState)->value().toInt();
      
      if(u8firstMessage == WIFI__RELAY1 && u8secondMessage == WIFI__RELAY_ON)
      {
        WiFi__stLightsData.u8LowBeam = WIFI__RELAY_ON;
        RELAY1_SetState(WiFi__stLightsData.u8LowBeam);

      }
      else if(u8firstMessage == WIFI__RELAY1 && u8secondMessage == WIFI__RELAY_OFF)
      {
        WiFi__stLightsData.u8LowBeam = WIFI__RELAY_OFF;
        RELAY1_SetState(WiFi__stLightsData.u8LowBeam);
      }
      else if(u8firstMessage == WIFI__RELAY2 && u8secondMessage == WIFI__RELAY_ON)
      {
        WiFi__stLightsData.u8HighBeam = WIFI__RELAY_ON;
        RELAY2_SetState(WiFi__stLightsData.u8HighBeam);
      }
      else if(u8firstMessage == WIFI__RELAY2 && u8secondMessage == WIFI__RELAY_OFF)
      {
        WiFi__stLightsData.u8HighBeam = WIFI__RELAY_OFF;
        RELAY2_SetState(WiFi__stLightsData.u8HighBeam);
      }
      
      CommonData_Set(CommonData_enLightsData, &WiFi__stLightsData);
    }
    else {
      u8firstMessage = 0;
      u8secondMessage = 0;
    }

    request->send(WIFI__SERVER_CODE, "text/plain", "OK"); });

  // finally start the server
  WiFi_awsServer.begin();
}