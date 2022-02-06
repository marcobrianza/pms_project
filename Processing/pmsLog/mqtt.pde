boolean DEBUG_MQTT=true;


int RECONNECT_INTERVAL = 15000; //millis
int reconnectInterval=RECONNECT_INTERVAL;
int lastConnectTime=-RECONNECT_INTERVAL;

//status
int STATUS_INTERVAL=5; //minutes
boolean publishStatus = false;
String T_STATUS=TOPIC_ROOT+"/"+name+"/status";

import java.util.Date;

import mqtt.*; //MQTT library by Joel Gaehwiler
boolean mqttClientConnected=false;
int QOS_AT_LEAST_1 = 1;
int QOS_EXACTLY_ONE=2;

int upTime = 0;
int lastMinute = 0;



// mqttClient;

MQTTClient mqttClient = new MQTTClient(this);

// ---- MQTT callbacks
void clientConnected() {
  if (DEBUG_MQTT) println("mqtt connected");
  mqttClientConnected=true;
  publishStatus=true;
  mqttSubscribe();
}


void messageReceived(String topic, byte[] payload) {

  String pl=new String(payload);
  if (DEBUG_MQTT) println("receiving mqtt message (Small): " + topic + " " + pl);
  mqttAppReceiveString(topic, pl);
}

void connectionLost() {
  if (DEBUG_MQTT) println("mqtt connection lost");
  mqttClientConnected=false;
}
//----------


void MQTT_loop() {


  if ((millis() - lastConnectTime) > reconnectInterval ) {
    lastConnectTime = millis();
    connectMQTT() ;
  }

  int m = millis() / 60000;
  if (m != lastMinute) {
    lastMinute = m;
    upTime++;
    if (upTime % STATUS_INTERVAL == 0 && STATUS_INTERVAL > 0 )publishStatus = true;
  }


  if (publishStatus) {
    publishStatus = false;
    publishStatusMQTT();
  }
}


void publishStatusMQTT() {

  JSONObject json;
  json = new JSONObject();

  json.setString("name", name);
  json.setInt("upTime", upTime);
  json.setString("softwareInfo", softwareInfo);

  Date thisDate = new Date();
  long thisDateTS=thisDate.getTime();
  json.setLong("timeSt", thisDateTS);

  String strJson=json.toString();

  sendMQTTmessageString(T_STATUS, strJson, true);
}


// byte version
void sendMQTTmessageByte(String Topic, byte[] Payload, boolean retained) {
  if (mqttClientConnected) {
    try {
      mqttClient.publish(Topic, Payload, QOS_AT_LEAST_1, retained);
      if (DEBUG_MQTT)  println("sending message (byte):", Topic);
    }
    catch(RuntimeException e) {
      // e.printStackTrace();
      if (DEBUG_MQTT)  println("mqtt coulnd not send message ");
    }
  } else {
    if (DEBUG_MQTT)  println("mqtt not connected");
  }
}

// String version
void sendMQTTmessageString(String Topic, String Payload, boolean retained) {
  if (mqttClientConnected) {
    try {
      mqttClient.publish(Topic, Payload, QOS_AT_LEAST_1, retained);
      if (DEBUG_MQTT)  println("sending message (String):", Topic, Payload);
    }
    catch(RuntimeException e) {
      // e.printStackTrace();
      if (DEBUG_MQTT)  println("mqtt coulnd not send message ");
    }
  } else {
    if (DEBUG_MQTT)  println("mqtt not connected");
  }
}



void connectMQTT() {
  if (!mqttClientConnected) {
    try {
      String mqttUrl="mqtt://" + mqttUsername+ ":"+mqttPassword+"@"+mqttServer+":"+MQTT_PORT;
      if (DEBUG_MQTT) println("connecting to:"+mqttUrl);
      mqttClient.connect(mqttUrl);
    }
    catch(RuntimeException e) {
      // e.printStackTrace();
      if (DEBUG_MQTT)  println("mqtt coulnd not connect, will retry in "+str(reconnectInterval/1000)+" seconds");
    }
  }
}
