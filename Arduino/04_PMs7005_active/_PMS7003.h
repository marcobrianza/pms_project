/*
  PMS Advances example using SoftwareSerial
  printing out
  - standard particles (CF=1)
  - Atmospheric environment particles
  - raw numbers of particle numbers measured by device


  NOTE: For measuring/comparing data atmospheric environment particles should be used all the time!
*/

#include <SoftwareSerial.h>
SoftwareSerial pmsSerial(D5, D6);

#include "src/Plantower_PMS/pms.h"


PMS pms(pmsSerial);
PMS::DATA data;

#define SEP ","

String sensorPM = "";
String sensorRAW = "";

void PMS7003_setup()
{
  pmsSerial.begin(9600);
  // Switch to passive mode.
  //pms.passiveMode();

  // Default state after sensor power, but undefined after ESP restart e.g. by OTA flash, so we have to manually wake up the sensor for sure.
  // Some logs from bootloader is sent via Serial port to the sensor after power up. This can cause invalid first read or wake up so be patient and wait for next read cycle.
  pms.wakeUp();
}




bool PMS_7003_loop() {

  if (pms.read(data)) {
    return (true);
  } else {
    return (false);
  }
}

void PMS_7003_makeCSV()  {
  sensorPM = String(data.PM_SP_UG_1_0) + SEP + String(data.PM_AE_UG_1_0) + SEP + String(data.PM_SP_UG_2_5) + SEP + String(data.PM_AE_UG_2_5) + SEP + String(data.PM_SP_UG_10_0) + SEP + String(data.PM_AE_UG_10_0);
  sensorRAW = String(data.PM_RAW_0_3) + SEP + String(data.PM_RAW_0_5) + SEP + String(data.PM_RAW_1_0) + SEP + String(data.PM_RAW_2_5) + SEP + String(data.PM_RAW_5_0) + SEP + String(data.PM_RAW_10_0);
}

void PMS7003_print() {
  Serial.print("PM 1.0 (ug/m3) CF=1: ");
  Serial.println(data.PM_SP_UG_1_0);

  Serial.print("PM 1.0 (ug/m3): ");
  Serial.println(data.PM_AE_UG_1_0);

  Serial.print("PM 2.5 (ug/m3) CF=1: ");
  Serial.println(data.PM_SP_UG_2_5);

  Serial.print("PM 2.5 (ug/m3): ");
  Serial.println(data.PM_AE_UG_2_5);

  Serial.print("PM 10.0 (ug/m3) CF=1: ");
  Serial.println(data.PM_SP_UG_10_0);

  Serial.print("PM 10.0 (ug/m3): ");
  Serial.println(data.PM_AE_UG_10_0);

  // raw particle counts
  Serial.print("P > 0.3 (count/0.1l): ");
  Serial.println(data.PM_RAW_0_3);

  Serial.print("P > 0.5 (count/0.1l): ");
  Serial.println(data.PM_RAW_0_5);

  Serial.print("P > 1.0 (count/0.1l): ");
  Serial.println(data.PM_RAW_1_0);

  Serial.print("P > 2.5 (count/0.1l): ");
  Serial.println(data.PM_RAW_2_5);

  Serial.print("P > 5.0 (count/0.1l): ");
  Serial.println(data.PM_RAW_5_0);

  Serial.print("P > 10.0 (count/0.1l): ");
  Serial.println(data.PM_RAW_10_0);


}
