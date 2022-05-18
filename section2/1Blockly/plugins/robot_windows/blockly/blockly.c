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
#include <webots/receiver.h>
#include <webots/robot.h>
#include <webots/supervisor.h>
#include <webots/utils/motion.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

WbDeviceTag emitter, receiver;
const char *NAO;
WbNodeRef naoRef, root_node;
WbFieldRef root_children_field;
bool hasFinished = false;

// Window initialization: get some robot devices.
void wb_robot_window_init() {
  emitter = wb_robot_get_device("emitter");
  receiver = wb_robot_get_device("receiver");
  wb_receiver_enable(receiver, 10);
  root_node = wb_supervisor_node_get_root();
  root_children_field = wb_supervisor_node_get_field(root_node, "children");
  naoRef = wb_supervisor_node_get_from_def("NAO");
  NAO = wb_supervisor_node_export_string(naoRef);
}

// A simulation step occurred.
void wb_robot_window_step(int time_step) {
  // Window initialization: get some robot devices.
  const char *message = wb_robot_wwi_receive_text();
  if (message) {
    char signal[16];
    if (strncmp(message, "forward", strlen("forward")) == 0) {
      sprintf(signal, "forward");
      wb_emitter_send(emitter, signal, strlen(message));
    } else if (strncmp(message, "backward", strlen("backward")) == 0) {
      sprintf(signal, "backward");
      wb_emitter_send(emitter, signal, strlen(message));
    } else if (strncmp(message, "sideStepLeft", strlen("sideStepLeft")) == 0) {
      sprintf(signal, "sideStepLeft");
      wb_emitter_send(emitter, signal, strlen(message));
    } else if (strncmp(message, "sideStepRight", strlen("sideStepRight")) ==
               0) {
      sprintf(signal, "sideStepRight");
      wb_emitter_send(emitter, signal, strlen(message));
    } else if (strncmp(message, "turnLeft40", strlen("turnLeft40")) == 0) {
      sprintf(signal, "turnLeft40");
      wb_emitter_send(emitter, signal, strlen(message));
    } else if (strncmp(message, "turnLeft60", strlen("turnLeft60")) == 0) {
      sprintf(signal, "turnLeft60");
      wb_emitter_send(emitter, signal, strlen(message));
    } else if (strncmp(message, "turnRight40", strlen("turnRight40")) == 0) {
      sprintf(signal, "turnRight40");
      wb_emitter_send(emitter, signal, strlen(message));
    } else if (strncmp(message, "turnRight60", strlen("turnRight60")) == 0) {
      sprintf(signal, "turnRight60");
      wb_emitter_send(emitter, signal, strlen(message));
    } else if (strncmp(message, "taichi", strlen("taichi")) == 0) {
      sprintf(signal, "taichi");
      wb_emitter_send(emitter, signal, strlen(message));
    } else if (strncmp(message, "wipeForehead", strlen("wipeForehead")) == 0) {
      sprintf(signal, "wipeForehead");
      wb_emitter_send(emitter, signal, strlen(message));
    } else if (strncmp(message, "handWave", strlen("handWave")) == 0) {
      sprintf(signal, "handWave");
      wb_emitter_send(emitter, signal, strlen(message));
    } else if (strncmp(message, "reset", strlen("reset")) == 0) {
      wb_supervisor_field_import_mf_node_from_string(root_children_field, -1,
                                                     NAO);
      wb_supervisor_node_remove(naoRef);
      naoRef = wb_supervisor_node_get_from_def("NAO");
      NAO = wb_supervisor_node_export_string(naoRef);
    } else
      fprintf(stderr, "Unkown message: '%s'\n", message);
  }

  while (wb_receiver_get_queue_length(receiver) > 0) {
    const char *message = wb_receiver_get_data(receiver);
    if (message[0] == 'f') {
      wb_robot_wwi_send_text("next");
    }
    wb_receiver_next_packet(receiver);
  }

  // Check if the NAO reached the end of the track
  const double *position = wb_supervisor_node_get_position(naoRef);
  if (position[0] > 3.7 && !hasFinished) {
    wb_robot_wwi_send_text("success");
    wb_supervisor_set_label(0, "Success!", 0, 0, 0.2, 0xff0000, 0, "Arial");
    hasFinished = true;
  }
}
