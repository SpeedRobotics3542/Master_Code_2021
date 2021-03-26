#ifndef ACTIONHANDLER_H
#define ACTIONHANDLER_H

#include "Shooter.h"
#include "DriveTrain.h"
#include "Indexer.h"
#include "Intake.h"
#include "Limelight.h"
#include "frc/controller/PIDController.h"


class Handler
{
    private:

        DriveTrain *Chassis;
        Intook *Intake;
        Shooting *Shooter;
        Index *Indexer;
        LimeLight *Limelight;

        //PID controller and variables for PID
        double P = .01;
        double I = 0;
        double D = 0;
        double PIDTolerance = 2.5;
        
        frc2::PIDController AimingPID{P, I, D};

        PigeonIMU *Pigeon = new PigeonIMU (1);

        // toggle for shooter Error calculated
        

    public:
    int ShooterCase = 0;

Handler(DriveTrain* D, Intook* inny, Shooting* Shoot, Index* In, LimeLight* GreenLight)
{ 

    Chassis = D;
    Intake = inny;
    Shooter = Shoot;
    Indexer = In;
    Limelight = GreenLight;

    //Setting Tolerance for Aiming
    AimingPID.SetTolerance(PIDTolerance, 10);

}

//function returns the angle from Pigeon
double GetPigeonAngle()
{

    PigeonIMU::FusionStatus *stat = new PigeonIMU::FusionStatus();
    Pigeon->GetFusedHeading(*stat);
    return stat->heading;

}

//runs intake and indexer together
void IntakeIndexer(bool activated)
{
    if(activated == 1)
    {

        Indexer->HopperHoldingSystemRun(50,50);
        Intake->IntakeRun(50);

    } else {

        Indexer->HopperHoldingSystemRun(0,0);
        Intake->IntakeRun(0, false);

    }
}

// checks to see if the Limelight sees a target and sets the error on the pigeon.
// if 1: set pigeon to error angle
// if 0: no Target!
bool LimelightError()
{

    if (Limelight->targetValid)
    {

        //Limelight angle of error = Pigeon 
        Pigeon->SetFusedHeading(Limelight->targetOffsetAngle_Horizontal);

        return 1;

    }

        return 0;

}

//Connects Limelight, Drivetrain, and Pigeon to aim
bool MasterAiming()
{
           
        //Aiming PID is not where you want  
        //Check setpoint and move robot    
        if (!AimingPID.AtSetpoint())
        {

            //calculate PID output
            double power = AimingPID.Calculate(GetPigeonAngle(), 0);

            //Move toward target
            Chassis->Aim(power);

            return 0;

        } else {

        return 1;

    }

}


int CalcHoodPos()
{

// SOMETHING using limelight distance

}

// purpose: synchronize shooting sequence
//          - move robot and set shooter speed
//          - fire balls When step 1 is complete
// inputs: N/A
// outputs: N/A

void ShootingSequence ()
{

   switch (ShooterCase)
   {
    case 0:

        //Sets angle of error from limelight to the pigeon
        //Allows the shooter to turn on and start the aiming process
        if(LimelightError() == 1)

        {

            Shooter->SetVelocity(2000);
            MasterAiming();
            ShooterCase = 10;

        }

    break;
    
    case 10:

    //Makes sure that the robot is lined up
    if(MasterAiming() == 1)
    {

        ShooterCase = 20;

    }

    break;

    case 20:

        //Moves the Hood on the shooter according to position on the field
        if(Shooter->HoodMove(CalcHoodPos()) == 1)
        {

            ShooterCase = 30;

        }

    break;

    case 30:

        //Double checks that previous conditions are still true
        if(LimelightError() == 1 and MasterAiming() ==1 and Shooter->HoodMove(CalcHoodPos()) == 1)
        {

            //Shooter in range
            //Holding system is on and ball stop allows balls to escape
            if(Shooter->MeteringWheelRun(85) == 1)
            {

                Indexer->HoldingSystemRun(85);
                
                if(Indexer->GetBallStop() == 1)
                {

                    Indexer->FlipBallStop();

                }  

            } else {

                //If not true then Holding system is off
                //Ball stop is closed
                Indexer->HoldingSystemRun(0);

                if(Indexer->GetBallStop() == 0)
                {

                    Indexer->FlipBallStop();

                }
            }

        }

    break;
   }





}


};

#endif