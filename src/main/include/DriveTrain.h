#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include <ctre/Phoenix.h>

class DriveTrain
{
private:

    /* data */
public:
    TalonFX RightDrive {2};
    TalonFX RightDrive2 {3};
    TalonFX LeftDrive {0};
    TalonFX LeftDrive2 {1};


 DriveTrain()

 {
    
    //Follower code
    RightDrive2.Follow(RightDrive);
    LeftDrive2.Follow(LeftDrive);

    //Declares the sensor
    RightDrive.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor,0,10);
    LeftDrive.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor,0,10);

    //Inverts Drive
    RightDrive.SetInverted(false);
    RightDrive2.SetInverted(RightDrive.GetInverted());
    LeftDrive.SetInverted(false);
    LeftDrive2.SetInverted(LeftDrive.GetInverted());
};


 void Drive(double LeftJoystick, double RightJoystick, double Power = 1){

     //Driving on Joysticks
     RightDrive.Set(ControlMode::PercentOutput, RightJoystick * Power);
     LeftDrive.Set(ControlMode::PercentOutput, LeftJoystick * Power);

 };

// Function name: aim
// inputs: power (PID) turning right is positive!
// Function actions: turns robot by giving opposite power to each side of the robot.
// return values: boolean for completion

bool Aim(double Power = 0)
{

    //Set motor power to turn
    RightDrive.Set(ControlMode::PercentOutput, -Power);
    LeftDrive.Set(ControlMode::PercentOutput, Power);
    
    return 1;

}


};



#endif