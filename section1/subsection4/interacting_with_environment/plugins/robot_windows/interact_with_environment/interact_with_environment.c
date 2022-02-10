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
void wb_robot_window_init() {printf("init\n");}

// A simulation step occurred.
void wb_robot_window_step(int time_step) {

  // Window initialization: get some robot devices.
  const char *message = wb_robot_wwi_receive_text();
  if (message) {
    WbNodeRef root_node = wb_supervisor_node_get_root();
    WbFieldRef root_children_field = wb_supervisor_node_get_field(root_node, "children");

    if (strncmp(message, "waterbottle", 11) == 0)
      wb_supervisor_field_import_mf_node_from_string(root_children_field, -1, "WaterBottle{translation 4.9 -0.83 0.6}");
    else if (strncmp(message, "storage", 7) == 0) {
      WbNodeRef storageNode = wb_supervisor_node_get_from_def("STORAGE");
      if (storageNode)
        wb_supervisor_node_remove(storageNode);
    } else if (strncmp(message, "cardboardBox", 12) == 0) {
      wb_supervisor_field_import_mf_node_from_string(root_children_field, -1, "CardboardBox{translation 0.219139 0.941823 0.3 size 0.5 0.5 0.6 mass 0.4}");
      wb_supervisor_field_import_mf_node_from_string(root_children_field, -1, "CardboardBox{translation 0.320341 0.846947 0.75 rotation 0 0 1 2.094395 size 0.4 0.6 0.3 mass 0.4}");
      wb_supervisor_field_import_mf_node_from_string(root_children_field, -1, "CardboardBox{translation 0.30946 0.834497 1.15 rotation 0 0 1 -0.5235 size 0.5 0.5 0.5 mass 0.4}");
    }
    else
      fprintf(stderr, "Unkown message: '%s'\n", message);
  }
}
