/*
 * File:          epuck_avoid_collision.c
 * Date:          11/09/2024
 * Description:
 * Author:        ZAHID
 * Modifications:
 */

/*
 * You may need to add include files like <webots/distance_sensor.h> or
 * <webots/motor.h>, etc.
 */
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/distance_sensor.h>

#define TIME_STEP 64
#define MAX_SPEED 6.28

int main(int argc, char **argv) {
  /* necessary to initialize webots stuff */
  //initializing webots API
  wb_robot_init(); 

  int i;
  
  WbDeviceTag ps[8];

  char ps_names[8][4] = {
    "ps0", "ps1", "ps2", "ps3", 
    "ps4", "ps5", "ps6", "ps7"
  };

  for (i = 0; i < 8; i++){
    ps[i] = wb_robot_get_device(ps_names[i]);
    wb_distance_sensor_enable(ps[i], TIME_STEP);
  }

  WbDeviceTag left_motor = wb_robot_get_device("left wheel motor");
  WbDeviceTag right_motor = wb_robot_get_device("right wheel motor");
  wb_motor_set_position(left_motor, INFINITY);
  wb_motor_set_position(right_motor, INFINITY);
  wb_motor_set_velocity(left_motor, 0.0);
  wb_motor_set_velocity(right_motor, 0.0);

  while (wb_robot_step(TIME_STEP) != -1) {
    // reading sensor outputs
    double ps_values[8];
    for (i = 0; i < 8; i++){
      ps_values[i] = wb_distance_sensor_get_value(ps[i]);
      }

  // detect obstacles
  bool right_obstacle = ps_values[0] > 80.0 || ps_values[1] > 80.0 || ps_values[2] > 80.0;
  bool left_obstacle = ps_values[5] > 80.0 || ps_values[6] > 80.0 || ps_values[7] > 80.0;

  // initializing motor speeds
  double left_speed = 0.5 * MAX_SPEED;
  double right_speed = 0.5 * MAX_SPEED;

  if (left_obstacle){
    // turning right
    left_speed = 0.5 * MAX_SPEED;
    right_speed = -0.5 * MAX_SPEED;
  }
  else if (right_obstacle){
    // turning left
    left_speed = -0.5 * MAX_SPEED;
    right_speed = 0.5 * MAX_SPEED;
  }

  // writing updated wheel values in case of obstacles
  wb_motor_set_velocity(left_motor, left_speed);
  wb_motor_set_velocity(right_motor, right_speed);

  };

  // cleanup webots API
  wb_robot_cleanup();
  return 0;
}
