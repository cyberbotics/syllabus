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

/*
 * Description:  The controller used to move the Surveyor.
 */

#include "surveyor_protocol.h"
#include <stdio.h>
#include <webots/robot.h>

#define TIME_STEP 16
#define MAX_BUFFER_SIZE 4
#define MAX_RESP_BUFFER_SIZE 90

int main() {
  unsigned char buffer[MAX_BUFFER_SIZE];
  static unsigned char response[MAX_RESP_BUFFER_SIZE];
  buffer[0] = '8';
  wb_robot_init();
  surveyor_init();
  surveyor_send(buffer, response);
  while (wb_robot_step(TIME_STEP) != -1) {
  }

  return 0;
}
