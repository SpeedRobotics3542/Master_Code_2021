#ifndef LIMELIGHT_H
#define LIMELIGHT_H

#include "frc/smartdashboard/Smartdashboard.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"

class LimeLight
{

private:
    /* data */
public:

    LimeLight(){}

    //limelight
    std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
    double targetOffsetAngle_Horizontal = table->GetNumber("tx", 0.0);
    double targetOffsetAngle_Vertical = table->GetNumber("ty", 0.0);
    double targetArea = table->GetNumber("ta", 0.0);
    double targetSkew = table->GetNumber("ts", 0.0);
    double targetValid = table->GetNumber("tv", 0.0);

    //Updates limelight values
    void LimelightValues()
    {

        table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
        targetOffsetAngle_Horizontal = table->GetNumber("tx", 0.0);
        targetOffsetAngle_Vertical = table->GetNumber("ty", 0.0);
        targetArea = table->GetNumber("ta", 0.0);
        targetSkew = table->GetNumber("ts", 0.0);
        targetValid = table->GetNumber("tv", 0.0);

    }

};



#endif // LIMELIGHT_H
