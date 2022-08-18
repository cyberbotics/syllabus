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

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static bool play_simulation = false;
int challenge_number = 0;
double prev_remaining_distance = 0;
bool newStart = false;
int count = 0;
int max_count = 0;
bool init = false;
bool send_init = false;
bool restart_controller = false;
int current_robot = -1;
WbNodeRef current_robot_node;
WbNodeRef previous_robot_node;
char *robot_node_def;
char *old_robot_node_def;
char *robot_controller;
char *none_controller;
double challenge_target_position[4][2] = {
    {-1.81, 3.98}, {-6, 0.39}, {-7.85, -6.2}, {-1.5, -4.37}};

// Window initialization: get some robot devices.
void wb_robot_window_init() {}

// A simulation step occurred.
void wb_robot_window_step(int time_step) {
  if (restart_controller) {
    wb_supervisor_node_restart_controller(current_robot_node);
    restart_controller = false;
    if(previous_robot_node) {
      wb_supervisor_node_restart_controller(previous_robot_node);
      wb_supervisor_node_reset_physics(previous_robot_node);
    }
  }
  const char *message = wb_robot_wwi_receive_text();
  if (message) {
    if (strncmp(message, "robotName:", 10) == 0) {
      char *data = strchr(message, ':') + 1;
      const char s[2] = "/";
      char *robot_name = strtok(data, s);
      challenge_number = atoi(strtok(NULL, s));

      char controllerArgs[0x100];

      double newTranslation[3] = {-1000, -1000, -10};
      double newRotation[4] = {0, 0, 1, 0};
      old_robot_node_def = robot_node_def;
      if (strcmp(robot_name, "AiboErs7") == 0) {
        robot_node_def = "R0";
        newTranslation[2] = 0.153;
        robot_controller = "AiboErs7_competition";
      } else if (strcmp(robot_name, "Mavic2Pro") == 0) {
        robot_node_def = "R1";
        sprintf(controllerArgs, "--patrol_coords=%f %f",
                challenge_target_position[challenge_number][0],
                challenge_target_position[challenge_number][1]);
        newTranslation[2] = 0.15;
        robot_controller = "Mavic2Pro_competition";
      } else if (strcmp(robot_name, "Nao") == 0) {
        robot_node_def = "R2";
        newTranslation[2] = 0.334;
        robot_controller = "Nao_competition";
      } else if (strcmp(robot_name, "Pioneer3at") == 0) {
        robot_node_def = "R3";
        newTranslation[2] = 0.05;
        robot_controller = "Pioneer3at_competition";
      } else if (strcmp(robot_name, "Shrimp") == 0) {
        robot_node_def = "R4";
        newTranslation[2] = 0.1;
        robot_controller = "Shrimp_competition";
      } else if (strcmp(robot_name, "SummitXlSteel") == 0) {
        robot_node_def = "R5";
        newTranslation[2] = 0.118;
        robot_controller = "SummitXlSteel_competition";
      } else if (strcmp(robot_name, "trackedRobot") == 0) {
        robot_node_def = "R6";
        newTranslation[2] = 0.334;
        robot_controller = "trackedRobot_competition";
      }

      if (current_robot_node) {
        newTranslation[0] = -10.1;
        if (strcmp(old_robot_node_def, "R0") == 0) {
          newTranslation[1] = -4.6;
          none_controller = "<none>";
        } else if (strcmp(old_robot_node_def, "R1") == 0) {
          newTranslation[1] = -3.7;
          none_controller = "Mavic2Pro_stop";
        } else if (strcmp(old_robot_node_def, "R2") == 0) {
          newTranslation[1] = -5.3;
          none_controller = "Nao_stop";
        } else if (strcmp(old_robot_node_def, "R3") == 0) {
          newTranslation[1] = -7;
          none_controller  = "Pioneer3at_stop";
        } else if (strcmp(old_robot_node_def, "R4") == 0) {
          newTranslation[1] = -6.1;
          none_controller = "Shrimp_stop";
        } else if (strcmp(old_robot_node_def, "R5") == 0) {
          newTranslation[1] = -8;
          none_controller = "SummitXlSteel_stop";
        } else if (strcmp(old_robot_node_def, "R6") == 0) {
          newTranslation[1] = -9.2;
          none_controller = "trackedRobot_stop";
        }

        WbFieldRef translation =
            wb_supervisor_node_get_field(current_robot_node, "translation");
        wb_supervisor_field_set_sf_vec3f(translation, newTranslation);
        WbFieldRef rotation =
            wb_supervisor_node_get_field(current_robot_node, "rotation");
        wb_supervisor_field_set_sf_rotation(rotation, newRotation);

        WbFieldRef controller = wb_supervisor_node_get_field(current_robot_node, "controller");
        wb_supervisor_field_set_sf_string(controller, none_controller);

        if (strcmp(old_robot_node_def, "R1") == 0) {
          WbFieldRef controller_args = wb_supervisor_node_get_field(
              current_robot_node, "controllerArgs");
          wb_supervisor_field_set_mf_string(controller_args, -1, "");
        }
      }
      newRotation[3] = -1.5708;

      if (challenge_number == 0) {
        newTranslation[0] = -2.05;
        newTranslation[1] = 8.28;
      } else if (challenge_number == 1) {
        newTranslation[0] = -6.1;
        newTranslation[1] = 8.28;
      } else if (challenge_number == 2) {
        newTranslation[0] = -7.24;
        newTranslation[1] = -0.4;

        if (strcmp(robot_name, "Shrimp") == 0) {
          newRotation[0] = 0;
          newRotation[1] = 0;
          newRotation[2] = 1;
          newRotation[3] = -1.82;
        }
      } else if (challenge_number == 3) {
        newTranslation[0] = -2.17;
        newTranslation[1] = 0.44;
      }

      previous_robot_node = current_robot_node;
      current_robot_node = wb_supervisor_node_get_from_def(robot_node_def);
      WbFieldRef controller = wb_supervisor_node_get_field(current_robot_node, "controller");
      wb_supervisor_field_set_sf_string(controller, robot_controller);
      restart_controller = true;
      if (strcmp(robot_name, "Mavic2Pro") == 0) {
        WbFieldRef controller_args =
            wb_supervisor_node_get_field(current_robot_node, "controllerArgs");
        wb_supervisor_field_set_mf_string(controller_args, -1, controllerArgs);
      }

      WbFieldRef custom_data_field =
          wb_supervisor_node_get_field(current_robot_node, "customData");
      wb_supervisor_field_set_sf_string(custom_data_field, "start");
      WbFieldRef rotation =
          wb_supervisor_node_get_field(current_robot_node, "rotation");
      wb_supervisor_field_set_sf_rotation(rotation, newRotation);
      WbFieldRef translation =
          wb_supervisor_node_get_field(current_robot_node, "translation");
      wb_supervisor_field_set_sf_vec3f(translation, newTranslation);
      wb_supervisor_node_reset_physics(current_robot_node);

      newStart = true;

      if (strcmp(robot_name, "AiboErs7") == 0 && challenge_number == 2)
        max_count = 60;
      else if (strcmp(robot_name, "Nao") == 0 && challenge_number > 0)
        max_count = 20;
      else
        max_count = 500;
    } else
      fprintf(stderr, "Unkown message: '%s'\n", message);

    play_simulation = true;
    prev_remaining_distance = 0;
    count = 0;
    init = true;
  }

  if (play_simulation) {
    wb_supervisor_set_label(1, "", 0, 0.1, 0.1, 0x00ff00, 0.2, "Impact");
    WbNodeRef robot_node = wb_supervisor_node_get_from_def(robot_node_def);
    WbFieldRef custom_data_field =
        wb_supervisor_node_get_field(robot_node, "customData");
    const double *robot_position = wb_supervisor_node_get_position(robot_node);
    char answer[0x100];
    // if the robot reaches the target goal, stop the robot.
    double remaining_distance = fabs(
        robot_position[1] - challenge_target_position[challenge_number][1]);

    if (remaining_distance < 0.2) {
      if (newStart)
        newStart = false;
      else {
        play_simulation = false;
        wb_supervisor_set_label(1, "Challenge achieved successfully!", 0, 0.1,
                                0.1, 0x00ff00, 0.2, "Impact");
        wb_robot_wwi_send_text("success");
        wb_supervisor_field_set_sf_string(custom_data_field, "stop");
      }
    }
    if (fabs(prev_remaining_distance - remaining_distance) < 0.00001) {
      count++;
    }
    if (count > max_count) { // after 500 robot step we consider that the
                             // robot is not moving anymore.
      play_simulation = false;
      wb_supervisor_set_label(1, "Challenge failed.", 0, 0.1, 0.1, 0xff0000,
                              0.2, "Impact");
      wb_robot_wwi_send_text("failure");
      wb_supervisor_field_set_sf_string(custom_data_field, "stop");
    }

    if (init) {
      send_init = true;
      init = false;
    } else if (send_init) {
      send_init = false;
      sprintf(answer, "init: %f", remaining_distance);
      wb_robot_wwi_send_text(answer);
    }
    // At each step, send the remained distance value to JavaScript.
    else if (remaining_distance > 0 && !isnan(remaining_distance)) {
      sprintf(answer, "distance: %f", remaining_distance);
      wb_robot_wwi_send_text(answer);
    }
    prev_remaining_distance = remaining_distance;
  }
}
