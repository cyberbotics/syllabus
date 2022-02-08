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
 * Description:  An example of a controller using a pen device which you can
 *               turn on and off using the defined keys.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <webots/accelerometer.h>
#include <webots/altimeter.h>
#include <webots/camera.h>
#include <webots/compass.h>
#include <webots/distance_sensor.h>
#include <webots/gps.h>
#include <webots/gyro.h>
#include <webots/light_sensor.h>
#include <webots/motor.h>
#include <webots/robot.h>

#define SPEED 6.67
#define TIME_STEP 64

static double clamp(double value, double min, double max) {
  if (min > max) {
    assert(0);
    return value;
  }
  return value < min ? min : value > max ? max : value;
}

int main() {
  WbDeviceTag ds0, ds1, left_motor, right_motor;
  int left_speed, right_speed;
  double max_speed;

  wb_robot_init();

  /* get a handler to the distance sensors. */
  ds0 = wb_robot_get_device("ds0");
  ds1 = wb_robot_get_device("ds1");

  wb_distance_sensor_enable(ds0, TIME_STEP);
  wb_distance_sensor_enable(ds1, TIME_STEP);
  
  WbDeviceTag altimeter = wb_robot_get_device("altimeter");
  wb_altimeter_enable(altimeter, TIME_STEP);
  
  WbDeviceTag accelerometer = wb_robot_get_device("accelerometer");
  wb_accelerometer_enable(accelerometer, TIME_STEP);
  
  WbDeviceTag camera = wb_robot_get_device("camera");
  wb_camera_enable(camera, TIME_STEP);
  
  WbDeviceTag compass = wb_robot_get_device("compass");
  wb_compass_enable(compass, TIME_STEP);
  
  WbDeviceTag gps = wb_robot_get_device("gps");
  wb_gps_enable(gps, TIME_STEP);
  
  WbDeviceTag gyro = wb_robot_get_device("gyro");
  wb_gyro_enable(gyro, TIME_STEP);
  
  WbDeviceTag light_sensor = wb_robot_get_device("light sensor");
  wb_light_sensor_enable(light_sensor, TIME_STEP);


  /* get a handler to the motors and set target position to infinity (speed control). */
  left_motor = wb_robot_get_device("left wheel motor");
  right_motor = wb_robot_get_device("right wheel motor");
  wb_motor_set_position(left_motor, INFINITY);
  wb_motor_set_position(right_motor, INFINITY);
  wb_motor_set_velocity(left_motor, 0.0);
  wb_motor_set_velocity(right_motor, 0.0);
  max_speed = wb_motor_get_max_velocity(left_motor);

  while (wb_robot_step(TIME_STEP) != -1) {
    const double ds0_value = wb_distance_sensor_get_value(ds0);
    const double ds1_value = wb_distance_sensor_get_value(ds1);

    if (ds1_value > 500) {
      /*
       * If both distance sensors are detecting something, this means that
       * we are facing a wall. In this case we need to move backwards.
       */
      if (ds0_value > 200) {
        left_speed = -SPEED;
        right_speed = -SPEED / 2;
      } else {
        /*
         * We turn proportionally to the sensors value because the
         * closer we are from the wall, the more we need to turn.
         */
        left_speed = -ds1_value / 50;
        right_speed = ds0_value / 50;
        left_speed = clamp(left_speed, -max_speed, max_speed);
        right_speed = clamp(right_speed, -max_speed, max_speed);
      }
    } else if (ds0_value > 500) {
      left_speed = ds1_value / 50;
      right_speed = -ds0_value / 50;
      left_speed = clamp(left_speed, -max_speed, max_speed);
      right_speed = clamp(right_speed, -max_speed, max_speed);
    } else {
      /*
       * If nothing was detected we can move forward at maximal speed.
       */
      left_speed = SPEED;
      right_speed = SPEED;
    }

    /* Set the motor speeds. */
    wb_motor_set_velocity(left_motor, left_speed);
    wb_motor_set_velocity(right_motor, right_speed);
  }

  wb_robot_cleanup();

  return 0;
}
