#ifndef INDEXER_H
#define INDEXER_H

#include <frc/Solenoid.h>
#include <ctre/Phoenix.h>
#include <rev/CANSparkMax.h>

class Index
{

private:

    bool BallStopPosition;
    TalonSRX Hopper {0};
    VictorSPX HoldingSystem {1};
    frc::Solenoid BallStop {0};

public:

    //Sets motor adresses and sets Ball Stopper to Stop the balls from shooting
    Index()
    {

        BallStopPosition = true; //stopping ball
        
    };

    //Hopper control (Forward)
    void HopperRun(double power = 0)
    {

        power = power / 100;

        Hopper.Set(ControlMode::PercentOutput, power);

    }
    
    //Holding System Control (Forward)
    void HoldingSystemRun(double power = 0)
    {

        power = power / 100;

        HoldingSystem.Set(ControlMode::PercentOutput, power);

    } 

    //Running Hopper and Holding System forward (Possibly at different powers)
    void HopperHoldingSystemRun(double PowerHopper = 0, double PowerHoldingSystem = 0)
    {

        HopperRun(PowerHopper);
        HoldingSystemRun(PowerHoldingSystem);

    }

    //GetBallStop returns the position of the ball-stopper
    bool GetBallStop()
    {

        return BallStopPosition;

    }

    //FlipBallStop actuates the solenoid to the other position
    bool FlipBallStop()
    {

        BallStop.Set(!BallStopPosition);
        BallStopPosition = !BallStopPosition;
        return true;

    }

};

#endif