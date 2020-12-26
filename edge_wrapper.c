#include "wrapper.h"
void EDGE_Init() {
  pinMode(EDGE_Right, INPUT);
  pinMode(EDGE_Middle, INPUT);
  pinMode(EDGE_Left, INPUT);
}

int EDGE_GetRightState() {
  return digitalRead(EDGE_Right);
}

int EDGE_GetMiddleState() {
  return digitalRead(EDGE_Middle);
}

int EDGE_GetLeftState() {
  return digitalRead(EDGE_Left);
}
