#ifndef WiFiI_h
#define WiFiI_h

#include "LightsE.h"
#include "RELAYE.h"

#define WIFI__SERVER_PORT 80
#define WIFI__SERVER_CODE 200
#define WIFI__RELAY1 1
#define WIFI__RELAY2 2
#define WIFI__RELAY_ON 1
#define WIFI__RELAY_OFF 0
#define WIFI_DIAG_DEBUG
// #define WIFI_DEBUG

Lights_stData WiFi__stLightsData;

const char *WiFi__cSSID = "esp";
const char *WiFi__cPassword = "12345678";
const char *WiFi__cGetSSID;
const char *WiFi__cGetPassword;

const char *WiFi__cParamSpeedUnit = "speed_unit";
const char *WiFi__cParamTempUnit = "temp_unit";
const char *WiFi__cParamTimeFormat = "time_format";
const char *WiFi__cParamRelay = "relay";
const char *WiFi__cParamRelayState = "state";

const char WiFi__cIndexHtml[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP32</title>
  <meta name="viewport" content="width=device-width">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
    .switch {position: relative; display: inline-block; width: 120px; height: 68px} 
    .switch input {display: none}
    .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 40px}
    .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 30px}
    input:checked+.slider.blue {background-color: #3CA1FA}
    input:checked+.slider.yellow {background-color: #FFD10B}
    input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
    .current-config {font-size: 16px;}
    .new-config {font-size: 16px; padding: 0 0 5px 0;}
    .relays {padding: 0 0 13px 0;}
  </style>
</head>

<body>
  <div class="current-config">
    <h3>Current config</h3>
    <p>Speed Unit : <span>%SPEEDUNITPLACEHOLDER%</span></p>
    <p>Temperature Unit : <span id="tempu">%TEMPUNITPLACEHOLDER%</span></p>
    <p>Time Format : <span>%TIMEFORMATPLACEHOLDER%</span></p>
  </div>

  <div class="new-config">
    <h3>New config</h3>
    <form action="/" method="POST">
      <legend>Select speed unit</legend>
      <input type="radio" name="speed_unit" value="1" checked>
      <label>km/h</label>
      <input type="radio" name="speed_unit" value="2">
      <label>m/h</label>

      <legend>Select temperature unit</legend>
      <input type="radio" name="temp_unit" value="1" checked>
      <label>Celsius</label>
      <input type="radio" name="temp_unit" value="2">
      <label>Fahrenheit</label>

      <legend>Select time format</legend>
      <input type="radio" name="time_format" value="24" checked>
      <label>24h</label>
      <input type="radio" name="time_format" value="12">
      <label>12h</label>
      <br><br><button type="submit" name="submit">Submit</button>
    </form>
  </div>

  <div class="relays">
  <h3>Control Relays</h2>
  %RELAYSPLACEHOLDER%
  </div>

  <script>function toggleCheckbox(element) {
    var xhr = new XMLHttpRequest();
    if(element.checked){ xhr.open("GET", "/update?relay="+element.id+"&state=1", true); }
    else { xhr.open("GET", "/update?relay="+element.id+"&state=0", true); }
    xhr.send();
  }
  </script>
</body>
</html>)rawliteral";

#endif