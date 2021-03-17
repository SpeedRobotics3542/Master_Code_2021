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
        
        frc2::PIDController AimingPID{P, I, D};

    public:
    

Handler(DriveTrain* D, Intook* inny, Shooting* Shoot, Index* In, LimeLight* GreenLight)
{

    Chassis = D;
    Intake = inny;
    Shooter = Shoot;
    Indexer = In;
    Limelight = GreenLight;

}

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

void IndexShooterMetering(int Rpm = 100, bool activated = true)
{
    if(activated == 1)
    {

        Shooter->SetVelocity(Rpm);
        Indexer->HoldingSystemRun(75);
        Shooter->MeteringWheelRun(90);
    
    } else {

        Shooter->SetVelocity(0);
        Indexer->HoldingSystemRun(0);
        Shooter->MeteringWheelRun(0);

    }

}

// logic: assist in aiming
// inputs: none
// outputs: 1 if target is in range and valid 0 if target is not valid and or not in range


// TOLERANCES ON PID!!! SET THEM!!!!!

bool MasterAiming(int Pidgeon)
{
    //Target is valid and within set range
    if (Limelight->targetValid and Limelight->targetOffsetAngle_Horizontal > 8 or Limelight->targetOffsetAngle_Horizontal < -8)
    {
        //Limelight angle of error = "Pidgeon"
        Limelight->targetOffsetAngle_Horizontal = Pidgeon;  

        //Aiming PID is not where you want      
        while (!AimingPID.AtSetpoint())
        {

            //Move toward target
            Chassis->Aim(35);

            //Check to see if it is in range again
            if(AimingPID.AtSetpoint())
            {
                //Return 1 if true
                return 1;

            } else {

                !AimingPID.AtSetpoint();

            }

        }

    } else {

        return 0;

    }

}

//while(***conditional***)
//{***True Statement***}



};




#endif