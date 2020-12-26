#include "/Users/kieran/Documents/c_projects/arduino_lib/wrapper.h"

#define CAR_Fast CAR_Unfreeze

/*
 ENA   ENB   IN1   IN2   IN3   IN4
 HIGH  HIGH  HIGH  LOW   LOW   HIGH  forward
 HIGH  HIGH  LOW   HIGH  HIGH  LOW   back
 HIGH  HIGH  LOW   HIGH  LOW   HIGH  left
 HIGH  HIGH  HIGH  LOW   HIGH  LOW   right
 HIGH  HIGH  LOW   LOW   LOW   LOW   stop
 HIGH  HIGH  HIGH  HIGH  HIGH  HIGH  stop
 LOW   LOW   N/A   N/A   N/A   N/A   stop (Default)

 Left motor truth table
 ENA         IN1               IN2         Description
 LOW         N/A               N/A         Motor is off
 HIGH        LOW               LOW         Motor is stopped (brakes)
 HIGH        HIGH              LOW         Motor is on and turning forwards
 HIGH        LOW               HIGH        Motor is on and turning backwards
 HIGH        HIGH              HIGH        Motor is stopped (brakes)

   Right motor truth table
 ENB         IN3             IN4         Description
 LOW         N/A             N/A         Motor is off
 HIGH        LOW             LOW         Motor is stopped (brakes)
 HIGH        LOW             HIGH        Motor is on and turning forwards
 HIGH        HIGH            LOW         Motor is on and turning backwards
 HIGH        HIGH            HIGH        Motor is stopped (brakes)

   Left motor truth table
 stop(off)     stop(off)       Car is stopped
 forward       forward         Car is running forwards
 forward       backward        Car is turning right
 backward      forward         Car is turning left
 backward      backward        Car is running backwards
*/
void CAR_Unfreeze() {
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
}

void CAR_Init() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  CAR_Unfreeze();
}


void CAR_Freeze() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
}

void CAR_Slow() {
  analogWrite(ENA, 128);
  analogWrite(ENA, 128);
}

void CAR_Move(int in1, int in2, int in3, int in4) {
  CAR_Slow();
  delay(1000);
  CAR_Freeze();
  digitalWrite(IN1, in1);
  digitalWrite(IN2, in2);
  digitalWrite(IN3, in3);
  digitalWrite(IN4, in4);
  delay(1000);
  CAR_Slow();
  delay(1000);
  CAR_Fast();
}

void CAR_Forward() {
  CAR_Move(HIGH, LOW, LOW, HIGH);
}

void CAR_Backward() {
  CAR_Move(LOW, HIGH, HIGH, LOW);
}

void CAR_Left() {
  CAR_Move(LOW, HIGH, LOW, HIGH);
}

void CAR_Right() {
  CAR_Move(HIGH, LOW, HIGH, LOW);
}

int CAR_Degrees_to_miliseconds(int degrees) {
  double answer = (double) degrees * 5.55;
  return (int) answer;
}
