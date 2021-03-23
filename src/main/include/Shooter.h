#ifndef SHOOTER_H
#define SHOOTER_H

#include <rev/CANSparkMax.h>
#include "frc/Servo.h"

class Shooting
{
    private:

    int ShooterVelocity = 0;

    public:



    //Defining and adressing Motors on shooter
    //Defining Encoders on shooter
    //Creating PID controller for shooter
    rev::CANSparkMax Shooter1 = rev::CANSparkMax(0, rev::CANSparkMax::MotorType::kBrushless);
    rev::CANSparkMax Shooter2 = rev::CANSparkMax(1, rev::CANSparkMax::MotorType::kBrushless);
    rev::CANSparkMax Shooter3 = rev::CANSparkMax(2, rev::CANSparkMax::MotorType::kBrushless);
    rev::CANSparkMax MeteringWheel = rev::CANSparkMax(3, rev::CANSparkMax::MotorType::kBrushless);
    rev::CANEncoder Shooter1Encoder = Shooter1.GetEncoder();
    rev::CANEncoder Shooter2Encoder = Shooter2.GetEncoder();
    rev::CANEncoder Shooter3Encoder = Shooter3.GetEncoder();
    rev::CANEncoder MeteringWheelEncoder = MeteringWheel.GetEncoder();
    rev::CANPIDController ShooterPIDController = Shooter1.GetPIDController();
    rev::CANPIDController MeteringWheelPIDController = MeteringWheel.GetPIDController();


    frc::Servo hood1 {1};
    frc::Servo hood2 {2};

    Shooting()
    {

        //Setting Shooter PID Controller and Output range
        ShooterPIDController.SetP(.1);
        ShooterPIDController.SetI(0);
        ShooterPIDController.SetD(0);
        ShooterPIDController.SetOutputRange(-.05, 1);

        //Setting Ramp rate
        Shooter1.SetClosedLoopRampRate(1);
        Shooter2.SetClosedLoopRampRate(1);
        Shooter3.SetClosedLoopRampRate(1);
        MeteringWheel.SetClosedLoopRampRate(.25);

        //Setting motors 2 & 3 to follow motor 1
        Shooter2.Follow(Shooter1);
        Shooter3.Follow(Shooter1);

        //Setting Current limits
        Shooter1.SetSmartCurrentLimit(5, 40);
        Shooter2.SetSmartCurrentLimit(5, 40);
        Shooter3.SetSmartCurrentLimit(5, 40);

    };

    // function name: SetVelocity
    // inputs: target velocity
    // purpose: set veloity of the shooter motors
    bool SetVelocity(int target)
    {

        ShooterVelocity = target;
        ShooterPIDController.SetReference(target, rev::ControlType::kVelocity);
        return 1;

    }

    //returns shooter velocity
    int GetVelocity()
    {

        return ShooterVelocity;

    }

    //metering wheel speed/direction 
    //input: RPM
    bool MeteringWheelRun(double MeteringWheelVelocity = 0)
    {

        //Velocity range for shooter to turn on Metering Wheel      
        if((ShooterVelocity * .95) <= Shooter1Encoder.GetVelocity() and 
            (ShooterVelocity * 1.05) >= Shooter1Encoder.GetVelocity())
        {

            MeteringWheelPIDController.SetReference(MeteringWheelVelocity, rev::ControlType::kVelocity);
            return 1;

        }

        //Metering wheel turns off if condition is not true
        else
        {

            MeteringWheel.Set(0);

        }

        return 0;

    }

    // input a percent value
    // scale to the servo units
    // run one forward and one backward
    // run the servos at that value

    bool runHood(double power)
    {
        
        double servoPower = power / 100;

        hood1.Set(servoPower);
        hood2.Set(-servoPower);

        return 1;

    }

};




#endif