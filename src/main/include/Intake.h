#ifndef INTAKE_H
#define INTAKE_H

#include <frc/Solenoid.h>

#include <ctre/Phoenix.h>

class Intook 
{

private:

    VictorSPX IntakeMotor {7};
    frc::Solenoid IntakePosition {1};

public:

    //Set Addresses for motor and Solenoid
    Intook ()
    {};

    //Intake control (Position and power(Posibility of forward and backward))
    //IntakePower: (between -100 and 100)
    //IntakeOut: true = Out, False = up
    void IntakeRun(double IntakePower = 0, bool IntakeOut = true)
        {

            IntakePower = IntakePower / 100;
            IntakePosition.Set(IntakeOut);
            IntakeMotor.Set(ControlMode::PercentOutput, IntakePower);

        }

};

#endif