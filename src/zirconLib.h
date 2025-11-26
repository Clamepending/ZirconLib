#pragma once
#include <Arduino.h>
#include <Adafruit_BNO055.h>

void setZirconVersion();

// 1 = Original Hardware (Default), 15 = New Hardware
void InitializeZircon(int hardwareVersion = 1);

void CalibrateCompass();

double readCompass();

int readBall(int ballSensorNumber);

int readLine(int lineNumber);

int readButton(int buttonNumber);

void motor1(int power, bool direction);

void motor2(int power, bool direction);

void motor3(int power, bool direction);

void initializePins(int hardwareVersion);

String getZirconVersion();
