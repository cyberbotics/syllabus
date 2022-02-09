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
 * Description:  This controller is used to move the mecanum-wheeled robot
 * Summit-XL Steel in an industrial environment using the keyboard. The keys are
 * the following:
 *
 *               vx: ↑/↓
 *               vy: ←/→
 *               ω: Page Up/Page Down
 *               Reset: Space bar
 */

#include <stdio.h>

#include <string.h>
#include <webots/motor.h>
#include <webots/robot.h>

#define WHEEL_RADIUS 0.123
#define LX 0.2045 // lateral distance from robot's COM to wheel [m].
#define LY 0.2225 // longitudinal distance from robot's COM to wheel [m].
#define SPEED_INCREMENT 0.1
#define MAX_SPEED 1.5

int main() {
  wb_robot_init();

  const int time_step = wb_robot_get_basic_time_step();

  WbDeviceTag motor_fl = wb_robot_get_device("front_left_wheel_joint");
  WbDeviceTag motor_fr = wb_robot_get_device("front_right_wheel_joint");
  WbDeviceTag motor_bl = wb_robot_get_device("back_left_wheel_joint");
  WbDeviceTag motor_br = wb_robot_get_device("back_right_wheel_joint");

  // Velocity control, so position must be set to infinity.
  wb_motor_set_position(motor_fl, INFINITY);
  wb_motor_set_position(motor_fr, INFINITY);
  wb_motor_set_position(motor_bl, INFINITY);
  wb_motor_set_position(motor_br, INFINITY);

  wb_motor_set_velocity(motor_fl, 10.0);
  wb_motor_set_velocity(motor_fr, 10.0);
  wb_motor_set_velocity(motor_bl, 10.0);
  wb_motor_set_velocity(motor_br, 10.0);
  while (wb_robot_step(time_step) != -1) {
    const char *custom_data = wb_robot_get_custom_data();
    if (strcmp(custom_data, "stop") == 0) {
      wb_motor_set_velocity(motor_fl, 0);
      wb_motor_set_velocity(motor_fr, 0);
      wb_motor_set_velocity(motor_bl, 0);
      wb_motor_set_velocity(motor_br, 0);
      wb_robot_cleanup();
      return 0;
    }
  }
}
