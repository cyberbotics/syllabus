/*
 * File:          supervisor_add_items.c
 * Date:
 * Description:
 * Author:
 * Modifications:
 */

/*
 * You may need to add include files like <webots/distance_sensor.h> or
 * <webots/motor.h>, etc.
 */
#include <webots/supervisor.h>
#include <webots/robot.h>
#include <webots/keyboard.h>

/*
 * You may want to add macros here.
 */
#define TIME_STEP 8

/*
 * This is the main program.
 * The arguments of the main function can be specified by the
 * "controllerArgs" field of the Robot node
 */
int main(int argc, char **argv) {
  /* necessary to initialize webots stuff */
  wb_robot_init();
  wb_keyboard_enable(64);
  WbNodeRef root_node = wb_supervisor_node_get_root();
  WbFieldRef root_children_field = wb_supervisor_node_get_field(root_node, "children");
  int i = 0;
  while (wb_robot_step(TIME_STEP) != -1) {
    int key = wb_keyboard_get_key();
    if (key == WB_KEYBOARD_HOME) {
        if (i == 0)
          wb_supervisor_field_import_mf_node_from_string(root_children_field, -1, "WaterBottle{translation 4.9 -0.83 0.6}");
        i++;
    } else if (key == 'A') {
        if (i == 0) {
          WbNodeRef storageNode = wb_supervisor_node_get_from_def("STORAGE");
          wb_supervisor_node_remove(storageNode);
        }
        i++;
    }
    else if (key == 'B') {
        if (i == 0) 
          wb_supervisor_field_import_mf_node_from_string(root_children_field, -1, "CardboardBox{translation 0.1 0.91 0.77 size 0.4 0.4 1.5 mass 0.4}");
        i++;
    }
    
    if (i != 0) {
      if (i >= 100)
        i = 0;
       else 
        i++;
    }
  };

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}
