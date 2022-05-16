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

WbNodeRef car1, car2, car3;
WbFieldRef translations[3];

// Window initialization: get some robot devices.
void wb_robot_window_init() {
  car1 = wb_supervisor_node_get_from_def("CAR1");
  car2 = wb_supervisor_node_get_from_def("CAR2");
  car3 = wb_supervisor_node_get_from_def("CAR3");
  
  translation[0] = wb_supervisor_node_get_field(car1, "translation");
  translation[1] = wb_supervisor_node_get_field(car2, "translation");
  translation[2] = wb_supervisor_node_get_field(car3, "translation");
}

// A simulation step occurred.
void wb_robot_window_step(int time_step) {
  const char *message = wb_robot_wwi_receive_text();
  while (message) {

    message = wb_robot_wwi_receive_text();
  }
  
  for (int i = 0; i < 3; i++) {
    const double * pos = wb_supervisor_field_get_sf_vec3f(translation[i]);
    if (pos[1] >
  }
}
