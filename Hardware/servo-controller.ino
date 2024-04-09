#include <Servo.h>

Servo servo;

const int flexPin = A0;

void setup() {
  Serial.begin(9600);
  servo.attach(11);
}

void moveServo() {
    int sensorPos;
    int servoPos;
    sensorPos = analogRead(flexPin);
    servoPos = map(sensorPos, 800, 900, 0, 180);
    sensorPos = constrain(sensorPos, 0, 180);
    myServo.write(servoPos);
}

void loop() {
    moveServo(); 
    delay(80);
}
