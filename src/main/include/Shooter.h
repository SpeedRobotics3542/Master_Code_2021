#ifndef SHOOTER_H
#define SHOOTER_H

#include <rev/CANSparkMax.h>
#include "frc/Servo.h"
#include "frc/PIDController.h"
#include "frc/Encoder.h"
#include "frc/smartdashboard/Smartdashboard.h"

class Shooting
{
    private:

    int ShooterVelocity = 0;

    public:



    //Defining and adressing Motors on shooter
    //Defining Encoders on shooter
    //Creating PID controller for shooter

    // are these addresses correct????
    rev::CANSparkMax Shooter1 {4, rev::CANSparkMax::MotorType::kBrushless};
    rev::CANSparkMax Shooter2 {5, rev::CANSparkMax::MotorType::kBrushless};
    rev::CANSparkMax Shooter3 {6, rev::CANSparkMax::MotorType::kBrushless};
    rev::CANSparkMax MeteringWheel {11, rev::CANSparkMax::MotorType::kBrushless};
    rev::CANEncoder Shooter1Encoder = Shooter1.GetEncoder();
    rev::CANEncoder Shooter2Encoder = Shooter2.GetEncoder();
    rev::CANEncoder Shooter3Encoder = Shooter3.GetEncoder();
    rev::CANEncoder MeteringWheelEncoder = MeteringWheel.GetEncoder();
    rev::CANPIDController ShooterPIDController = Shooter1.GetPIDController();
    rev::CANPIDController ShooterPIDController2 = Shooter2.GetPIDController();
    rev::CANPIDController ShooterPIDController3 = Shooter3.GetPIDController();
    rev::CANPIDController MeteringWheelPIDController = MeteringWheel.GetPIDController();

    // defining servos and the hood PID
    frc::Servo hood1 {2};
    frc::Servo hood2 {3};

    double P = 0.1;
    double I = 0;
    double D = 0;
    double HoodTolerance = 500;

    frc2::PIDController HoodPID{P, I, D};


    // Hood encoder
     frc::Encoder HoodEncoder{0, 1};

    Shooting()
    {

        Shooter1.RestoreFactoryDefaults();
        Shooter2.RestoreFactoryDefaults();
        Shooter3.RestoreFactoryDefaults();
        MeteringWheel.RestoreFactoryDefaults();

        Shooter1.SetInverted(true);
        Shooter2.SetInverted(true);
        Shooter3.SetInverted(true);

        //Setting the Hood Tolerance
        HoodPID.SetTolerance (HoodTolerance, 10);

        //Setting Shooter PID Controller and Output range
        ShooterPIDController.SetP(.005);
        ShooterPIDController.SetI(0);
        ShooterPIDController.SetD(0);
        ShooterPIDController.SetFF(0);

        ShooterPIDController2.SetP(.005);
        ShooterPIDController2.SetI(0);
        ShooterPIDController2.SetD(0);
        ShooterPIDController2.SetFF(0);

        ShooterPIDController3.SetP(.005);
        ShooterPIDController3.SetI(0);
        ShooterPIDController3.SetD(0);
        ShooterPIDController3.SetFF(0);

        MeteringWheelPIDController.SetP(.000025);
        MeteringWheelPIDController.SetI(.000000395);
        MeteringWheelPIDController.SetD(.000001);

        ShooterPIDController.SetOutputRange(-1, 1);
        MeteringWheelPIDController.SetOutputRange(-1, 1);


        //Setting Ramp rate
        Shooter1.SetClosedLoopRampRate(1);
        Shooter2.SetClosedLoopRampRate(1);
        Shooter3.SetClosedLoopRampRate(1);
        MeteringWheel.SetClosedLoopRampRate(.25);

        //Setting motors 2 & 3 to follow motor 1
        // Shooter2.Follow(Shooter1);
        // Shooter3.Follow(Shooter1);

        //Setting Current limits
        Shooter1.SetSmartCurrentLimit(500, 400);
        Shooter2.SetSmartCurrentLimit(500, 400);
        Shooter3.SetSmartCurrentLimit(500, 400);

      

        MeteringWheel.SetSmartCurrentLimit(5, 30);


// //------------------------------------OLIVIA LOOK HERE--------------------------------------
//         Shooter2.Follow(Shooter1);
//         Shooter3.Follow(Shooter1);
//         Shooter1.Set(rev::ControlType::kVelocity);

//         MeteringWheel.Set(rev::ControlType::kVelocity);

// // ---------------------------------------------------------------------------------------

    };

    // function name: SetVelocity
    // inputs: target velocity
    // purpose: set veloity of the shooter motors
    bool SetVelocity(int target)
    {

        ShooterVelocity = target;
        if(target == 0)
        {
            
            Shooter1.Set(0);
            
        } else {
        
        ShooterPIDController.SetReference(target, rev::ControlType::kVelocity);
        frc::SmartDashboard::PutNumber("Shooter Velocity", Shooter1Encoder.GetVelocity());
        return 1;

        }


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
        //if((ShooterVelocity * .95) <= Shooter1Encoder.GetVelocity() and 
          //  (ShooterVelocity * 1.05) >= Shooter1Encoder.GetVelocity())
        //{

            MeteringWheelPIDController.SetReference(MeteringWheelVelocity, rev::ControlType::kVelocity);

            frc::SmartDashboard::PutNumber("set point", MeteringWheelVelocity);
            //MeteringWheel.Set(.5);
            
            //return 1;

        //}

        //Metering wheel turns off if condition is not true
        //else
        //{

            //MeteringWheel.Set(0);

        //}

        //return 0;

    }

    // function that moves the hood based on the PID
    // calculate the PID value
    // pass that value to the servo function (runHood)

    bool HoodMove (int ServoPosition = 0)
    {
        if(!HoodPID.AtSetpoint())
        {
            double HoodPower = HoodPID.Calculate(HoodEncoder.GetDistance(), ServoPosition);
            runHood(HoodPower);
            return 0;

        } else {

            return 1;

        }
    }

    // input a percent value
    // scale to the servo units
    // run one forward and one backward
    // run the servos at that value

    bool runHood(double power)
    {
        
        double servoPower = power / 100;
        servoPower = servoPower + 1.0;
        servoPower = servoPower / 2;

        double servoPower2 = -power / 100;
        servoPower2 = servoPower2 + 1.0;
        servoPower2 = servoPower2 / 2;

        hood1.Set(servoPower);
        hood2.Set(servoPower2);

        return 1;

    }

};




#endif