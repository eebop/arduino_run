#include "/Users/kieran/Documents/c_projects/arduino_lib/edge_wrapper.c"
#include "/Users/kieran/Documents/c_projects/arduino_lib/car_wrapper.c"
#include "/Users/kieran/Documents/c_projects/arduino_lib/servo_wrapper.c"

void setup() {
  EDGE_Init();
  CAR_Init();
  SERVO_Init();
}

void loop() {
  int directions[10];
  int distances[10];
  int branch[10];
  int branch_depth = 0;

}


int No_cliff() {
  return (EDGE_GetMiddleState() || EDGE_GetLeftState() || EDGE_GetRightState());
}


// returns degrees
int get_local_maximums(int **data, int **local_maximums) {
  int i;
  for (i=0; i!=120; i++;) {
    &local_maximums[i] = 1;
  }
  &data = get_data();
  loc = local_maximums(data, local_maximums);
  //ofset because of starting at 30 in get_data
  return loc + 30;
}

int *get_data() {
  int data[120];
  int i;
  for(i=30; i!=150; i++;) {
    SERVO_ChangeDirection(i);
    data[i-30] = SERVO_CheckDistance();
  }
}

int double_max(int x, int y) {
  if (x > y) {
    return 0;
  } else {
    return 1;
  }
}

int get_max_number(int x, int y) {
  int index = double_max(x, y);
  int answer;
  if (index == 0) {
    answer = x;
  } else {
    answer = y;
  }
  return answer;
}

int triple_max(int x, int y, int z) {
  int xy = get_max_number(x, y);
  int num = get_max_number(z, xy);
  int answer;

  if (num == x) {
    answer = 0;
  } else if (num == y) {
    answer = 1;
  } else if (num == z) {
    answer = 2;
  }
  return answer;
}

// returns 1 when it is the final iteration, 0 otherwise
// classic rolling solution
int update_local_maximums(int **data_p, int **max_p) {
  int *data = &data_p;
  int *max = &max_p;
  int loc;
  int maximum;
  int isdone = 1;
  for(loc=0; loc!=120; loc++;) {
    if (max[loc]) {
      if (loc == 0) {
        maximum = double_max(data[loc], data[loc+1]) + 1;
      } else if (loc == 119) {
        maximum = double_max(data[loc-1], data[loc]);
      } else {
        maximum = triple_max(data[loc-1], data[loc], data[loc+1]);
      }
      max[loc] = 0;
      max[maximum-1] = 1;
      if (maximum != 1) {
        isdone = 0;
      }
    }
  }
  return isdone;
}

//returns the number of local maximums, and puts the indexes in max_p
int local_maximums(int **data_p, int **max_p) {
  int *data = &data_p;
  int *maxes = &data_p;
  int isdone = 0;
  while (!isdone) {
    isdone = update_local_maximums(data_p, max_p);
  }
}

int is_dead_end(int *data) {
  int max = 0;
  int i;
  for(i=0; i!=120; i++;) {
    if (data[i] > max) {
      max = data[i];
    }
  }
  if (max < 30) {
    return 1;
  } else if (No_cliff()) {
    return 0;
  } else {
    return 1;
  }
}

int wall_ahead(int *data) {
  // 58 - 62 (inc)
  int i;
  int min = 100;
  for(i=58;i!=63;i++) {
    if (data[i] < min) {
      min = data[i];
    }
  }
  if (min < 20) {
    return 1;
  } else if (No_cliff()) {
    return 0;
  } else {
    return 1;
  }
}
void revert(int distance, int direction) {
  CAR_Backward(distance);
  CAR_Left(direction);
}

void turn(direction) {
  CAR_Right(CAR_Degrees_to_miliseconds(direction));
}
