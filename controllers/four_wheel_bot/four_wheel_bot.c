/*
 * File:          four_wheel_bot.c
 * Date:          11/09/2024
 * Description:
 * Author:        ZAHID
 * Modifications:
 */

#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/distance_sensor.h>

#define TIME_STEP 64

int main(int argc, char **argv) {
  wb_robot_init();
  int i;
  bool obstacle_counter = 0;
  
  WbDeviceTag wheels[4];
  char wheel_names[4][8] = {"wheel0", "wheel1", "wheel2", "wheel3"};  
  for (i = 0; i < 4; i++){
    wheels[i] = wb_robot_get_device(wheel_names[i]);
    wb_motor_set_position(wheels[i], INFINITY);
  }

  WbDeviceTag ds[2];
  char ds_names[2][10] = {"ds_left", "ds_right"};
  for (i = 0; i < 2; i++){
    ds[i] = wb_robot_get_device(ds_names[i]);
    wb_distance_sensor_enable(ds[i], TIME_STEP);
  }


  while (wb_robot_step(TIME_STEP) != -1) {
    
    double left_speed = -1.0;
    double right_speed = -1.0;

    if (obstacle_counter > 0){
      obstacle_counter--;
      left_speed = 1.0;
      right_speed = -1.0;
    } 
    else {
      double ds_values[2];
      for (i = 0; i < 2; i++){
        ds_values[i] = wb_distance_sensor_get_value(ds[i]);
      }
      if (ds_values[0] < 950.0 || ds_values[1] < 950.0){
        obstacle_counter = 100;
      }

      wb_motor_set_velocity(wheels[0], left_speed);
      wb_motor_set_velocity(wheels[1], left_speed);
      wb_motor_set_velocity(wheels[2], right_speed);
      wb_motor_set_velocity(wheels[3], right_speed);
    }

  };

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}
