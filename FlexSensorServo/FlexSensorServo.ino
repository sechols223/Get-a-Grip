#include <Servo.h>
#include "FlexLibrary.h"

#define PORT = 80;

const int nFingers = 5;
const int flexPins[] = {7, 8, 9, 10, 11};
const int servoPins[] = {2, 3, 4, 5, 6};
//Set the server address
const char* serverAddress = "";

Flex flexes[nFingers](0);

Servo servos[nFingers];

int SERVO_ANGLE[nFingers];
int minVals[nFingers];
int maxVals[nFingers];

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

void initializeFlexes() {
  for (int i = 0; i < nFingers; i++) {
    flexes[i] = Flex(flexPins[i]);
    minVals[i] = flexes[i].getMinInput();
    maxVals[i] = flexes[i].getMaxInput();
    pinMode(flexPins[i], INPUT);
  }
}

void initializeServos() {
  for (int i = 0; i < nFingers; i++) {
    servos[i].attach(servoPins[i]);
  }
}

void calibrateSensors() {
  for (int i = 0; i < 10000; i++) {
    for (int i = 0; i < nFingers; i++) {
      flexes[i].Calibrate();
    }
  }
}

void setup() {
  initializeFlexes();
  initializeServos();

  calibrateSensors();

	Serial.begin(115200);
}

void reset() {
    for (int i = 0; i < nFingers; i++) {
      servos[i].write(90);
    }
    hasReset = true;
}

void updateServos() {

}

void loop() {
  if (!hasReset) {
    reset();
  }

  for (int i = 0; i < nFingers; i++) {

    flexes[i].updateVal();
    int flexValue = analogRead(flexPins[i]);
    int servoAngle = map(flexes[i].getSensorValue(), minVals[i], maxVals[i], 180, 0);
    
    servoAngle = constrain(servoAngle, 0, 180);

    if (SERVO_ANGLE[i] != servoAngle && isWithinThreshold(servoAngle)) {
      servos[i].write(servoAngle);
    }

    SERVO_ANGLE[i] = servoAngle;
  }
  // Serial.println(servoAngle);
}