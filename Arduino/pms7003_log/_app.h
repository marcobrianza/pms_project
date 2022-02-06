boolean DEBUG_APP = true;


#include "_PMS7003.h"
#include "_sht3x.h"

unsigned long lastAppTime = 0;
unsigned long  APP_INTERVAL = 100;

unsigned long lastButtonTime = 0;
unsigned long  BUTTON_INTERVAL = 2000;

//------


//#define abs2(x) ((x)>0?(x):-(x))


void app_setup() {
  PMS7003_setup();
  sht3x_setup();
  showState(APP_START);

}

void app_loop() {
  
}
