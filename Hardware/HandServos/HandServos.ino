
#include <ESP32Servo.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <ArduinoWebsockets.h>

const char* SSID = "slu-guest";
const char* PWD = "greengold11";
const char* SERVER = "ws://getagrip.ngrok.app";

const int SERVO_PINS[5] = { 33, 34, 35, 36, 39 };

using namespace websockets;

int status = WL_IDLE_STATUS;

WebsocketsClient client;

StaticJsonDocument<200> document;

void setup()
{
  Serial.begin(115200);
  WiFi.begin(SSID, PWD);

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

  client.onMessage([&](WebsocketsMessage message){
        Serial.print("Got Message: ");
        Serial.println(message.data());
    });
}

int getFinger(String finger) 
{
  if (finger == "thumb") {
    return 0;
  }
  else if (finger == "index") {
    return 1;
  }
  else if (finger == "middle") {
    return 2;
  }
  else if (finger == "ring") {
    return 3;
  }
  else if (finger == "pinky") {
    return 4;
  }
}

void loop()
{
  // setPositions();
  client.poll();
  delay(100);
}