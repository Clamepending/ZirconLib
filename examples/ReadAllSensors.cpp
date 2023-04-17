#include <Arduino.h>
#include <zirconLib.h>


void setup(void)
{
  Serial.begin(115200);
  InitializeZircon();

}


void loop(void)
{

  Serial.println("reading sensors ");
  Serial.println("ball sensor 1: " + String(readBall(1)));
  Serial.println("ball sensor 2: " + String(readBall(2)));
  Serial.println("ball sensor 3: " + String(readBall(3)));
  Serial.println("ball sensor 4: " + String(readBall(4)));
  Serial.println("ball sensor 5: " + String(readBall(5)));
  Serial.println("ball sensor 6: " + String(readBall(6)));
  Serial.println("ball sensor 7: " + String(readBall(7)));
  Serial.println("ball sensor 8: " + String(readBall(8)));
  Serial.println("push button 1: " + String(digitalRead(9)));
  Serial.println("push button 2: " + String(digitalRead(10)));
  Serial.println("orientation: " + String(readCompass()));
  Serial.println("current runtime: " + String(millis()) + " milliseconds");
  Serial.println("--------------------------------------");


  //first number is power, second is direction
  //ex: motor1(100, 1) spins motor 1 at 100/255 speed in one direction
  //ex: motor1(255, 0) spins motor 1 at 255/255 (100%) speed in the other direction
  motor1(100, 1);
  motor2(50, 0);
  motor3(255, 1);
  delay(1000); // freeze program for 1 second

  //stop by writing 0 power to all motors (direction doesnt matter)
  motor1(0, 1);
  motor2(0, 0);
  motor3(0, 1);
  delay(1000); // freeze program for 1 second




}