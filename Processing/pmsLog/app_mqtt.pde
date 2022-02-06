//---- mqtt config
String mqttServer = "mqtt.marcobrianza.it";
//String mqttServer = "127.0.0.1";

int MQTT_PORT = 1883;
String mqttUsername = "aieie";
String mqttPassword = "brazorf";

String TOPIC_ROOT="worldsensors";
String name="pmsProcessing";
String softwareInfo=name+" 1.0.0";


//----------------------


String T_SUBSCRIBE="worldsensors/+/sensor";


void mqttSubscribe() {
  mqttClient.subscribe(T_SUBSCRIBE);
}



void mqttAppReceiveString(String Topic, String Payload) {


  //if (Topic.equals("worldsensors/PMS_E8:DB:84:9B:5B:52/sensor")== true ) {
  JSONObject pmsData = parseJSONObject(Payload);

  println(pmsData);
  String name=pmsData.getString("name");

  int pm1_0=pmsData.getInt("PM_1.0_SP");
  int pm2_5=pmsData.getInt("PM_2.5_SP");
  int pm10=pmsData.getInt("PM_10_SP");

  int pm1_0ae=pmsData.getInt("PM_1.0_AE");
  int pm2_5ae=pmsData.getInt("PM_2.5_AE");
  int pm10ae=pmsData.getInt("PM_10_AE");

  int pm_raw_03=pmsData.getInt("PM_RAW_0.3");
  int pm_raw_05=pmsData.getInt("PM_RAW_0.5");
  int pm_raw_1=pmsData.getInt("PM_RAW_1.0");
  int pm_raw_2_5=pmsData.getInt("PM_RAW_2.5");
  int pm_raw_5_0=pmsData.getInt("PM_RAW_5.0");
  int pm_raw_10=pmsData.getInt("PM_RAW_10");

  float temperature=pmsData.getFloat("Temperature");
  float humidity=pmsData.getFloat("Humidity");

  print(name, temperature, humidity);

  //}
}
