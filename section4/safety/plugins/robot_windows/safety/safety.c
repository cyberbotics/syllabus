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

#include <webots/plugins/robot_window/robot_wwi.h>
#include <webots/robot.h>
#include <webots/supervisor.h>

#include <stdio.h>

WbNodeRef barriers[3], human;
WbFieldRef barriersTranslation[3], humansTranslation;
bool isBarriers, isBox, isHuman;

// Window initialization: get some robot devices.
void wb_robot_window_init() {
  isBarriers = false;
  isBox = false;
  isHuman = false;
  barriers[0] = wb_supervisor_node_get_from_def("BARRIER0");
  barriers[1] = wb_supervisor_node_get_from_def("BARRIER1");
  barriers[2] = wb_supervisor_node_get_from_def("BARRIER2");
  for (int i = 0; i < 3; i++)
    barriersTranslation[i] =
        wb_supervisor_node_get_field(barriers[i], "translation");
}

// A simulation step occurred.
void wb_robot_window_step(int time_step) {
  const char *message = wb_robot_wwi_receive_text();
  while (message) {
    if (strncmp(message, "barriers", strlen("barriers")) == 0) {
      for (int i = 0; i < 3; i++) {
        double *pos = wb_supervisor_field_get_sf_vec3f(barriersTranslation[i]);
        if (isBarriers) {
          pos[2] = -1000;
        } else {
          pos[2] = 0;
        }
        wb_supervisor_field_set_sf_vec3f(barriersTranslation[i], pos);
      }
      isBarriers = !isBarriers;
    }
    message = wb_robot_wwi_receive_text();
  }
}
