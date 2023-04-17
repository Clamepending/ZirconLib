#include "zirconLib.h"

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);

void InitializeZircon() {
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
  // TODO: DONT CALIBRATE IF DETECT NO COMPASS

  bno.begin();
  uint8_t system, gyro, accel, mag = 0;
  while (mag < 3 || gyro < 3) {
    bno.getCalibration(&system, &gyro, &accel, &mag);
    Serial.println("Calibrate your comapass sensor!");
    Serial.println(String(mag) + "/3 magnitometer");
    Serial.println(String(gyro) + "/3 gyroscope");
    Serial.println();
    delay(100);
  }
}

double readCompass() {
  sensors_event_t orientationData;
  bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
  return orientationData.orientation.x;
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

void motor1(int power, boolean direction) {
  digitalWrite(motor1dir1, direction);//DIR 1
  digitalWrite(motor1dir2, !direction);//DIR 2
  analogWrite(motor1pwm, power);//POWER
}

void motor2(int power, boolean direction) {
  digitalWrite(motor2dir1, direction);
  digitalWrite(motor2dir2, !direction);
  analogWrite(motor2pwm, power);
}

void motor3(int power, boolean direction) {
  digitalWrite(motor3dir1, direction);
  digitalWrite(motor3dir2, !direction);
  analogWrite(motor3pwm, power);
}

void initializePins() {
  if (ZirconVersion == "Mark1") {
    const int motor1dir1 = 2;
    const int motor1dir2 = 5;
    const int motor1pwm = 3;
    const int motor2dir1 = 8;
    const int motor2dir2 = 7;
    const int motor2pwm = 6;
    const int motor3dir1 = 12;
    const int motor3dir2 = 11;
    const int motor3pwm = 4;

    const int ballpin1 = 14;
    const int ballpin2 = 15;
    const int ballpin3 = 16;
    const int ballpin4 = 17;
    const int ballpin5 = 20;
    const int ballpin6 = 21;
    const int ballpin7 = 22;
    const int ballpin8 = 23;

    const int buttonpin1= 9;
    const int buttonpin2 = 10;

  } else if (ZirconVersion == "Naveen1") {
    const int motor1dir1 = 2;
    const int motor1dir2 = 5;
    const int motor1pwm = 3;
    const int motor2dir1 = 8;
    const int motor2dir2 = 7;
    const int motor2pwm = 6;
    const int motor3dir1 = 12;
    const int motor3dir2 = 11;
    const int motor3pwm = 4;

    const int ballpin1 = 14;
    const int ballpin2 = 15;
    const int ballpin3 = 16;
    const int ballpin4 = 17;
    const int ballpin5 = 20;
    const int ballpin6 = 21;
    const int ballpin7 = 22;
    const int ballpin8 = 23;

    const int buttonpin1= 9;
    const int buttonpin2 = 10;
    
  } else {
    while (!Serial.available());
    Serial.println("Zircon Version Not defined!, Check if teensy is properly plugged into the robot circuit board");
    const int motor1dir1 = 2;
    const int motor1dir2 = 5;
    const int motor1pwm = 3;
    const int motor2dir1 = 8;
    const int motor2dir2 = 7;
    const int motor2pwm = 6;
    const int motor3dir1 = 12;
    const int motor3dir2 = 11;
    const int motor3pwm = 4;

    const int ballpin1 = 14;
    const int ballpin2 = 15;
    const int ballpin3 = 16;
    const int ballpin4 = 17;
    const int ballpin5 = 20;
    const int ballpin6 = 21;
    const int ballpin7 = 22;
    const int ballpin8 = 23;

    const int buttonpin1= 9;
    const int buttonpin2 = 10;
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

