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

//
// Description: A controller for the Aibo ERS-7 robot which will go straight.
//

#include "../../libraries/mtn/mtn.h"
#include <stdio.h>
#include <string.h>
#include <webots/motor.h>
#include <webots/robot.h>

#define TIME_STEP 64

int main() {
  wb_robot_init();

  // read MTN motion sequence
  MTN *mtn = mtn_new("../../data/mtn/WWFWD.MTN");
  if (!mtn)
    fprintf(stderr, "MTN Error: %s\n", mtn_get_error());

  while (wb_robot_step(TIME_STEP) != -1) {
    // actuate MTN Motor motors
    mtn_step(TIME_STEP);

    const char *custom_data = wb_robot_get_custom_data();
    if (strcmp(custom_data, "stop") < 0) {
      // play mtn until stop
      if (mtn_is_over(mtn))
        mtn_play(mtn);
    }
  }

  wb_robot_cleanup();
  mtn_delete(mtn);

  return 0;
}
