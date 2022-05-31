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

#include <string.h>
#include <webots/camera.h>
#include <webots/distance_sensor.h>
#include <webots/motor.h>
#include <webots/position_sensor.h>
#include <webots/receiver.h>
#include <webots/robot.h>

#include <stdio.h>

#define TIME_STEP 32

enum State { WAITING, GRASPING, ROTATING, RELEASING, ROTATING_BACK, STOPPED };

int main(int argc, char **argv) {
  wb_robot_init();
  int counter = 0, i = 0;
  int state = WAITING;
  const double target_positions[] = {-1.88, -2.14, -2.38, -1.51};
  double speed = 1.0;
  bool oiled = false;
  bool calibrated = false;
  bool cleaned = false;
  bool stopped = false;

  if (argc == 2)
    sscanf(argv[1], "%lf", &speed);

  WbDeviceTag hand_motors[3];
  hand_motors[0] = wb_robot_get_device("finger_1_joint_1");
  hand_motors[1] = wb_robot_get_device("finger_2_joint_1");
  hand_motors[2] = wb_robot_get_device("finger_middle_joint_1");
  WbDeviceTag ur_motors[5];
  ur_motors[0] = wb_robot_get_device("shoulder_lift_joint");
  ur_motors[1] = wb_robot_get_device("elbow_joint");
  ur_motors[2] = wb_robot_get_device("wrist_1_joint");
  ur_motors[3] = wb_robot_get_device("wrist_2_joint");
  ur_motors[4] = wb_robot_get_device("shoulder_pan_joint");

  WbDeviceTag receiver = wb_robot_get_device("receiver");
  wb_receiver_enable(receiver, TIME_STEP);

  for (i = 0; i < 5; ++i)
    wb_motor_set_velocity(ur_motors[i], speed);

  WbDeviceTag distance_sensor = wb_robot_get_device("distance sensor");
  wb_distance_sensor_enable(distance_sensor, TIME_STEP);

  WbDeviceTag position_sensor = wb_robot_get_device("wrist_1_joint_sensor");
  wb_position_sensor_enable(position_sensor, TIME_STEP);

  WbDeviceTag camera = wb_robot_get_device("camera");
  wb_camera_enable(camera, TIME_STEP);

  bool saccade = false;
  while (wb_robot_step(TIME_STEP) != -1) {
    if (counter % 4 == 0) {
      if (oiled)
        speed = 1;
      else {
        if (saccade)
          speed = 2;
        else
          speed = 0;
        saccade = !saccade;
      }
      wb_motor_set_velocity(ur_motors[0], speed);
    }

    if (calibrated) {
      wb_motor_set_position(ur_motors[4], 0.2618);
    }

    if (counter <= 0) {
      switch (state) {
      case WAITING:
        if (wb_distance_sensor_get_value(distance_sensor) < 500) {
          state = GRASPING;
          counter = 8;
          printf("Grasping can\n");
          const unsigned char *image = wb_camera_get_image(camera);
          if (cleaned && wb_camera_image_get_green(image, 1, 0, 0) <
                             wb_camera_image_get_red(image, 1, 0, 0)) {
            for (i = 0; i < 3; ++i)
              wb_motor_set_position(hand_motors[i], 0.85);
          }
        }
        break;
      case GRASPING:
        for (i = 0; i < 4; ++i)
          wb_motor_set_position(ur_motors[i], target_positions[i]);
        printf("Rotating arm\n");
        state = ROTATING;
        break;
      case ROTATING:
        if (wb_position_sensor_get_value(position_sensor) < -2.3) {
          counter = 8;
          printf("Releasing can\n");
          state = RELEASING;
          for (i = 0; i < 3; ++i)
            wb_motor_set_position(hand_motors[i],
                                  wb_motor_get_min_position(hand_motors[i]));
        }
        break;
      case RELEASING:
        for (i = 0; i < 4; ++i)
          wb_motor_set_position(ur_motors[i], 0.0);
        printf("Rotating arm back\n");
        state = ROTATING_BACK;
        break;
      case ROTATING_BACK:
        if (wb_position_sensor_get_value(position_sensor) > -0.1) {
          state = WAITING;
          printf("Waiting can\n");
        }
        break;
      }
    }

    while (wb_receiver_get_queue_length(receiver) > 0) {
      const char *buffer = wb_receiver_get_data(receiver);
      if (strncmp(buffer, "oil", strlen("oil")) == 0)
        oiled = true;
      else if (strncmp(buffer, "calibrate", strlen("oil")) == 0)
        calibrated = true;
      else if (strncmp(buffer, "camera", strlen("cleaned")) == 0) {
        cleaned = true;
      } else if (strncmp(buffer, "prepare", strlen("prepare")) == 0) {
        if (!stopped) {
          for (i = 0; i < 4; ++i)
            wb_motor_set_position(ur_motors[i], 0.0);
          for (i = 0; i < 3; ++i)
            wb_motor_set_position(hand_motors[i],
                                  wb_motor_get_min_position(hand_motors[i]));
          state = STOPPED;
          stopped = true;
        } else {
          stopped = false;
          state = WAITING;
        }
      } else if (strncmp(buffer, "cycle", strlen("prepare")) == 0) {
        for (i = 0; i < 4; ++i)
          wb_motor_set_position(ur_motors[i], target_positions[i]);
        for (i = 0; i < 3; ++i)
            wb_motor_set_position(hand_motors[i],
                                  wb_motor_get_min_position(hand_motors[i]));
        state = RELEASING;
        counter = 24;
      }

      wb_receiver_next_packet(receiver);
    }
    counter--;
  };

  wb_robot_cleanup();
  return 0;
}
