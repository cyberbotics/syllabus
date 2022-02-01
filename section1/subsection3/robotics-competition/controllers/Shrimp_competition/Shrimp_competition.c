/*
 * Copyright 1996-2022 Cyberbotics Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Description:  The controller used to move the shrimp with the keyboard.
 */

#include <stdio.h>
#include <string.h>
#include <webots/robot.h>
#include "shrimp_protocol.h"

#define TIME_STEP 64
#define MAX_BUFFER_SIZE 4
#define MAX_STRING_SIZE 1024
#define WHEELS_NUMBER 6

#define MAX_VELOCITY 127
#define MAX_DIRECTION 90

static int velocity;
static int direction;

int main() {

  wb_robot_init();
  shrimp_init();

  while (wb_robot_step(TIME_STEP) != -1) {
    unsigned char buffer[MAX_BUFFER_SIZE];
  
    velocity = 127;
    direction = 0;
    buffer[0] = 0x04;
    buffer[1] = (unsigned char)velocity;
    buffer[2] = (unsigned char)direction;
    shrimp_send(buffer);
  }
  wb_robot_cleanup();

  return 0;
}
