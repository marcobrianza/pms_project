
int const APP_START = 0;
int const UPDATE = 1;
int const AUTO_UPDATE = 2;
int const UPDATE_ERROR = -3;
int const UPDATE_OK = 3;
int const WIFI_MANAGER_AP = 4;
int const WIFI_MANAGER_SAVE = 5;


void showState(int s) {

  //String ss;
  switch (s) {
    case UPDATE:

      break;
    case AUTO_UPDATE:

      blink(10);
      break;
    case UPDATE_OK:

      blink(10);
      break;
    case UPDATE_ERROR:

      break;
    case WIFI_MANAGER_AP:
      //ss = "wifi manager ap";

      break;
    case WIFI_MANAGER_SAVE:

      break;
    case APP_START:
      //ss = "app start";

      break;

  }
  //if (ss != "") Serial.println(ss);

}
