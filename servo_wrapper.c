#include <Servo.h>
#include "wrapper.h"


Servo SERVO_obj;


void SERVO_Init() {
  SERVO_obj.attach(3);  // attach servo on pin 3 to servo object
  pinMode(SERVO_Echo, INPUT);
  pinMode(SERVO_Trig, OUTPUT);
}


//Ultrasonic distance measurement Sub function
int SERVO_CheckDistance() {
  digitalWrite(SERVO_Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(SERVO_Trig, HIGH);
  delayMicroseconds(20);
  digitalWrite(SERVO_Trig, LOW);
  float Fdistance = pulseIn(SERVO_Echo, HIGH);
  Fdistance= Fdistance / 58;
  return (int)Fdistance;
}

void SERVO_ChangeDirection(int dir) {
  dir = dir % 360;
  if (dir > 180) {
    dir = 360 - dir;
  }
  SERVO_obj.write(dir);
}
