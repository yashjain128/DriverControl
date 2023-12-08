/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Yash Jain                                                 */
/*    Created:      12/7/2023, 1:53:38 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "iostream"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
brain Brain;// Robot configuration code.
controller Controller = controller(primary);

motor LeftMotorA = motor(PORT1, ratio18_1, false);
motor LeftMotorB = motor(PORT2, ratio18_1, false);
motor_group LeftDrive = motor_group(LeftMotorA, LeftMotorB);

motor RightMotorA = motor(PORT3, ratio18_1, true);
motor RightMotorB = motor(PORT4, ratio18_1, true);
motor_group RightDrive = motor_group(RightMotorA, RightMotorB);

motor Puncher = motor(PORT5, ratio18_1, false);

// Control constants
int min_joystick = 5;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton() {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*Basic Tank Control*/
void tank_drive()
{
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous() {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void driver_control() {
  // User control code here, inside the loop
  Controller.rumble("--");
  while (true) {
    // Read joystick axes and then set velocity
    double left_axis = Controller.Axis3.position();
    double right_axis = Controller.Axis2.position();

    // Ignore values less minimum
    if (abs(left_axis) > min_joystick){
      left_axis = 0;
    }
    if (abs(right_axis) <= min_joystick){
      right_axis = 0;
    }

    LeftDrive.setVelocity(left_axis, percent);
    RightDrive.setVelocity(right_axis, percent);
    
    LeftDrive.spin(forward);
    RightDrive.spin(forward);

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(driver_control);

  // Run the pre-autonomous function.
  pre_auton();

  std::cout << "Hey\n";
  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
