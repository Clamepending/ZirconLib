#include <Arduino.h>
#include <Adafruit_BNO055.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);

void setZirconVersion();

void InitializeZircon();

void CalibrateCompass();

double readCompass();

int readBall(int ballSensorNumber);

void motor1(int power, boolean direction);

void motor2(int power, boolean direction);

void motor3(int power, boolean direction);

void initializePins();

String ZirconVersion;

const int motor1dir1;
const int motor1dir2;
const int motor1pwm;
const int motor2dir1;
const int motor2dir2;
const int motor2pwm;
const int motor3dir1;
const int motor3dir2;
const int motor3pwm;

const int ballpin1;
const int ballpin2;
const int ballpin3;
const int ballpin4;
const int ballpin5;
const int ballpin6;
const int ballpin7;
const int ballpin8;
int ballpins[8];

const int buttonpin1;
const int buttonpin2;




