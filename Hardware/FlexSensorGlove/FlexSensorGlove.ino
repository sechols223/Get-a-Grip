#include "FlexLibrary.h"
#include <ArduinoJson.h>
#include <WiFi.h>
#include <ArduinoWebsockets.h>

const char* SSID = "slu-guest";
const char* PWD = "greengold11";
const char* SERVER = "ws://getagrip.ngrok.app";

const int FLEX_PINS[5] = { 33, 34, 35, 36, 39 };

using namespace websockets;

Flex SENSORS[5] = {Flex(0), Flex(0), Flex(0), Flex(0), Flex(0)};
int MIN_VALUES[5];
int MAX_VALUES[5];
void initSensors() 
{
  for (int i = 0; i < 5; ++i)
  {
    SENSORS[i] = Flex(FLEX_PINS[i]);
    MIN_VALUES[i] = SENSORS[i].getMinInput();
    MAX_VALUES[i] = SENSORS[i].getMaxInput();
  }
}



int status = WL_IDLE_STATUS;

WebsocketsClient client;

StaticJsonDocument<200> document;

void setup()
{
  Serial.begin(115200);
  WiFi.begin(SSID, PWD);
  
  initSensors();

  while (WiFi.status() != WL_CONNECTED) 
  {
    WiFi.begin(SSID, PWD);
    delay(1000);
    Serial.println("Failed to conncet to WiFi. Retrying");
  }

  Serial.println("Connected to WiFi.");
  Serial.println("Connecting to WS Server.");

  client.connect(SERVER);

  while (!client.available())
  {
    client.connect(SERVER);
    delay(1000);
    Serial.println("Failed to conncet to WSS. Retrying");
  }

  Serial.println("Connected to WSS.");
  client.send("Please work!");
}

char* pickFinger(int nFinger) 
{
  char* finger;

  switch (nFinger) 
  {
    case 0:
      finger = "thumb";
      break;
    case 1:
      finger = "index";
      break;
    case 2:
      finger = "middle";
      break;
    case 3:
      finger = "ring";
      break;
    case 4:
      finger = "pinky";
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

  serializeJson(document, buffer);

  client.send(buffer);
}

void setPositions()
{
  for (int i = 0; i < 5; ++i)
  {
    SENSORS[i].updateVal();

    float sensorValue = SENSORS[i].getSensorValue();
    float servoAngle = map(SENSORS[i].getSensorValue(), MIN_VALUES[i], MAX_VALUES[i], 180, 0);
    servoAngle = constrain(servoAngle, 0, 180);
    Serial.printf("Finger: %d Angle: %f\n", i, servoAngle);
    Serial.printf("Min: %d Angle: %f\n", i, MIN_VALUES[i]);
    Serial.printf("Maxin: %d Angle: %f\n", i, MAX_VALUES[i]);

    sendPositionMessage(i, servoAngle);
  }
}

void loop()
{
  setPositions();
  delay(100);
}