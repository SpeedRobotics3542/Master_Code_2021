#ifndef SHOOTER_H
#define SHOOTER_H

#include <rev/CANSparkMax.h>

class Shooting
{
    private:

    int ShooterVelocity = 0;

    public:



    //Defining and adressing Motors on shooter
    //Defining Encoders on shooter
    //Creating PID controller for shooter
    rev::CANSparkMax Shooter1 = rev::CANSparkMax(4, rev::CANSparkMax::MotorType::kBrushless);
    rev::CANSparkMax Shooter2 = rev::CANSparkMax(5, rev::CANSparkMax::MotorType::kBrushless);
    rev::CANSparkMax Shooter3 = rev::CANSparkMax(6, rev::CANSparkMax::MotorType::kBrushless);
    rev::CANSparkMax MeteringWheel = rev::CANSparkMax(11, rev::CANSparkMax::MotorType::kBrushless);
    rev::CANEncoder Shooter1Encoder = Shooter1.GetEncoder();
    rev::CANEncoder Shooter2Encoder = Shooter2.GetEncoder();
    rev::CANEncoder Shooter3Encoder = Shooter3.GetEncoder();
    rev::CANEncoder MeteringWheelEncoder = MeteringWheel.GetEncoder();
    rev::CANPIDController ShooterPIDController = Shooter1.GetPIDController();
    rev::CANPIDController MeteringWheelPIDController = MeteringWheel.GetPIDController();


    // frc::Servo test {1};

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
        
        //ShooterVelocity = target;

        Shooter1.Set(rev::ControlType::kVelocity);
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

        MeteringWheel.Set(rev::ControlType::kVelocity);
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

};


#endif