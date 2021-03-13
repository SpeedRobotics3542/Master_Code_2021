// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once 

#include <string>
#include <frc/TimedRobot.h>
#include "DriveTrain.h"
#include "Indexer.h"
#include "Intake.h"
#include "Limelight.h"
#include <frc/XboxController.h>
#include <frc/smartdashboard/SendableChooser.h>
#include "Shooter.h"
#include "ActionHandler.h"

class Robot : public frc::TimedRobot {

 public:
  frc::XboxController Driver = frc::XboxController (0);
  frc::XboxController Manipulator = frc::XboxController (1);


  DriveTrain* Chassis = new DriveTrain();
  Index* Indexer = new Index();
  Intook* Intake = new Intook();
  Shooting* Shooter = new Shooting();
  LimeLight* Limelight = new LimeLight();

//  Handler ActionHandler = Handler( Chassis, Intake, Shooter, Indexer, Limelight);



  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;
  
  Robot(void){}

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;


};
