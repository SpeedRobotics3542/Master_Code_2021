#ifndef LIMELIGHT_H
#define LIMELIGHT_H


#include "frc/smartdashboard/Smartdashboard.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"
#include <cmath>

class LimeLight
{

private:
    /* data */
public:
    double pi = 3.14159265359;

    LimeLight(){}

    //limelight
    std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
    double targetOffsetAngle_Horizontal = table->GetNumber("tx", 0.0);
    double targetOffsetAngle_Vertical = table->GetNumber("ty", 0.0);
    double targetArea = table->GetNumber("ta", 0.0);
    double targetSkew = table->GetNumber("ts", 0.0);
    double targetValid = table->GetNumber("tv", 0.0);
    double VerticalRads = 0;

    //CHANGE TO CORRECT VALUES THESE ARE ESIMATES
    double TargetHeight = 100;
    double RobotHeight = 24;
    double AngleToFloor = pi/6;

    //Updates limelight values
    void LimelightValues()
    {

        table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
        targetOffsetAngle_Horizontal = table->GetNumber("tx", 0.0);
        targetOffsetAngle_Vertical = table->GetNumber("ty", 0.0);
        VerticalRads = targetOffsetAngle_Vertical*pi/180;
        targetArea = table->GetNumber("ta", 0.0);
        targetSkew = table->GetNumber("ts", 0.0);
        targetValid = table->GetNumber("tv", 0.0);

    }

//purpose: get distance to target from limelight
// inputs: N/A
// outputs: double distance
double LimelightDistance()
{

   double Answer;
   Answer = (TargetHeight - RobotHeight) / tan(VerticalRads + AngleToFloor); 
   return Answer;

}

//d = (h2-h1) / tan(a1+a2)


};



#endif // LIMELIGHT_H
