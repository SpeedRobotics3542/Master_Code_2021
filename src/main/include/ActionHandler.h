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

    public:
    

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


//Connects Limelight, Drivetrain, and Pigeon to aim
bool MasterAiming()
{
    

    //Target is valid and within set range
    if (Limelight->targetValid and (Limelight->targetOffsetAngle_Horizontal > PIDTolerance or 
                                    Limelight->targetOffsetAngle_Horizontal < -PIDTolerance))
    {
        //Limelight angle of error = Pigeon 
        Pigeon->SetFusedHeading(Limelight->targetOffsetAngle_Horizontal);
        
        //Aiming PID is not where you want  
        //Check setpoint and move robot    
        while (!AimingPID.AtSetpoint())
        {

            //calculate PID output
            double power = AimingPID.Calculate(GetPigeonAngle(), 0);

            //Move toward target
            Chassis->Aim(power);

        }

        //Return 1 if at setpoint
        return 1;

    } else {

        return 0;

    }

}

};

#endif