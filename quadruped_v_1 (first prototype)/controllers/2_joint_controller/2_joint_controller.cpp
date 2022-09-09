// File:          Quadruped_2Joint_V1.cpp
// Date:
// Description:
// Author:
// Modifications:

// You may need to add webots include files such as
// <webots/DistanceSensor.hpp>, <webots/Motor.hpp>, etc.
// and/or to add some other includes
#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <iostream>
#include <string>
#define TIME_STEP 16

// All the webots classes are defined in the "webots" namespace
using namespace webots;
using namespace std;

// This is the main program of your controller.
// It creates an instance of your Robot instance, launches its
// function(s) and destroys it at the end of the execution.
// Note that only one instance of Robot should be created in
// a controller program.
// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node


double FORWARDS_S = -0.9;
double FORWARDS_E = 0.8;
double MIDDLE_S = -0.7;
double MIDDLE_E = 1.1;
double BACK_S = -0.27;
double BACK_E = 0.9;
double TUCK_S = -1.6;
double TUCK_E = 1.8;


int step = 1;
double resumeTime = 0;


Robot *robot;

//Returns actual time delayed
void sleep(double seconds){
  double startTime = robot->getTime();
  double sleepUntilTime = startTime + seconds;
  while (robot->step(TIME_STEP) != -1 && robot->getTime() < sleepUntilTime);
}


int main(int argc, char **argv) {
  // create the Robot instance.
  robot = new Robot();

  // get the time step of the current world.
  //int timeStep = (int)robot->getBasicTimeStep();

  // You should insert a getDevice-like function in order to get the
  // instance of a device of the robot. Something like:
  //  Motor *motor = robot->getMotor("motorname");
  //  DistanceSensor *ds = robot->getDistanceSensor("dsname");
  //  ds->enable(timeStep);
  
  Motor *FL_shoulder = robot->getMotor("FrontLeft_Shoulder");
  Motor *FL_elbow = robot->getMotor("FrontLeft_Elbow");
  Motor *FR_shoulder = robot->getMotor("FrontRight_Shoulder");
  Motor *FR_elbow = robot->getMotor("FrontRight_Elbow");
  Motor *BL_shoulder = robot->getMotor("BackLeft_Shoulder");
  Motor *BL_elbow = robot->getMotor("BackLeft_Elbow");
  Motor *BR_shoulder = robot->getMotor("BackRight_Shoulder");
  Motor *BR_elbow = robot->getMotor("BackRight_Elbow");
  
  
  
  
  //Starting positions
  FL_shoulder->setPosition(MIDDLE_S);
  FL_elbow->setPosition(MIDDLE_E);
  FR_shoulder->setPosition(FORWARDS_S);
  FR_elbow->setPosition(FORWARDS_E);
  BL_shoulder->setPosition(BACK_S);
  BL_elbow->setPosition(BACK_E);
  BR_shoulder->setPosition(MIDDLE_S);
  BR_elbow->setPosition(MIDDLE_E);
  
  
  
  FL_shoulder->setVelocity(1);
  FL_elbow->setVelocity(1);
  FR_shoulder->setVelocity(1);
  FR_elbow->setVelocity(1);
  BL_shoulder->setVelocity(1);
  BL_elbow->setVelocity(1);
  BR_shoulder->setVelocity(1);
  BR_elbow->setVelocity(1);
  

  // Main loop:
  // - perform simulation steps until Webots is stopping the controller
  //Note: I have set the loop to stop after 1 walk cycle.
  //Change the loop condition to make it run longer/indefinitely.
  int cycles = 0;
  while (robot->step(TIME_STEP) != -1 && cycles < 5) {
    /*
    Note: when moving the back leg forward, it may be necessary to tuck the leg in
    before rotating it in front to prevent the leg from scraping the ground.
    Add a delay to let the leg move, then set the required motor position:
      probably shoulder->setPosition(FORWARDS_S), elbow->setPosition(FORWARDS_E)
    
    To create a delay, set the variable "delay" to the number of seconds 
    (up to 3 decimals) to let the robot wait for that amount of time. 
    Servos will still move to and hold their position.
    
    Note: when moving back legs forwards, it may be necessary to move it
    to middle, not forwards position
    
    */
    if (robot->getTime() < resumeTime) continue;
    //Step 1: tuck and move BL forwards and rotate everything else back 1
    //Step 1.5: untuck BL and set it on the ground
    if (step == 1){
      //BL angles should be set to intermediate positions to tuck the leg in
      BL_elbow->setPosition(TUCK_E);
      BL_shoulder->setPosition(TUCK_S);
      
      FL_shoulder->setPosition(BACK_S);
      FL_elbow->setPosition(BACK_E);
      FR_shoulder->setPosition(MIDDLE_S);
      FR_elbow->setPosition(MIDDLE_E);
      BR_shoulder->setPosition(BACK_S);
      BR_elbow->setPosition(BACK_E);
      
      sleep (2);
      
      BL_elbow->setPosition(FORWARDS_E);
      sleep (1);
      BL_shoulder->setPosition(FORWARDS_S);
      sleep(2);
    }
    //Step 2: move FL forwards
    //Step 2.5: untuck FL and set it on the ground
    else if (step == 2){
      FL_elbow->setPosition(TUCK_E);
      FL_shoulder->setPosition(TUCK_S);
      sleep(2);
      FL_elbow->setPosition(FORWARDS_E);
      sleep(1);
      FL_shoulder->setPosition(FORWARDS_S);
      sleep(2);
    }
    //Step 3: tuck and move BR forwards and rotate everything else back 1
    //Step 3.5: untuck BR and set it on the ground
    else if (step == 3){
      BR_elbow->setPosition(TUCK_E);
      BR_shoulder->setPosition(TUCK_S);
      
      FR_shoulder->setPosition(BACK_S);
      FR_elbow->setPosition(BACK_E);
      FL_shoulder->setPosition(MIDDLE_S);
      FL_elbow->setPosition(MIDDLE_E);
      BL_shoulder->setPosition(BACK_S);
      BL_elbow->setPosition(BACK_E);
      
      sleep (2);
      
      BR_elbow->setPosition(FORWARDS_E);
      sleep(1);
      BR_shoulder->setPosition(FORWARDS_S);
      sleep(2);
    }
    //Step 4: move FR forwards
    //Step 4.5: untuck FR and set it on the ground
    else if (step == 4){
      FR_elbow->setPosition(TUCK_E);
      FR_shoulder->setPosition(TUCK_S);
      sleep(2);
      FR_elbow->setPosition(FORWARDS_E);
      sleep(1);
      FR_shoulder->setPosition(FORWARDS_S);
      sleep(2);
    }
    
    step++;
    if (step > 4){
      step = 1;
      cycles++;
    }
  };

  // Enter here exit cleanup code.

  delete robot;
  return 0;
}
