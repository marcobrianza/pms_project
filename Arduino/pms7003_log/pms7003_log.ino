// tested on ESP8266 Core 3.0.2
// use FS:1MB
// https://arduino.esp8266.com/stable/package_esp8266com_index.json

boolean DEBUG_MAIN = true;

String softwareName = "PMSLog";
String softwareVersion = "1.0.0";
String appId = "PMS";

String softwareInfo = "";
String softwarePlatform = "";

String thingId = "";
String name = "";

#include <ESP8266WiFi.h>  // built in ESP8266 Core

#include "_miniUI.h"
#include "_app_status.h"
#include "_WiFi.h"
#include "_app.h"
#include "_MQTT.h"



#include "_WiFiManager.h"

void setup() {

  softwareInfo_setup();
  ledOFF();
  app_setup();

  loadParametersFromFile();

  byte bc = miniUI_bootCount();
  //if (bc == BOOT_TEST_DEVICE)  app_testDevice();

  ledON();
  WiFi_setup();

  // test parameters
  //connectWiFi("Red", "marcolino");
  //mqttServer = "192.168.1.5";

  switch  (bc) {
    case BOOT_RESET:
      if (DEBUG_MAIN) Serial.println("Reset parameters");
      saveParametersToFile();
      connectWiFi_Manager(true);
      break;

    case BOOT_DEFAULT_AP:
      if (DEBUG_MAIN) Serial.println("Reset parameters and connecting to default AP");
      saveParametersToFile();
      connectWiFi("", "");
      break;

    case BOOT_ESPTOUCH:
      connectWiFi_Smart();
      break;
    default:
      connectWiFi_Manager(false);
  }

  autoUpdate();
  OTA_setup();
  mqtt_setup();

  ledOFF();
  if (DEBUG_MAIN) Serial.println("starting loop");

}



void loop() {

  miniUI_loop();
  WiFi_loop();
  mqtt_loop();

  // app loop
  if (PMS_7003_loop())
  {
    //PMS7003_print();
    PMS_7003_makeCSV();
    Serial.print(sensorPM);
    Serial.print(" - ");
    Serial.println(sensorRAW);
    //publishSensor();
  }
  //sht3x_loop() ;

  if (newSettings) {
    newSettings = false;
    saveParametersToFile();
  }

}



void softwareInfo_setup() {
  softwareInfo = softwareName + " - " + softwareVersion +  " - " + ESP.getSketchMD5() + " - " + String (ESP.getCpuFreqMHz()); // + " - " + String (__DATE__) + " - " + String(__TIME__);;
  softwarePlatform = ESP.getFullVersion();
  thingId = appId + "_" +  WiFi.macAddress().c_str();
  name = thingId;

  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);

  if (DEBUG_MAIN) {
    Serial.println("");
    Serial.println(softwareInfo);
    Serial.println(softwarePlatform);
    Serial.println("resetReason=" + ESP.getResetReason());
    Serial.println("thingId: " + thingId);
  }

}
