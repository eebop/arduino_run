#ifndef _WRAPPER_H
#define _WRAPPER_H
#include <stdio.h>

#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#define SERVO_Echo A4
#define SERVO_Trig A5
#define EDGE_Right 10
#define EDGE_Middle 4
#define EDGE_Left 2

#ifdef _COMMAND_LINE_MODE

  int pinMode(int a, int b) {
    printf("Cannot use command-line mode to execute a pinMode command\n");
    return 1;
  }

  int digitalWrite(int a, int b) {
    printf("Cannot use command-line mode to execute a digitalWrite command\n");
    return 1;
  }

  int digitalRead(int a, int b) {
    printf("Cannot use command-line mode to execute a digitalRead command\n");
    return 1;
  }
  #define LOW 0
  #define HIGH 1
  #define INPUT 0
  #define OUTPUT 1
  #define INPUT_PULLUP 2
#endif
#endif
