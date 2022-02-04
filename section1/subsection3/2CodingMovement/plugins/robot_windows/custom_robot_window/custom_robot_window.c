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

#include <webots/motor.h>
#include <webots/plugins/robot_window/robot_wwi.h>
#include <webots/supervisor.h>

#include <math.h>
#include <stdio.h>

static WbNodeRef thymioRef = 0;

// Window initialization: get some robot devices.
void wb_robot_window_init() {
  thymioRef = wb_supervisor_node_get_from_def("THYMIO");
}

// A simulation step occurred.
void wb_robot_window_step(int time_step) {
  // Window initialization: get some robot devices.
  const char *message = wb_robot_wwi_receive_text();
  if (message) {
      fprintf(stdout, "Unkown message: '%s'\n", message);
  }


  // At each step, send the velocity value to JavaScript.
  const double* velocity = wb_supervisor_node_get_velocity(thymioRef);
  char answer[0x100];
  sprintf(answer, "velocity: %f, %d", velocity[0], time_step);
  wb_robot_wwi_send_text(answer);
}

void wb_robot_window_cleanup() {
  // This is called when the robot window is destroyed.
  // There is nothing to do here in this example.
  // This callback can be used to store information.
}
