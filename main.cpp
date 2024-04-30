#include <Servo.h>

Servo base;
Servo joint1;
Servo joint2;
Servo wrist;
Servo gripper;

int dataServo1 = 90;
int dataServo2 = 90;
int dataServo3 = 90;
int dataServo4 = 0;
int dataServo5 = 90;

float dirServo1Offset = 0;  
float dirServo2Offset = 0;  
float dirServo3Offset = 0;
float dirServo4Offset = 0;  
float dirServo5Offset = 20;  

int baseEncoder;
int joint1Encoder;
int joint2Encoder;
int wristEncoder;
int gripperEncoder;

int servoTarget1 = dataServo1;
int servoTarget2 = dataServo2;
int servoTarget3 = dataServo3;
int servoTarget4 = dataServo4;
int servoTarget5 = dataServo5;

float kP = 0.3;

int angleChange = 20;

char input;
boolean receivingInput;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting arm");
 
  base.attach(9);
  joint1.attach(6);
  joint2.attach(5);
  wrist.attach(3);
  gripper.attach(11);

  base.write(dataServo1+dirServo1Offset);
  joint1.write(dataServo2+dirServo2Offset);
  joint2.write(dataServo3+dirServo3Offset);
  wrist.write(dataServo4+dirServo4Offset);
  gripper.write(dataServo5+dirServo5Offset);
}

void loop() {
  Serial.print("Data Servo1: ");
  Serial.print(dataServo1);
  Serial.print(", Servo Target 1: ");
  Serial.println(servoTarget1);
 
  Serial.print("Data Servo2: ");
  Serial.print(dataServo2);
  Serial.print(", Servo Target 2: ");
  Serial.println(servoTarget2);
 
  if (dataServo1 != servoTarget1) {
    dataServo1 += (servoTarget1 - dataServo1) * kP;
  }
  if (dataServo2 != servoTarget2) {
    dataServo2 += (servoTarget2 - dataServo2) * kP;
  }
  if (dataServo3 != servoTarget3) {
    dataServo3 += (servoTarget3 - dataServo3) * kP;
  }
  if (dataServo4 != servoTarget4) {
    dataServo4 += (servoTarget4 - dataServo4) * kP;
  }
  if (dataServo5 != servoTarget5) {
    dataServo5 += (servoTarget5 - dataServo5) * kP;
  }
 
  // put your main code here, to run repeatedly:
  base.write(dataServo1+dirServo1Offset);
  joint1.write(dataServo2+dirServo2Offset);
  joint2.write(dataServo3+dirServo3Offset);
  wrist.write(dataServo4+dirServo4Offset);
  gripper.write(dataServo5+dirServo5Offset);

  getInput();
  showInput();

  switch (input) {
    case 'w':
      if (servoTarget2 <= 180 - angleChange)
        servoTarget2 += angleChange;
      break;
    case 'd':
      if (servoTarget1 >= 0 + angleChange)
        servoTarget1 -= angleChange;
      break;
    case 'a':
      if (servoTarget1 <= 180 - angleChange)
        servoTarget1 += angleChange;
      break;
    case 's':
      if (servoTarget2 >= -30 + angleChange)
        servoTarget2 -= angleChange;
      break;
    case '1':
      servoTarget3 += angleChange;
      break;
    case '2':
      servoTarget3 -= angleChange;
      break;
    case '9':
      servoTarget5 += angleChange;
      break;
    case '0':
      servoTarget5 -= angleChange;
      break;
  }
}

void getInput() {
  if (Serial.available() > 0) {
    input = Serial.read();
    receivingInput = true;
  } else {
    receivingInput = false;
  }
}

void showInput() {
  if (receivingInput) {
    Serial.println(input);
  }
}
