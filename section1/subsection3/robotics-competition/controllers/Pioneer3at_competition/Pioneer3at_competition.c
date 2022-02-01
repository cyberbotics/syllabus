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
 * Description:  Example of Sick LMS 291.
 *               The velocity of each wheel is set
 *               according to a Braitenberg-like algorithm which takes the values returned by the Sick as input.
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <webots/motor.h>
#include <webots/robot.h>

#define TIME_STEP 32
#define CRUISING_SPEED 5.0

int main(int argc, char **argv) {
  // init webots stuff
  wb_robot_init();

  // get devices
  WbDeviceTag front_left_wheel = wb_robot_get_device("front left wheel");
  WbDeviceTag front_right_wheel = wb_robot_get_device("front right wheel");
  WbDeviceTag back_left_wheel = wb_robot_get_device("back left wheel");
  WbDeviceTag back_right_wheel = wb_robot_get_device("back right wheel");

  // init motors
  wb_motor_set_position(front_left_wheel, INFINITY);
  wb_motor_set_position(front_right_wheel, INFINITY);
  wb_motor_set_position(back_left_wheel, INFINITY);
  wb_motor_set_position(back_right_wheel, INFINITY);

  // init speed for each wheel
  double back_left_speed = 0.0, back_right_speed = 0.0;
  double front_left_speed = 0.0, front_right_speed = 0.0;
  wb_motor_set_velocity(front_left_wheel, front_left_speed);
  wb_motor_set_velocity(front_right_wheel, front_right_speed);
  wb_motor_set_velocity(back_left_wheel, back_left_speed);
  wb_motor_set_velocity(back_right_wheel, back_right_speed);

  // control loop
  while (wb_robot_step(TIME_STEP) != -1) {
    // set actuators
    wb_motor_set_velocity(front_left_wheel, CRUISING_SPEED);
    wb_motor_set_velocity(front_right_wheel, CRUISING_SPEED);
    wb_motor_set_velocity(back_left_wheel, CRUISING_SPEED);
    wb_motor_set_velocity(back_right_wheel, CRUISING_SPEED);

  }

  wb_robot_cleanup();

  return 0;
}
