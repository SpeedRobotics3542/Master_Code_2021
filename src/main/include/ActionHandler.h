#ifndef ACTIONHANDLER_H
#define ACTIONHANDLER_H

#include "Shooter.h"
#include "DriveTrain.h"
#include "Indexer.h"
#include "Intake.h"
#include "Limelight.h"



class Handler
{
    private:

        DriveTrain *Chassis;
        Intook *Intake;
        Shooting *Shooter;
        Index *Indexer;
        LimeLight *Limelight;

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

};




#endif