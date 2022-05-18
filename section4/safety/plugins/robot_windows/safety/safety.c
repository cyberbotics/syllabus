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

WbNodeRef barriers[3], box, worker;
WbFieldRef barriersTranslation[3], boxTranslation, workerTranslation,
    workerRotation;
bool isBarriers, isBox, isWorker1, isWorker2;

// Window initialization: get some robot devices.
void wb_robot_window_init() {
  isWorker1 = false;
  isWorker2 = false;
  isBarriers = false;
  isBox = false;

  // Get NodeRefs
  worker = wb_supervisor_node_get_from_def("WORKER");
  barriers[0] = wb_supervisor_node_get_from_def("BARRIER0");
  barriers[1] = wb_supervisor_node_get_from_def("BARRIER1");
  barriers[2] = wb_supervisor_node_get_from_def("BARRIER2");
  box = wb_supervisor_node_get_from_def("BOX");

  // Get FieldRefs
  workerTranslation = wb_supervisor_node_get_field(worker, "translation");
  workerRotation = wb_supervisor_node_get_field(worker, "rotation");
  for (int i = 0; i < 3; i++)
    barriersTranslation[i] =
        wb_supervisor_node_get_field(barriers[i], "translation");
  boxTranslation = wb_supervisor_node_get_field(box, "translation");
}

void change_human() {
  double pos[3] = {-1000, -1000, 0};
  if (isWorker1 || isWorker2)
    isWorker1 = isWorker2 = false;
  else if (isBarriers || isBox) {
    pos[0] = -1.82;
    pos[1] = 2.9;
    isWorker2 = true;
  } else {
    pos[0] = -1.82;
    pos[1] = 1.65;
    isWorker1 = true;
  }

  double rotation[4] = {0, 0, 1, 0};
  wb_supervisor_field_set_sf_rotation(workerRotation, rotation);
  wb_supervisor_field_set_sf_vec3f(workerTranslation, pos);
  wb_supervisor_node_reset_physics(worker);
}

void change_barriers() {
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

void change_box() {
  double *pos = wb_supervisor_field_get_sf_vec3f(boxTranslation);
  if (isBox) {
    pos[2] = -1000;
  } else {
    pos[2] = 2;
  }
  wb_supervisor_field_set_sf_vec3f(boxTranslation, pos);
  isBox = !isBox;
}

// A simulation step occurred.
void wb_robot_window_step(int time_step) {
  const char *message = wb_robot_wwi_receive_text();
  while (message) {
    if (strncmp(message, "human", strlen("human")) == 0) {
      change_human();
    } else if (strncmp(message, "barriers", strlen("barriers")) == 0) {
      change_barriers();
      if (isBox && isBarriers)
        change_box();

      if ((isWorker1 && isBarriers) || (isWorker2 && !isBarriers)) {
        change_human(); // unset previous human
        change_human(); // put new one behind the fences
      }
    } else if (strncmp(message, "box", strlen("barriers")) == 0) {
      change_box();
      if (isBarriers && isBox)
        change_barriers();
      if ((isWorker1 && isBox) || (isWorker2 && !isBox)) {
        change_human(); // unset previous human
        change_human(); // put new one behind the box
      }
    }
    message = wb_robot_wwi_receive_text();
  }
}
