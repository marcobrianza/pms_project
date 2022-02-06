
#include "_sht3x.h"

void setup() {
  Serial.begin(115200);
  delay(1000);

  sht3x_setup();
}


void loop() {
  sht3x_loop();
  Serial.print (strTemperature);
  Serial.print(" ");
  Serial.println(strHumidity);

  delay(1000);

}
