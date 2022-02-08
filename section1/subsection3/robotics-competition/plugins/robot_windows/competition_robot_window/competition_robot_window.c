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
int count = 0;
bool mavic = false;
bool aibo = false;
bool init = false;

const char *challenge_start_position[] = {"-2.05 8.28 0.334", "-6.1 8.28 0.334",
                                          "-7.78 -0.4 0.334",
                                          "-2.17 0.44 0.334"};
double challenge_target_position[4][2] = {
    {-1.81, 3.98}, {-6, 0.39}, {-7.85, -6.2}, {-1.5, -4.37}};

double viewpoint_orient[4][4] = {{0.191, 0.129, -0.973, 1.98},
                                 {0.441, 0.221, -0.87, 2.32},
                                 {0.187, 0.101, -0.977, 2.17},
                                 {0.173, 0.232, -0.957, 1.32}};
double viewpoint_pos[4][3] = {{0.166, 11.9, 3.14},
                              {-2.89, 9.5, 8.49},
                              {-4.01, 4.15, 4.04},
                              {-4.44, 4.9, 4.56}};

// Window initialization: get some robot devices.
void wb_robot_window_init() {}

// A simulation step occurred.
void wb_robot_window_step(int time_step) {
  // Window initialization: get some robot devices.
  const char *message = wb_robot_wwi_receive_text();
  if (message) {
    if (strncmp(message, "robotName:", 10) == 0) {
      char *data = strchr(message, ':') + 1;
      const char s[2] = "/";
      char *robot_name = strtok(data, s);
      challenge_number = atoi(strtok(NULL, s));

      // remove previous robot
      WbNodeRef old_robot_node = wb_supervisor_node_get_from_def("MY_ROBOT");
      if (old_robot_node) {
        wb_supervisor_node_remove(old_robot_node);
      }

      // load the robot in front of the given challenge number with its
      // controller
      char robot_node_content[0x255];
      char controllerArgs[0x100];
      mavic = strcmp(robot_name, "Mavic2Pro") == 0;
      aibo = strcmp(robot_name, "AiboErs7") == 0;

      if (strcmp(robot_name, "Shrimp") == 0 && challenge_number == 2) {
        sprintf(robot_node_content,
                "DEF MY_ROBOT %s { translation %s rotation 0 0 1 -1.82 "
                "controller \"%s_competition\" }",
                robot_name, challenge_start_position[challenge_number],
                robot_name);
      } else if (mavic) {
        sprintf(controllerArgs,
                " controllerArgs [ \"--patrol_coords\" \"%f %f\" ]",
                challenge_target_position[challenge_number][0],
                challenge_target_position[challenge_number][1]);
        sprintf(robot_node_content,
                "DEF MY_ROBOT %s { translation %s rotation 0 0 1 -1.5708 "
                "controller \"%s_competition\" %s }",
                robot_name, challenge_start_position[challenge_number],
                robot_name, controllerArgs);
      } else
        sprintf(robot_node_content,
                "DEF MY_ROBOT %s { translation %s rotation 0 0 1 -1.5708 "
                "controller \"%s_competition\" }",
                robot_name, challenge_start_position[challenge_number],
                robot_name);

      WbNodeRef root_node = wb_supervisor_node_get_root();
      WbFieldRef children_field =
          wb_supervisor_node_get_field(root_node, "children");
      wb_supervisor_field_import_mf_node_from_string(children_field, -1,
                                                     robot_node_content);

      // move the viewpoint to the challenge
      /*char viewpoint_name[12];
      sprintf(viewpoint_name, "VIEWPOINT_%d", challenge_number);
      WbNodeRef viewpoint_node =
      wb_supervisor_node_get_from_def(viewpoint_name);
      */

      WbNodeRef viewpoint_node = wb_supervisor_node_get_from_def("VIEWPOINT");
      wb_supervisor_node_move_viewpoint(viewpoint_node);

      WbFieldRef viewpoint_orient_field =
          wb_supervisor_node_get_field(viewpoint_node, "orientation");
      WbFieldRef viewpoint_pos_field =
          wb_supervisor_node_get_field(viewpoint_node, "position");
      wb_supervisor_field_set_sf_rotation(viewpoint_orient_field,
                                          viewpoint_orient[challenge_number]);
      wb_supervisor_field_set_sf_vec3f(viewpoint_pos_field,
                                       viewpoint_pos[challenge_number]);

    } else
      fprintf(stderr, "Unkown message: '%s'\n", message);

    play_simulation = true;
    prev_remaining_distance = 0;
    count = 0;
    init = true;
  }

  if (play_simulation) {

    wb_supervisor_set_label(1, "", 0, 0.1, 0.1, 0x00ff00, 0.2, "Impact");
    WbNodeRef robot_node = wb_supervisor_node_get_from_def("MY_ROBOT");
    WbFieldRef custom_data_field =
        wb_supervisor_node_get_field(robot_node, "customData");
    const double *robot_position = wb_supervisor_node_get_position(robot_node);
    char answer[0x100];
    // if the robot reaches the target goal, stop the robot.
    double remaining_distance = fabs(
        robot_position[1] - challenge_target_position[challenge_number][1]);
    if (remaining_distance < 0.2) {
      play_simulation = false;
      wb_supervisor_set_label(1, "Challenge achieved successfully!", 0, 0.1,
                              0.1, 0x00ff00, 0.2, "Impact");
      wb_robot_wwi_send_text("success");

      wb_supervisor_field_set_sf_string(custom_data_field, "stop");
    }
    if (!mavic && !aibo &&
        fabs(prev_remaining_distance - remaining_distance) < 0.00001) {
      count++;
    }
    if (count > 500) { // after 500 robot step we consider that the robot is not
                       // moving anymore.
      play_simulation = false;
      wb_supervisor_set_label(1, "Challenge failed.", 0, 0.1, 0.1, 0xff0000,
                              0.2, "Impact");
      wb_robot_wwi_send_text("failure");
      wb_supervisor_field_set_sf_string(custom_data_field, "stop");
    }

    if (init) {
      sprintf(answer, "init: %f", remaining_distance);
      wb_robot_wwi_send_text(answer);
      init = false;
    }
    // At each step, send the remained distance value to JavaScript.
    else if (remaining_distance > 0 && !isnan(remaining_distance)) {
      sprintf(answer, "distance: %f", remaining_distance);
      wb_robot_wwi_send_text(answer);
    }
    prev_remaining_distance = remaining_distance;
  }
}
