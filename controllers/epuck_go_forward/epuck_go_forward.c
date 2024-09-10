/*
 * File:          epuck_go_forward.c
 * Date:
 * Description:
 * Author:
 * Modifications:
 */

/*
 * You may need to add include files like <webots/distance_sensor.h> or
 * <webots/motor.h>, etc.
 */
#include <webots/robot.h>
#include <webots/motor.h>

/*
 * You may want to add macros here.
 */
#define TIME_STEP 64
#define MAX_SPEED 6.28

/*
 * This is the main program.
 * The arguments of the main function can be specified by the
 * "controllerArgs" field of the Robot node
 */
int main(int argc, char **argv) {
  
  /* necessary to initialize webots stuff */
  wb_robot_init();
  
  //getting motor wheel devices
  WbDeviceTag left_motor = wb_robot_get_device("left wheel motor");
  WbDeviceTag right_motor = wb_robot_get_device("right wheel motor");

  wb_motor_set_velocity(left_motor, 0.1 * MAX_SPEED);  
  wb_motor_set_velocity(right_motor, 0.1 * MAX_SPEED);

  
  //setting the target position of the motors
  wb_motor_set_position(left_motor, 10.0);
  wb_motor_set_position(right_motor, 10.0);
  
 
  while (wb_robot_step(TIME_STEP) != -1) {
    
  };

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}
