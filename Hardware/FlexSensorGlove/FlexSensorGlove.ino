#include <WiFi101.h>
#include <ArduinoHttpClient.h>
#include "FlexLibrary.h"

const char* SSID = "";
const char* PASSWORD = "";
const char* WS_HOST = "get-a-grip.onrender.com";
const int PORT = 10000;

const int FLEX_PINS[] = {33, 34, 35, 36, 39};

Flex SENSORS[5];

int MIN_VALUES[5];
int MAX_VALUES[5];

int status = WL_IDLE_STATUS;

WiFiClient wifiClient;
WebSocketClient client = WebSocketClient(wifiClient, WS_HOST, PORT);

JsonDocument document;

void initWifiClient() 
{
  Serial.println("Connecting to WiFi..");
  int connectionAttempt = 1;

  status = wifiClient.begin(SSID, PASSWORD);
  while (status != WL_CONNECTED
  {
    Serial.printf("Failed to connect to wifi. Attempting to reconnect..Attempt %d\n", connectionAttempt);
    status = wifiClient.begin(SSID, PASSWORD;
  }
}

void setup() 
{
  Serial.begin(115200);
  initWifiClient();
}

char* pickFinger(int nFinger) 
{
  char* finger;

  switch (nFinger) 
  {
    case 0:
      *finger = "thumb";
      break;
    case 1:
      *finger = "index";
      break;
    case 2:
      *finger = "middler";
      break;
    case 3:
      *finger = "ring";
      break;
    case 4:
      *finger = "pinky";
      break;
  }

  return finger;
}

void sendPositionMessage(int nFinger, float angle) 
{
  char buffer[128];

  char* finger = pickFinger(nFinger);

  document["finger"] = finger;
  document["angle"] = angle;

  serializeJson(document, buffer, sizeof(buffer));

  client.beginMessage();
  client.print(buffer);
  client.end();

  free(buffer);
  free(finger);
}

void setPositions()
{
  for (int i = 0; i < 5; ++i)
  {
    SENSORS[i].updateValue();

    float sensorValue = digitalRead(FLEX_PINS[i]);
    float servoAngle = map(flexes[i].getSensorValue(), minVals[i], maxVals[i], 180, 0);
    servoAngle = constrain(servoAngle, 0, 180);

    sendPositionMessage(i, servoAngle);
  }
}

void checkWSConnection() 
{
  while (!client.connected())
  {
    client.begin();
  }
}

void loop()
{
  checkWSConnection();
  setPosition();
}