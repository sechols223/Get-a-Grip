#include <Servo.h>
#include "FlexLibrary.h"

#define PORT = 80;

Flex flex(13);

Servo servo;

const int flexPin = 13;	
const int servoPin = 12;
const char* ssid = "Elevator3";
const char* pswd = "";
//Set the server address
const char* serverAddress = "";

int SERVO_ANGLE;
int minVal;
int maxVal;

float currentAngle;
bool hasReset = false;

bool isWithinThreshold(const int servoAngle) {
  const float minThreshold = 1.5;
  const float maxThreshold = 1.5;

  float minAdjustedAngle = (float) servoAngle - minThreshold;
  float maxAdjustedAngle = (float) servoAngle + maxThreshold;

  bool isWithinMin = servoAngle >= minAdjustedAngle;
  bool isWithinMax = servoAngle <= maxAdjustedAngle;

  return isWithinMin && isWithinMax;
}

void calibrateSensors() {
  for (int i = 0; i < 10000; i++) {
      flex.Calibrate();
    }
}

void setup() {

  calibrateSensors();

  minVal = flex.getMinInput();
  maxVal = flex.getMaxInput();

	Serial.begin(115200);
	pinMode(flexPin, INPUT);
  servo.attach(servoPin);
}

void reset() {
    servo.write(90);
    hasReset = true;
}

void loop() {
  if (!hasReset) {
    reset();
  }

  flex.updateVal();
  int flexValue = analogRead(flexPin);
  int servoAngle = map(flex.getSensorValue(), minVal, maxVal, 180, 0);
  
  servoAngle = constrain(servoAngle, 0, 180);

  if (SERVO_ANGLE != servoAngle && isWithinThreshold(servoAngle)) {
    servo.write(servoAngle);
  }

  SERVO_ANGLE = servoAngle;
  Serial.println(servoAngle);
}