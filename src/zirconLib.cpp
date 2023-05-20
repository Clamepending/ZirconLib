#include "zirconLib.h"
#include <Arduino.h>

Adafruit_BNO055 bno; // Define the Adafruit_BNO055 object

String ZirconVersion;
boolean compassCalibrated = false;

int motor1dir1;
int motor1dir2;
int motor1pwm;
int motor2dir1;
int motor2dir2;
int motor2pwm;
int motor3dir1;
int motor3dir2;
int motor3pwm;

int ballpin1;
int ballpin2;
int ballpin3;
int ballpin4;
int ballpin5;
int ballpin6;
int ballpin7;
int ballpin8;
int ballpins[8];

int buttonpin1;
int buttonpin2;
int buttonpins[2];


void InitializeZircon() {
  bno = Adafruit_BNO055(55, 0x28, &Wire);
  setZirconVersion();
  initializePins();
  CalibrateCompass();
}

void setZirconVersion() {
  pinMode(32, INPUT_PULLDOWN);

  if (digitalRead(32) == LOW) {
    ZirconVersion = "Mark1";
  } else {
    ZirconVersion = "Naveen1";
  }
}

void CalibrateCompass() {
  
  if (bno.begin())
  {
    // COMPASS DETECTED
    uint8_t system, gyro, accel, mag = 0;

    while (mag < 3 || gyro < 3) {
      bno.getCalibration(&system, &gyro, &accel, &mag);
      Serial.println("Calibrate your compass sensor!");
      Serial.println(String(mag) + "/3 magnetometer");
      Serial.println(String(gyro) + "/3 gyroscope");
      Serial.println();
      delay(100);

    }
    compassCalibrated = true;

  
  } else {
    // NO COMPASS DETECTED
    compassCalibrated = false;
  }

  
}

double readCompass() {
  if (compassCalibrated) {
    sensors_event_t orientationData;
    bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
    return orientationData.orientation.x;
  } else {
    Serial.println("Trying to read compass but compass is not calibrated! Check if compass is plugged in.");
    return 0;
  }
  
}

int readBall(int ballSensorNumber) {
  // ball sensor numbers are from 1 to 8
  // so to index into array we subtract 1
  return 1024 - analogRead(ballpins[ballSensorNumber - 1]); //flip the reading to make more intuitive sense (0 is see nothing)
}

int readButton(int buttonNumber) {
  // buttonNumber is from 1 to 2
  // so to index into array we subtract 1
  return digitalRead(buttonpins[buttonNumber - 1]);
}

void motor1(int power, bool direction) {
  digitalWrite(motor1dir1, direction);  // DIR 1
  digitalWrite(motor1dir2, !direction); // DIR 2
  analogWrite(motor1pwm, power);        // POWER
}

void motor2(int power, bool direction) {
  digitalWrite(motor2dir1, direction);
  digitalWrite(motor2dir2, !direction);
  analogWrite(motor2pwm, power);
}

void motor3(int power, bool direction) {
  digitalWrite(motor3dir1, direction);
  digitalWrite(motor3dir2, !direction);
  analogWrite(motor3pwm, power);
}

void initializePins() {
  if (ZirconVersion == "Mark1") {
    motor1dir1 = 2;
    motor1dir2 = 5;
    motor1pwm = 3;
    motor2dir1 = 8;
    motor2dir2 = 7;
    motor2pwm = 6;
    motor3dir1 = 12;
    motor3dir2 = 11;
    motor3pwm = 4;

    ballpin1 = 14;
    ballpin2 = 15;
    ballpin3 = 16;
    ballpin4 = 17;
    ballpin5 = 20;
    ballpin6 = 21;
    ballpin7 = 22;
    ballpin8 = 23;

    buttonpin1 = 9;
    buttonpin2 = 10;

  } else if (ZirconVersion == "Naveen1") {
    motor1dir1 = 2;
    motor1dir2 = 5;
    motor1pwm = 3;
    motor2dir1 = 8;
    motor2dir2 = 7;
    motor2pwm = 6;
    motor3dir1 = 12;
    motor3dir2 = 11;
    motor3pwm = 4;

    ballpin1 = 14;
    ballpin2 = 15;
    ballpin3 = 16;
    ballpin4 = 17;
    ballpin5 = 20;
    ballpin6 = 21;
    ballpin7 = 22;
    ballpin8 = 23;

    buttonpin1 = 9;
    buttonpin2 = 10;

  } else {
    motor1dir1 = 2;
    motor1dir2 = 5;
    motor1pwm = 3;
    motor2dir1 = 8;
    motor2dir2 = 7;
    motor2pwm = 6;
    motor3dir1 = 12;
    motor3dir2 = 11;
    motor3pwm = 4;

    ballpin1 = 14;
    ballpin2 = 15;
    ballpin3 = 16;
    ballpin4 = 17;
    ballpin5 = 20;
    ballpin6 = 21;
    ballpin7 = 22;
    ballpin8 = 23;

    buttonpin1 = 9;
    buttonpin2 = 10;
    
  }

  //initialize motor pins
  pinMode(motor1dir1, OUTPUT);
  pinMode(motor1dir2, OUTPUT);
  pinMode(motor1pwm, OUTPUT);
  pinMode(motor2dir1, OUTPUT);
  pinMode(motor2dir2, OUTPUT);
  pinMode(motor2pwm, OUTPUT);
  pinMode(motor3dir1, OUTPUT);
  pinMode(motor3dir2, OUTPUT);
  pinMode(motor3pwm, OUTPUT);

  //initialize ball sensor pins and line sensor pins
  pinMode(ballpin1, INPUT);
  pinMode(ballpin2, INPUT);
  pinMode(ballpin3, INPUT);
  pinMode(ballpin4, INPUT);
  pinMode(ballpin5, INPUT);
  pinMode(ballpin6, INPUT);
  pinMode(ballpin7, INPUT);
  pinMode(ballpin8, INPUT);
  pinMode(buttonpin1, INPUT);
  pinMode(buttonpin2, INPUT);
  
  int ballpins[8] = {ballpin1, ballpin2, ballpin3, ballpin4, ballpin5, ballpin6, ballpin7, ballpin8};
  int buttonpins[2] = {buttonpin1, buttonpin2};
}

String getZirconVersion() {
  return ZirconVersion;
}


bool isCompassCalibrated() {
  return compassCalibrated;
}


