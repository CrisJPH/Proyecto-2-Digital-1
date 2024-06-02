include <Servo.h>
#include <stdint.h>
#include <arduino.h>

int angulo;
int a = 0;
void setup(){

  Serial.begin(9600);
  while (!Serial);
}
