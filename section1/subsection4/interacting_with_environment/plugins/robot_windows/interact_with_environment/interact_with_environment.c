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

// Window initialization: get some robot devices.
void wb_robot_window_init() { printf("init\n"); }

int bottle_counter = '0';
int bottle_added = 0; // Allow the addition of only one bottle every 5 time step


// A simulation step occurred.
void wb_robot_window_step(int time_step) {
  const char *message = wb_robot_wwi_receive_text();
  if (bottle_added > 0)
    bottle_added--;
  while (message) {
    printf("%s\n", message);
    fflush(stdout);
    WbNodeRef root_node = wb_supervisor_node_get_root();
    WbFieldRef root_children_field =
        wb_supervisor_node_get_field(root_node, "children");

    if (strncmp(message, "waterbottle", 11) == 0) {
      if (!bottle_added) {
        if (bottle_counter <= '9') {
          char name[7] = "BOTTLE0";
          name[6] = bottle_counter;
          fflush(stdout);
          WbNodeRef bottle = wb_supervisor_node_get_from_def(name);
          WbFieldRef bottle_translation = wb_supervisor_node_get_field(bottle, "translation");
          const double position[3] = {4.9, -0.83, 0.6};
          wb_supervisor_field_set_sf_vec3f(bottle_translation, position);
          bottle_counter++;
        } else {
          wb_supervisor_field_import_mf_node_from_string(root_children_field, -1, "WaterBottle{translation 4.9 -0.83 0.7}");
        }
        bottle_added = 100;
      }
    } else if (strncmp(message, "storage", 7) == 0) {
      WbNodeRef storageNode = wb_supervisor_node_get_from_def("STORAGE");
      if (storageNode)
        wb_supervisor_node_remove(storageNode);
    } else if (strncmp(message, "cardboardBox", 12) == 0) {
      WbNodeRef box1 = wb_supervisor_node_get_from_def("BOX1");
      WbNodeRef box2 = wb_supervisor_node_get_from_def("BOX2");
      WbNodeRef box3 = wb_supervisor_node_get_from_def("BOX3");
 
      WbFieldRef box1_translation = wb_supervisor_node_get_field(box1, "translation");
      WbFieldRef box2_translation = wb_supervisor_node_get_field(box2, "translation");
      WbFieldRef box3_translation = wb_supervisor_node_get_field(box3, "translation");

      const double position1[3] = {0.219139, 0.941823, 0.3};
      wb_supervisor_field_set_sf_vec3f(box1_translation, position1);
      const double position2[3] = {0.320341, 0.846947, 0.75};
      wb_supervisor_field_set_sf_vec3f(box2_translation, position2);
      const double position3[3] = {0.30946, 0.834497, 1.15};
      wb_supervisor_field_set_sf_vec3f(box3_translation, position3);
    } else
      fprintf(stderr, "Unkown message: '%s'\n", message);

    message = wb_robot_wwi_receive_text();
  }
}
