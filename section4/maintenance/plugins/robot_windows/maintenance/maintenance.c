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

#include <webots/emitter.h>
#include <webots/plugins/robot_window/robot_wwi.h>
#include <webots/robot.h>
#include <webots/supervisor.h>

#include <stdio.h>

WbNodeRef finger;
WbFieldRef fingerRotation;
WbDeviceTag emitter;
WbNodeRef cans[10];
WbFieldRef cansTranslation[10];
WbFieldRef cansRotation[10];
int lastCanID = 9;
// Window initialization: get some robot devices.
void wb_robot_window_init() {
  emitter = wb_robot_get_device("emitter");

  // Get NodeRefs
  finger = wb_supervisor_node_get_from_def("FINGER");
  // Get FieldRefs
  fingerRotation = wb_supervisor_node_get_field(finger, "rotation");
  char name [5] = "CAN";
  char number [2];
  for (int i = 0; i < 10; i++) {
    sprintf(number, "%d", i);
    name[3] = number[0];
    name[4] = number[1];
    cans[i] = wb_supervisor_node_get_from_def(name);
    cansTranslation[i] = wb_supervisor_node_get_field(cans[i], "translation");
    cansRotation [i] = wb_supervisor_node_get_field(cans[i], "rotation");
  }
}

void change_finger() {
  double rotation[4] = {0, 0, 1, 0};
  wb_supervisor_field_set_sf_rotation(fingerRotation, rotation);
  wb_supervisor_node_reset_physics(finger);
}


// A simulation step occurred.
void wb_robot_window_step(int time_step) {
  const char *message = wb_robot_wwi_receive_text();
  while (message) {
    printf("message %s\n", message);
    if (strncmp(message, "finger", strlen("finger")) == 0)
      change_finger();
    else
      wb_emitter_send(emitter, message, strlen(message));


    message = wb_robot_wwi_receive_text();
  }
  
  const double* translation = wb_supervisor_field_get_sf_vec3f(cansTranslation[lastCanID]);
  if (translation[0] <= 6.07) {
    lastCanID = lastCanID == 9 ? 0 : lastCanID + 1;
    double newTranslation[3] = {7.7, -0.82, 0.66};
    wb_supervisor_field_set_sf_vec3f(cansTranslation[lastCanID], newTranslation);
    double newRotation[4] = {0, 0, 1, 0};
    wb_supervisor_field_set_sf_rotation(cansRotation[lastCanID], newRotation);
    wb_supervisor_node_reset_physics(cans[lastCanID]);
  } 
}
