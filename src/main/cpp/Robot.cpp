// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include "DriveTrain.h"

#include <iostream>

#include "Indexer.h"

#include "Intake.h"

#include "Shooter.h"



#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit()
{

  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() 
{

   Limelight->LimelightValues();

   //smarts dashboard shooter speed, hood encoder, 
   //shooter hood with servos (plugged into rio)
   //unplug before running shooter
   //use srs/srx programer thing for servos
    //user manual in discord (put in continous mode)
  //before plugging servos back in deploy with smart dashbord values for hood
  //explore the range of encoder (plug in first)
    //2 sets of wires(6 pin-6 pins) looks like motor controller plug in DONT USE
    //pwm wire (3 pin plug into rio)
      //4 sets of wire all have black and red (blue goes into 0, yellow goes into 1) DIO ports
      // black goes to ground (point away from the center of the rio)   
  // write down the range of values for the shooter hood (0-#)
  // if the individual components work, finalise buttons
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {

  Chassis->Drive(Driver.GetY(frc::XboxController::kLeftHand), Driver.GetY(frc::XboxController::kRightHand), .65);
  
  //Intake run on right bumper on manipulator 
  if (Manipulator.GetBumper(frc::XboxController::kRightHand)==1)
  {

    Intake->IntakeRun(25);

  } else {

    Intake->IntakeRun(0, false);

  }

//Holding System run on B Button on Manipulator
if (Manipulator.GetBButton()==1)
{

  Indexer->HoldingSystemRun(40);

} else {

  Indexer->HoldingSystemRun(0);

}

//Hopper and Holding system run 
if (Manipulator.GetAButton()==1)
{

    Indexer->HopperHoldingSystemRun(100, 40);

} else {

    Indexer->HopperHoldingSystemRun(0, 0);

}

//Shooter run on Left bumper on Manipulator
if (Manipulator.GetBumper(frc::XboxController::kLeftHand)==1)
{

  Shooter->SetVelocity(300);

} else {

  Shooter->SetVelocity(0);

}

//Metering Wheel run on X button on Manipulator
if(Manipulator.GetXButton()==1)
{

  //Shooter->SetVelocity(0);
  Shooter->MeteringWheelRun(500);

} else {

  //Shooter->SetVelocity(0);
  Shooter->MeteringWheelRun(0);
  
}

  
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif

