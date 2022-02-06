
#include "_PMS7003.h"

void setup()
{

  Serial.begin(115200);
  PMS7003_setup();

}

void loop()
{
  if (PMS_7003_loop())
  {
    //PMS7003_print();
    PMS_7003_makeCSV();
    Serial.println(sensorPM);
    Serial.println(sensorRAW);
  }


}
